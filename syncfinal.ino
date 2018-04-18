// This #include statement was automatically added by the Particle IDE.
#include "lib1.h"

// This #include statement was automatically added by the Particle IDE.
#include <elapsedMillis.h>

/* 
Final Project: SYNC
Vivian Wong & Enna Kim
DIGF 1006
OCAD University
Created on: April 10, 2017

Based on:
http://moving-rainbow.readthedocs.io/en/latest/guide/fade-in-and-out/ 
https://learn.adafruit.com/neopixel-jack-o-lantern/the-code // flickering light example
https://community.particle.io/t/serial-tutorial/26946
https://community.particle.io/t/elapsedmillis-and-elapsedmicros-library/2653
https://www.tweaking4all.com/hardware/arduino/adruino-led-strip-effects/
https://www.youtube.com/watch?v=E4y4qfPrcEI&feature=youtu.be
*/

// This #include statement was automatically added by the Particle IDE.
#include <neopixel.h>       // add Adafruit Neopixel library

// This #include statement was automatically added by the Particle IDE.

#include <elapsedMillis.h>  // add elapsedMillis library

#define PIN D1              // define digital pin 1
#define PIN2 D2             // define digital pin 2
#define PIN3 D3             // define digital pin 3
#define PIN4 D4             // define digital pin 4
#define PIXEL_TYPE WS2812B  // define pixel type as Neopixel strip

Adafruit_NeoPixel strip = Adafruit_NeoPixel(25, PIN, PIXEL_TYPE);       // initialize and set strip1 with necessary info  
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(15, PIN2, PIXEL_TYPE);     // initialize and set strip2 with necessary info
Adafruit_NeoPixel strip3 = Adafruit_NeoPixel(25, PIN3, PIXEL_TYPE);     // initialize and set strip3 with necessary info
Adafruit_NeoPixel strip4 = Adafruit_NeoPixel(25, PIN4, PIXEL_TYPE);     // initialize and set strip4 with necessary info

elapsedMillis timeElapsed;          // declare global elapsed millis time
unsigned int interval = 1000;       // delay in milliseconds between function called, set to 1000 ms

int waitTime = 5;                   // set waitTime to 5, used in fadeInAndOut()

const int analogInPin = A0;  // Analog input pin that the photoresistor is attached to
int sensorValue = 0;                // declare integer variable sensorValue and initiate it at 0
int outputValue = 0;                // declare integer variable outputValue and initiate it at 0

void setup()
{
  pinMode(analogInPin, INPUT); // set analog pin 0 as input
  strip.begin();        // prepare strip for data output
  strip2.begin();       // prepare strip2 for data output
  strip3.begin();       // prepare strip3 for data output
  strip4.begin();       // prepare strip4 for data output
  
  strip.show();         // show strip changes
  strip2.show();        // show strip2 changes
  strip3.show();        // show strip3 changes
  strip4.show();        // show strip4 changes
  
  Serial.begin(9600);   // initialize serial monitor
}


void loop()
{
    // Note: comments in brackets refer to what each called light pattern is representative of
    
  sensorValue = analogRead(analogInPin);                // sensorValue is equal to data read from analog pin 0
  outputValue = map(sensorValue, 0, 1023, 0, 200);      // map sensorValue to outputValue according to ratio values
  
  if (timeElapsed > interval)             // if timeElapsed is greater than interval time 1000 ms
  {				
    colorWipe(100, 40, 55, 50, 1);        // colour wipe strip 1 light pink forwards 
    colorWipe(0, 0, 0, 50, 1);            // colour wipe strip 1 no light forwards
    
    fadeInAndOut(25, 15, 255, waitTime);  // fade blue in and out for all strips (processing information)
    fadeInAndOut(190, 0, 150, waitTime);  // fade pink in and out for all strips
    fadeInAndOut(10, 150, 205, waitTime); // fade cyan in and out for all strips
    
    RunningLights(20, 40, 10, 100);       // light green sine wave for all strips (receiving signals)
    RunningLights(5, 5, 25, 100);       // light blue sine wave for all strips
    RunningLights(15, 10, 60, 100);         // light purple sine wave for all strips
    
    colorWipeBW(100, 40, 55, 100, 5);     // colour wipe light pink backwards, from right to left for all strips (successfully received signals)
    colorWipeBW(0, 0, 0, 100, 5);         // colour wipe no colour backwards, from left to right for all strips
    
    pulse(100, 100, 100, 2);              // white pulsating effect fading pixel 1 of strip 3 in and out every 2 seconds 8x (memory storage)
    
    colorWipe(60, 20, 5, 100, 3);     // colour wipe light orange forward, from right to left for strip 3 (sending signals)
    colorWipe(100, 40, 55, 100, 5);      // colour wipe light pink forward, from right to left for all strips
    colorWipe(0, 0, 0, 100, 5);          // colour wipe no colour forward, from right to left for all strips
    
    colorWipe(100, 40, 55, 50, 3);       // colour wipe strip 3 light pink  (finale of sending signals)
    colorWipe(0, 0, 0, 50, 3);           // colour wipe strip 3 no colour
    colorWipe(100, 40, 55, 50, 4);       // colour wipe strip 4 light pink
    colorWipe(0, 0, 0, 50, 4);           // colour wipe strip 4 no colour
    colorWipe(100, 40, 55, 50, 2);       // colour wipe strip 2 light pink
    colorWipe(0, 0, 0, 50, 2);           // colour wipe strip 2 no colour

      timeElapsed = 0;              // reset the counter to 0 so the counting starts over...
  }
  
  if (outputValue <= 240)                // if outputValue is less than or equal to 240...
  {
    colorWipeBW(100, 40, 55, 100, 5);    // colour wipe light pink backwards, from left to right for all strips (retrieving memory/signals)
    colorWipeBW(0, 0, 0, 100, 5);        // colour wipe no colour backwards, from left to right for all strips
  }
  else{ // if outputValue > 240
      // do nothing
  }
  
  Serial.print("sensor = ");            // print "sensor = " on serial monitor
  Serial.println(sensorValue);          // print sensorValue on serial monitor
  Serial.print("\t output = ");         // print "output = " on serial monitor
  Serial.println(outputValue);          // print outputValue on serial monitor
  delay(200);                           // delay each print of information by 200 ms
}

// function to wipe a colour across strip of pixels, from RIGHT to LEFT
void colorWipe (byte red, byte green, byte blue, int SpeedDelay, int Strip) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {

    if (Strip == 1) {                               // if Strip == 1
    strip.setPixelColor(i, red, green, blue);       // loop through and set each pixel colour of strip 1 to specified rgb values
    strip.show();                                   // show strip 1 changes
    } 
    
    if (Strip == 2) {                               // if Strip == 2
    strip2.setPixelColor(i, red, green, blue);      // loop through and set each pixel colour of strip2 to specified rgb values
    strip2.show();                                  //show strip2 changes
    }
    
    if (Strip == 3) {                               // if Strip == 3
    strip3.setPixelColor(i, red, green, blue);      // loop through and set each pixel colour of strip3 to specified rgb values
    strip3.show();                                  // show strip3 changes
    }
    
    if (Strip == 4) {                               // if Strip == 4
    strip4.setPixelColor(i, red, green, blue);      // loop through and set each pixel colour of strip4 to specified rgb values
    strip4.show();                                  // show strip4 changes
    }

    if (Strip == 5) {                           // if Pattern == 1, 3 neopixel strips colorWipe away from ear area, signals transferring of info
    strip2.setPixelColor(i, red, green, blue);  // loop through and set each pixel colour of strip2 to specified rgb values
    strip3.setPixelColor(i, red, green, blue);  // loop through and set each pixel colour of strip3 to specified rgb values
    strip4.setPixelColor(i, red, green, blue);  // loop through and set each pixel colour of strip4 to specified rgb values
    strip2.show();                              // show strip2 changes
    strip3.show();                              // show strip3 changes
    strip4.show();                              // show strip4 changes
    }
    delay(SpeedDelay);                         // delay iteration of each pixel colour change by speedDelay value
  }
}

// function to wipe a colour across a strip of pixels, from LEFT to RIGHT
void colorWipeBW (byte red, byte green, byte blue, int SpeedDelay, int Pattern) {
  for (uint16_t i = strip.numPixels(); i > 0; i--) {            // for i = number of pixels on strip, i greater than 0, change i by minus one each time
    
    if (Pattern == 1) {                                         // if Pattern == 1
    strip.setPixelColor(i, red, green, blue);                   // loop through and set each pixel colour of strip 1 to specified rgb values
    strip.show();                                               // show strip 1 changes
    }
    
     if (Pattern == 2) {                                        // if Pattern == 2
    strip2.setPixelColor(i, red, green, blue);                  // loop through and set each pixel colour of strip2 to specified rgb values
    strip2.show();                                              // show strip2 changes
    }
    
        if (Pattern == 3) {                                     // if Pattern == 3
    strip3.setPixelColor(i, red, green, blue);                  // loop through and set each pixel colour of strip3 to specified rgb values
    strip3.show();                                              // loop through and set each pixel colour of strip4 to specified rgb values
    }
    
        if (Pattern == 4) {
    strip4.setPixelColor(i, red, green, blue);                  // if Pattern == 4
    strip4.show();                                              // show strip4 changes
    }
    
      if (Pattern == 5) {                                       // if Pattern == 5, 3 neopixel strips colorWipe TOWARDS ear area, signals transferring of info
    strip2.setPixelColor(i, red, green, blue);                  // loop through and set each pixel colour of strip2 to specified rgb values
    strip3.setPixelColor(i, red, green, blue);                  // loop through and set each pixel colour of strip3 to specified rgb values
    strip4.setPixelColor(i, red, green, blue);                  // loop through and set each pixel colour of strip4 to specified rgb values
    strip2.show();                                              // show strip2 changes
    strip3.show();                                              // show strip3 changes
    strip4.show();                                              // show strip4 changes
    }
    delay(SpeedDelay);                                          // delay iteration of each pixel colour change by speedDelay value
  }
}



void fadeInAndOut(uint8_t red, uint8_t green, uint8_t blue, uint8_t wait) { // fadeInAndOut pattern portrays processing of information

  for(uint8_t b=0; b <255; b++) {                                           // for b = 0; b less than 255, increase b by 1 each time
     for(uint8_t i=0; i < strip.numPixels(); i++) {                         // for i = 0; i less than number of pixels in strip, increase i by 1
        strip.setPixelColor(i, red*b/255, green*b/255, blue*b/255);         // set colour according to specified values for strip 1, fade in effect
        strip2.setPixelColor(i, red*b/255, green*b/255, blue*b/255);        // set colour according to specified values for strip2, fade in effect
        strip3.setPixelColor(i, red*b/255, green*b/255, blue*b/255);        // set colour according to specified values for strip3, fade in effect
        strip4.setPixelColor(i, red*b/255, green*b/255, blue*b/255);        // set colour according to speciied values for strip4, fade in effect
     }
     strip.show();                                                          // show strip changes
     strip2.show();                                                         // show strip2 changes
     strip3.show();                                                         // show strip3 changes
     strip4.show();                                                         // show strip4 changes
     delay(wait);                                                           // delay for specified value of wait
  }

  for(uint8_t b=255; b > 0; b--) {                                      // for = 255, b greater than 0, decrease b by 1 each time
     for(uint8_t i=0; i < strip.numPixels(); i++) {                     // for i = 0, i less than number of pixels in strip, increase i by 1
        strip.setPixelColor(i, red*b/255, green*b/255, blue*b/255);     // set colour according to specified values for strip 1, fade out effect
        strip2.setPixelColor(i, red*b/255, green*b/255, blue*b/255);    // set colour according to specified values for strip2, fade out effect
        strip3.setPixelColor(i, red*b/255, green*b/255, blue*b/255);    // set colour according to specified values for strip3, fade out effect
        strip4.setPixelColor(i, red*b/255, green*b/255, blue*b/255);    // set colour according to specified values for strip4, fade out effect
     }
     strip.show();                                                      // show strip changes
     strip2.show();                                                     // show strip2 changes
     strip3.show();                                                     // show strip3 changes
     strip4.show();                                                     // show strip4 changes
     delay(wait);                                                       // delay for specified value of wait
  }
}

void RunningLights(byte red, byte green, byte blue, int WaveDelay) {    // RunningLights pattern runs using a sine wave
  int Position=0;                                                       // set integer variable Position to 0    
  
  for(int i=0; i<strip3.numPixels()*2; i++)                         // for integer i=0, as long as i is less than number of pixels * 2 in strip 3, increase i by 1
  {
      Position++;                                                       // add one to position through each loop
      for(int i=0; i<strip3.numPixels(); i++) {                         // for integer i=0, if i is less than number of pixels in strip 3, increase i by 1
                    
         strip2.setPixelColor(i,((sin(i+Position) * 127 + 128)/255)*red,    // set each pixel colour of strip2 based on sine wave position and specified rgb values
                   ((sin(i+Position) * 127 + 128)/255)*green,
                   ((sin(i+Position) * 127 + 128)/255)*blue);
                   
        strip3.setPixelColor(i,((sin(i+Position) * 127 + 128)/255)*red,     // set each pixel colour of strip3 based on sine wave position and specified rgb values
                   ((sin(i+Position) * 127 + 128)/255)*green,
                   ((sin(i+Position) * 127 + 128)/255)*blue);
                   
         strip4.setPixelColor(i,((sin(i+Position) * 127 + 128)/255)*red,    // set each pixel colour of strip4 based on sine wave position and specified rgb values
                   ((sin(i+Position) * 127 + 128)/255)*green,
                   ((sin(i+Position) * 127 + 128)/255)*blue);

      }
      strip2.show();                                                        // show strip2 changes
      strip3.show();                                                        // show strip3 changes
      strip4.show();                                                        // show strip4 changes
      delay(WaveDelay);                                                     // delay for specified value of WaveDelay
  }
}

void pulse(uint8_t red, uint8_t green, uint8_t blue, uint8_t wait) {         // pulse function allows pixel 1 of strip3 to fade in and out repeatedly
    
    for(uint8_t k=0; k < 8; k++) {                                           // for k = 0; k less than 8, increase k by 1 each time
                                                                             // iterate through this for loop 8x (pulsing occurs 8 times)
                                                                             
        for(uint8_t b=0; b <255; b++) {                                          // for b = 0; b less than 255, increase b by 1 each time
            strip3.setPixelColor(1, red*b/255, green*b/255, blue*b/255);         // set colour according to specified values for strip3, fade in effect
            strip3.show();                                                       // show strip3 changes
            delay(wait);                                                         // delay for specified value of wait
        }
    
        for(uint8_t b=255; b > 0; b--) {                                         // for = 255, b greater than 0, decrease b by 1 each time
            strip3.setPixelColor(1, red*b/255, green*b/255, blue*b/255);         // set colour according to specified values for strip3, fade out effect
            strip3.show();                                                       // show strip3 changes
            delay(wait);                                                         // delay for specified value of wait
        }
    }
}

