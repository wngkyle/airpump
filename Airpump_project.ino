// In here, master is when the air pump operates at 100% full speed
// Mode1 is when air pump operates at 25% ~ 35% speed
// Mode2 is when air pump operates at 65% ~ 75% speed
// pResistor indicates the photoresistor use for detecting light

//---------------- Variable intialization and declaration -------------------//
int master = 9; // 100% full speed, set variable master equals to 9
int mode1 = 10; // 25% ~ 35% speed, set variable mode1 equals to 10
int mode2 = 11; // 65% ~ 75% speed, set variable mode2 equals to 11
int pResistor = A0; // set variable pResistor equals to A0 
int sensorValue; // Declare variable sensorValue for later use
int state; // Declare variable state for later use
//---------------------------------------------------------------------------//



// void setup is run once in the begining of every program
void setup() {
  // Set up the data rate (9600) in baud for serial data communication
  Serial.begin(9600); 

  //--- pinMode initialization, set pins on Arduino board to INPUT or OUTPUT ---//
  // Set master (digital pin 9) to output
  pinMode(master, OUTPUT);
  // Set mode1 (digital pin 10) to output, use to control transistor
  pinMode(mode1, OUTPUT);
  // Set mode2 (digital pin 11) to output, also later use to control transistor
  pinMode(mode2, OUTPUT);
  // Set pResistor (analog pin A0) to input
  pinMode(pResistor, INPUT);
  //---------------------------------------------------------------------------//
}


// void loop is executed continuously until the break command is met  
void loop() {
  // analogRead() allows us to retrieve the data collected by the photoresistor
  // The retrieved data is then stored in the variable sensorValue which is declared in the "Variable intialization and declaration" section
  sensorValue = analogRead(pResistor);
  // Don't worry about the serial.print below, they are just used to verify the analogRead() is reading the correct values and for debugging purposes
  Serial.print("Sensor Value: ");
  Serial.println(sensorValue);


  //----------------------- Setting the desired state ------------------------//
  // This section of code basically just decide which speed mode (100%, 65% ~ 75%, or 25% ~ 35%) should the motor operates on based on the brightness of the light 
  // source, or the values collected by the photoresistor and stored in variable sensorValue
  // The way we did is to employed a series of if-else statement to check each condition we want individually. There's definitely a better way to implement this, but 
  // this is the easiest and fastest method.

  // If sensorValue is greater than 230 and less than 260 (230 < sensorValue < 260), then set variable state to 1, which is referred as mode1 (25% ~ 35% speed)
  // Variable state is also declared in the "Variable intialization and declaration" section
  // In this case, we just use variable state to store the desired speed mode, and then we will later use variable state again for executing motor commands
  if (sensorValue > 230 && sensorValue < 260) {
    state = 1;
  } 
  // If sensorValue is greater than 320 and less than 350 (320 < sensorValue < 350), then set variable state to 2, which is referred as mode2 (65% ~ 75% speed)
  else if (sensorValue > 320 && sensorValue < 350) {
    state = 2;
  // If sensorValue is greater than 390 (sensorValue > 390), then set variable state to 3, which is referred as master (100% speed)
  } else if (sensorValue > 390) {
    state = 3;
  // If none of the conditions specified above are met, then set variable state to 0, or all OFF mode
  } else {
    state = 0;
  }
  //---------------------------------------------------------------------------//

  // Don't worry about this part too, it's for debugging
  Serial.print("Desire Mode: ");
  Serial.println(state);
  Serial.println("");

  //------------------------- Executing motor commands ------------------------//
  // In this section, we use switch statement to help execute the motor commands. (You can also use if-else statement if you want b/c they are fundamentally the same thing)
  // So so so basically switch statement only runs a certain block of code in its statement depending on the input value
  // EX: if state is 1, then it will only run the block of code starting from "case 1:" to "break;"
  // Keyword "break" in the switch statement allows the program to jump out of the switch statement, avoiding running other unwanted blocks of code

  switch (state) {
    case 0:
      // This block is executed if variable state equals to 0
      // set master (digital pin 9) to low output
      digitalWrite(master, LOW); 
      // set mode1 (digital pin 10) to low output
      digitalWrite(mode1, LOW);
      // set mode2 (digital pin 11) to low output
      digitalWrite(mode2, LOW);
      Serial.println("Actual Mode: 0");
      break; 
    case 1:
      // This block is executed if variable state equals to 1
      // set master (digital pin 9) to low output
      digitalWrite(master, LOW);
      // set mode1 (digital pin 10) to HIGH output
      digitalWrite(mode1, HIGH);
      // set mode2 (digital pin 11) to low output
      digitalWrite(mode2, LOW);
      Serial.println("Actual Mode: 1");
      break;
    case 2:
      // This block is executed if variable state equals to 2
      // set master (digital pin 9) to low output
      digitalWrite(master, LOW);
      // set mode1 (digital pin 10) to low output
      digitalWrite(mode1, LOW);
      // set mode2 (digital pin 11) to HIGH output
      digitalWrite(mode2, HIGH);
      Serial.println("Actual Mode: 2");
      break;
    case 3:
      // This block is executed if variable state equals to 4
      // set master (digital pin 9) to HIGH output
      digitalWrite(master, HIGH);
      // set mode1 (digital pin 10) to low output
      digitalWrite(mode1, LOW);
      // set mode2 (digital pin 11) to low output
      digitalWrite(mode2, LOW);
      Serial.println("Actual Mode: 3");
      break;
  }

  // Since each control pins (here I mean the master (digital pin 9), mode1 (digital pin 10), mode2 (digital pin 11)) is connected to a TIP120 transistor, by controlling
  // the HIGH and LOW of these output pins, we are able to control the transistors like digital switches. Just imagine when you set a control pin to HIGH, it's like
  // you turn ON/OFF switch on the motor to the ON mode. When you set a output pin to LOW, you bascially turn the ON/OFF switch to OFF mode. 

  // Case 0 : All OFF mode. All transistors are OFF, creating open circuit on the breadboard, so the motor won't run at all
  // Case 1 : Mode1, 25% ~ 35% speed
  // Case 2 : Mode2, 65% ~ 75% speed
  // Case 3 : Master, full speed

  //---------------------------------------------------------------------------//

  // Delay the program for 0.050 seconds
  delay(50);

  // Notes:
  // Navigate to the "Tools" tab on top of the screen and select "Serial Monitor" if you want to view the print values used for debugging
}
