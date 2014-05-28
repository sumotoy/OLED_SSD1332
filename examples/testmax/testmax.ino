/*
OLED_SSD1332 Test
(standard test from Adafruit width additions)
 */

#include <Adafruit_GFX.h>
#include <OLED_SSD1332.h>
#include <SPI.h>

/*
Note for Teensy 3.x !!!!!!!!!!!!!!!!!!!
 You should choose from those pins for CS and RS:
 2,6,9,10,15,20,23
 */
#define cs   10
#define rst  14
#define dc   9
/*
This library use SPI so you still have 2 wires to connect:
MOSI: uno(11), Teensy3(11), etc.
SCLK: uno(13), Teensy3(13), etc.

*/

// Color definitions
#define	BLACK           0x0000
#define	BLUE            0x001F
#define	RED             0xF800
#define	GREEN           0x07E0
#define CYAN            0x07FF
#define MAGENTA         0xF81F
#define YELLOW          0xFFE0  
#define WHITE           0xFFFF
#define TRANSPARENT     -1


OLED_SSD1332 oled = OLED_SSD1332(cs, dc, rst);

float p = 3.1415926;

void setup(void) {
  oled.begin();
  //whant try SPI at max speed???
  #if defined(__MK20DX128__) || defined(__MK20DX256__)
  oled.setBitrate(24000000);
  #endif

  uint16_t time = millis();
  time = millis() - time;

  oled.setRotation(0);
  oled.clearScreen();
  oled.setCursor(0,0);
  oled.print("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur adipiscing ante sed nibh tincidunt feugiat. Maecenas enim massa");
  delay(1000);

  tftPrintTest();
  delay(2000);

  //a single pixel
  oled.drawPixel(oled.width()/2, oled.height()/2, GREEN);
  delay(500);

  // line draw test
  testlines(YELLOW);
  delay(500);    

  // optimized lines
  testfastlines(RED, BLUE);
  delay(500);    

  testdrawrects(GREEN);
  delay(1000);

  testfillrects(BLUE, YELLOW);
  delay(1000);

  randomRect(0);
  delay(100);
  randomCircles(0);
  delay(100);
  randomLines();
  delay(100);
  randomPoints();
  delay(500);

  oled.clearScreen();
  testfillcircles(10, BLUE);
  testdrawcircles(10, WHITE);
  delay(1000);

  testroundrects();
  delay(500);

  testtriangles();
  delay(500);

}

void loop() {
  testlines(random(0x0010,0xFFFF));
  randomLines();
  //randomCircles(1);
  randomCircles(0);
  randomRect(1);
  randomRect(1);
  randomRect(1);
  randomRect(1);
  randomRect(1);
  randomRect(0);
  randomRect(0);
  randomRect(0);
  randomRect(0);
  randomRect(0);
  randomRect(0);
  randomPoints();
}

void testlines(uint16_t color) {
  oled.clearScreen();
  for (int16_t x=0; x < (oled.width()-1); x+=6) {
    oled.drawLine(0, 0, x, (oled.height()-1), color);
  }
  for (int16_t y=0; y < (oled.height()-1); y+=6) {
    oled.drawLine(0, 0, (oled.width()-1), y, color);
  }
  oled.clearScreen();
  for (int16_t x=0; x < (oled.width()-1); x+=6) {
    oled.drawLine((oled.width()-1), 0, x, (oled.height()-1), color);
  }
  for (int16_t y=0; y < (oled.height()-1); y+=6) {
    oled.drawLine((oled.width()-1), 0, 0, y, color);
  }

  oled.clearScreen();
  for (int16_t x=0; x < (oled.width()-1); x+=6) {
    oled.drawLine(0, (oled.height()-1), x, 0, color);
  }
  for (int16_t y=0; y < (oled.height()-1); y+=6) {
    oled.drawLine(0, (oled.height()-1), (oled.width()-1), y, color);
  }
  oled.clearScreen();
  for (int16_t x=0; x < (oled.width()-1); x+=6) {
    oled.drawLine((oled.width()-1), (oled.height()-1), x, 0, color);
  }
  for (int16_t y=0; y < (oled.height()-1); y+=6) {
    oled.drawLine((oled.width()-1), (oled.height()-1), 0, y, color);
  }
  delay(500);
}


void testdrawtext(char *text, uint16_t color) {
  oled.setTextSize(1);
  oled.setTextColor(WHITE);
  oled.setCursor(0,0);

  for (uint8_t i=0; i < 168; i++) {
    if (i == '\n') continue;
    oled.write(i);
    if ((i > 0) && (i % 21 == 0))
      oled.println();
  }    
}

void testfastlines(uint16_t color1, uint16_t color2) {
  oled.clearScreen();
  for (int16_t y=0; y < (oled.height()-1); y+=5) {
    oled.drawFastHLine(0, y, (oled.width()-1), color1);
  }
  for (int16_t x=0; x < (oled.width()-1); x+=5) {
    oled.drawFastVLine(x, 0, (oled.height()-1), color2);
  }
}

void testdrawrects(uint16_t color) {
  oled.clearScreen();
  for (int16_t x=0; x < (oled.height()-1); x+=6) {
    oled.drawRect(((oled.width()-1)/2) - (x/2), ((oled.height()-1)/2) - (x/2) , x, x, color);
  }
}

void testfillrects(uint16_t color1, uint16_t color2) {
  oled.clearScreen();
  for (int16_t x = (oled.height()-1); x > 6; x-=6) {
    oled.fillRect(((oled.width()-1)/2) - (x/2), ((oled.height()-1)/2) - (x/2) , x, x, color1);
    oled.drawRect(((oled.width()-1)/2) - (x/2), ((oled.height()-1)/2) - (x/2) , x, x, color2);
  }
}

void testfillcircles(uint8_t radius, uint16_t color) {
  for (uint8_t x=radius; x < (oled.width()-1); x+=(radius*2)) {
    for (uint8_t y=radius; y < (oled.height()-1); y+=(radius*2)) {
      oled.fillCircle(x, y, radius, color);
    }
  }  
}

void testdrawcircles(uint8_t radius, uint16_t color) {
  for (int16_t x=0; x < (oled.width()-1)+radius; x+=(radius*2)) {
    for (int16_t y=0; y < (oled.height()-1)+radius; y+=(radius*2)) {
      oled.drawCircle(x, y, radius, color);
    }
  }  
}

void testtriangles() {
  oled.clearScreen();
  int color = 0xF800;
  int t;
  int w = oled.width()/2;
  int x = oled.height();
  int y = 0;
  int z = oled.width();
  for(t = 0 ; t <= 15; t+=1) {
    oled.drawTriangle(w, y, y, x, z, x, color);
    x-=4;
    y+=4;
    z-=4;
    color+=100;
  }
}

void testroundrects() {
  oled.clearScreen();
  int color = 100;
  int i;
  int t;
  for(t = 0 ; t <= 4; t+=1) {
    int x = 0;
    int y = 0;
    int w = oled.width();
    int h = oled.height();
    for(i = 0 ; i <= 24; i+=1) {
      oled.drawRoundRect(x, y, w, h, 5, color);
      x+=2;
      y+=3;
      w-=4;
      h-=6;
      color+=1100;
    }
    color+=100;
  }
}

void tftPrintTest() {
  oled.clearScreen();
  oled.setCursor(0, 5);
  oled.setTextColor(RED);  
  oled.setTextSize(1);
  oled.println("Hello World!");
  oled.setTextColor(YELLOW, GREEN);
  oled.setTextSize(2);
  oled.print("Hello Wo");
  oled.setTextColor(BLUE);
  oled.setTextSize(3);
  oled.print(12.57);
  delay(1500);
  oled.setCursor(0, 5);
  oled.clearScreen();
  oled.setTextColor(WHITE);
  oled.setTextSize(0);
  oled.println("Hello World!");
  oled.setTextSize(1);
  oled.setTextColor(GREEN);
  oled.print(p, 5);
  oled.println(" Want pi?");
  oled.print(8675309, HEX); // print 8,675,309 out in HEX!
  oled.print(" Print HEX");
  oled.setTextColor(WHITE);
  oled.println("Sketch has been");
  oled.println("running for: ");
  oled.setTextColor(MAGENTA);
  oled.print(millis() / 1000);
  oled.setTextColor(WHITE);
  oled.print(" seconds.");
}




void randomRect(bool fill){
  oled.clearScreen();
  uint8_t k,c;
  for (k = 0; k < 16; k++) {
    for (c = 0; c < 32; c++) {
      uint8_t cx, cy, x, y, w, h;
      //  center
      cx = random(0,oled.width());
      cy = random(0,oled.height());
      //  size
      w = random(0,30 + 6);
      h = random(0,20 + 4);
      //  upper-left
      x = cx - w / 2;
      y = cy - h / 2;
      if (x < 0) x = 0;
      if (y < 0) y = 0;
      //  adjust size
      if (x + w > oled.width()) w = oled.width() - x;
      if (y + h > oled.height()) h = oled.height() - y;
      if (fill){
        oled.fillRect(x, y, w, h,random(0x0010,0xFFFF));
      } 
      else {
        oled.drawRect(x, y, w, h,random(0x0010,0xFFFF));
      }

    }
    oled.clearScreen();
  }
}

void randomCircles(bool fill){
  oled.clearScreen();
  uint8_t k,c;
  for (k = 0; k < oled.height(); k++) {
    for (c = 0; c < 32; c++) {
      //  coordinates
      uint8_t x = random(0,(oled.width()-4) + 3), y = random(0,(oled.height()-3) + 2), r = random(0,20 + 1);
      if (x - r <  0) r = x;
      if (x + r > (oled.width()-1)) r = (oled.width()-1) - x;
      if (y - r <  0) r = y;
      if (y + r > (oled.height()-1)) r = (oled.height()-1) - y;
      if (fill){
        oled.fillCircle(x, y, r,random(0x0010,0xFFFF));
      } 
      else {
        oled.drawCircle(x, y, r,random(0x0010,0xFFFF));
      }
    }
    if (!fill)oled.clearScreen();
  }
}


void randomLines(){
  oled.clearScreen();
  uint8_t k,c;
  for (k = 0; k < oled.height(); k++) {
    for (c = 0; c < 32; c++) {
      uint8_t x1 = random(0,oled.width()), y1 = random(0,oled.height()), x2 = random(0,oled.width()), y2 = random(0,oled.height());
      oled.drawLine(x1, y1, x2, y2,random(0x0010,0xFFFF));
    }
    oled.clearScreen();
  }
}


void randomPoints(){
  oled.clearScreen();
  int k,c;
  for (k = 0; k < 128; k++) {
    for (c = 0; c < 1000; c++) {
      uint8_t x = random(0,oled.width()), y = random(0,oled.height());
      oled.drawPixel(x, y,random(0x0010,0xFFFF));
    }
    oled.clearScreen();
  }
}
