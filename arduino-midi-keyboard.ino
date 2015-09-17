/* Simple midi keyboard firmware          */
/* Reads keyboard matrix and outputs midi */
/* Public domain                          */

#include <MIDI.h>
uint16_t matrix_old[8] = {0};
uint16_t matrix[8] = {0};

MIDI_CREATE_DEFAULT_INSTANCE();

void setup() {
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(A5, OUTPUT);
  pinMode(A6, OUTPUT);
  pinMode(A7, OUTPUT);
  pinMode(50, OUTPUT);
  pinMode(51, OUTPUT);
  pinMode(52, OUTPUT);
  pinMode(53, OUTPUT);;
  
  //Serial.begin(115200);
  MIDI.begin(1);
}

void loop() {
  for (uint8_t oct = 0; oct < 8; oct++) { matrix_old[oct] = matrix[oct]; matrix[oct] = 0; }
  uint16_t key = 1;
  uint8_t keynum = 0;
  while (key<4097) {
  /*digitalWrite(A0, 0);//key&1);
  digitalWrite(A1, 1);//key&2);
  digitalWrite(A2, 0);//key&4);
  digitalWrite(A3, 0);//key&8);
  digitalWrite(A4, 0);//key&16);
  digitalWrite(A5, 0);//key&32);
  digitalWrite(A6, 0);//key&64);
  digitalWrite(A7, 0);//key&128);
  digitalWrite(50, 0);//key&256);
  digitalWrite(51, 0);//key&512);
  digitalWrite(52, 0);//key&1024);
  digitalWrite(53, 0);//key&2048);
  digitalWrite(54, 0);//key&4096);
  Serial.println("Key: "+String(key, DEC));*/
  //delay(100);
    PORTF = key&0xFF;
    PORTB = key >> 8;
    //Serial.print(key&0xFF, DEC);
    //Serial.print(" ");
    //Serial.print(key >> 8, DEC);
    //Serial.println(" ");
    //values[0] = 
    //Serial.print(keynum);
    //Serial.print(" ");
    //bool key1 = ((PINK&128) >> 7);
    //Serial.print(key1);
    /*
    if (((PINK&128)>>7)) { Serial.print("0. "); Serial.println(keynum, DEC); matrix[0] += key; }
    if (((PINK&64)>>6)) { Serial.print("1. "); Serial.println(keynum, DEC); matrix[1] += key; }
    if (((PINK&32)>>5)) { Serial.print("2. "); Serial.println(keynum, DEC); matrix[2] += key; }
    if (((PINK&16)>>4)) { Serial.print("3. "); Serial.println(keynum, DEC); matrix[3] += key; }
    if (((PINK&8)>>3)) { Serial.print("4. "); Serial.println(keynum, DEC); matrix[4] += key; }
    if (((PINK&4)>>2)) { Serial.print("5. "); Serial.println(keynum, DEC); matrix[5] += key; }
    if (((PINK&2)>>1)) { Serial.print("6. "); Serial.println(keynum, DEC); matrix[6] += key; }
    if (((PINK&1)>>0)) { Serial.print("7. "); Serial.println(keynum, DEC); matrix[7] += key; }
    */
    
    if (((PINK&128)>>7)) { matrix[0] += key; }
    if (((PINK&64)>>6)) { matrix[1] += key; }
    if (((PINK&32)>>5)) { matrix[2] += key; }
    if (((PINK&16)>>4)) { matrix[3] += key; }
    if (((PINK&8)>>3)) { matrix[4] += key; }
    if (((PINK&4)>>2)) { matrix[5] += key; }
    if (((PINK&2)>>1)) { matrix[6] += key; }
    if (((PINK&1)>>0)) { matrix[7] += key; }
    

    //Serial.println("matrix[0] += (("+String(((PINK&128)>>7),DEC)+") << "+ String(keynum, DEC)+")");
    //Serial.println((PINK&128)>>7, DEC);

    
    key = key << 1;
    keynum++;
    //Serial.print(String(PINK, DEC)+", ");   
    //delay(100); 
  }

  uint8_t oct = 0;
  //Serial.println();
  for (uint8_t oct = 0; oct < 8; oct++) {
    //Serial.print(String(matrix[oct], BIN)+" ");
    if (!(matrix[oct]==matrix_old[oct])) {
      for (uint16_t key = 0; key < 13; key++) {
        bool value = (matrix[oct]&(1<<key))>>key;
        bool value_old = (matrix_old[oct]&(1<<key))>>key;
        if (!(value==value_old)) {
          uint8_t midinumber = 29+(key+12*oct);
          if (midinumber>= 81) midinumber = 65+(12*(oct-4)+(key-4));
          if (value) {
            MIDI.sendNoteOn(midinumber,127,1);
            //Serial.println("NoteOn "+String(midinumber, DEC));
          } else {
            MIDI.sendNoteOff(midinumber,0,1);
            //Serial.println("NoteOff "+String(midinumber, DEC));
          }
        }
      }
    }
  }
}
