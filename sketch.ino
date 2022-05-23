#include <LiquidCrystal_I2C.h>
#include <ezButton.h>

byte clk = 2;
byte dt = 3;
byte sw = 4;

//  to track number of rotations
int counter = 0;
int prev_counter = 0;

//  lcd object : setting register address 0x27
LiquidCrystal_I2C lcd(0x27 , 20 , 4);

//  button object and variable
ezButton button(sw);

void setup(){

  attachInterrupt(digitalPinToInterrupt(clk) , encoder , FALLING);
  button.setDebounceTime(25);

  lcd.init();
  lcd.clear();
  lcd.backlight();

  lcd_print(0,0,"Enter Number : ");
  lcd_print(0,1,String(counter));
}

void encoder(){

  prev_counter = counter;

  if (digitalRead(dt)  ==  HIGH)counter++;
  else counter--;

  counter = constrain(counter , 0 , 256);
}

void loop(){

  //  looping the button
  button.loop();

  //  if button is pressed
  if (button.isPressed()){
    lcd.clear();
    String bin = "BIN : " + String(counter , BIN);
    String dec = "DEC : " + String(counter , DEC);
    String hex = "HEX : " + String(counter , HEX);
    lcd_print(0,0,bin);
    lcd_print(0,1,dec);
    lcd_print(0,2,hex);
  }

  if (prev_counter != counter){
    lcd.clear();
    lcd_print(0,0,"Enter Number : ");
    lcd_print(0,1,String(counter));
    prev_counter = counter;
  }

  //  for better working of simulator
  delay(10);
}


void lcd_print(int x , int y , String message){

  lcd.setCursor(x,y);
  lcd.print(message);
}

