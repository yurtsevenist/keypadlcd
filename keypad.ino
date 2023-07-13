#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <Servo.h>
#define Password_Length 8 

char Data[Password_Length]; 
char Master[Password_Length] = "12345678"; 
byte data_count = 0, master_count = 0;
bool Pass_is_good;
char customKey;
Servo servo;
int yesil=11,kirmizi=12;
const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

LiquidCrystal_I2C lcd(0x27, 20, 4); 

void setup(){
  lcd.init(); 
  lcd.backlight();
  pinMode(yesil, OUTPUT);
  pinMode(kirmizi, OUTPUT);
  servo.attach(10);
  servo.write(180);
}

void loop(){
  lcd.home();
  lcd.setCursor(0,0);
  lcd.print("Sifre Girin :");

  customKey = customKeypad.getKey();
  if (customKey){
    Data[data_count] = customKey; 
    lcd.setCursor(data_count,1); 
    lcd.print(Data[data_count]); 
    data_count++; 
    }

  if(data_count == Password_Length-1){
    lcd.clear();

    if(!strcmp(Data, Master)){
      lcd.print("Sifre Dogru");
      servo.write(0); 
      digitalWrite(yesil, HIGH);
      digitalWrite(kirmizi, LOW); 
      delay(2000);  
      }
    else{
      lcd.print("Sifre Yanlis!!!");
      servo.write(180);
      digitalWrite(kirmizi, HIGH);
      digitalWrite(yesil, LOW);
      delay(2000);
      }
    
    lcd.clear();
    clearData();  
  }
}

void clearData(){
  while(data_count !=0){
    Data[data_count--] = 0; 
  }
   digitalWrite(yesil, LOW);
   digitalWrite(kirmizi, LOW);  
  return;
}