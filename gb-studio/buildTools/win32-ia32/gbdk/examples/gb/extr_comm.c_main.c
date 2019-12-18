#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int UBYTE ;

/* Variables and functions */
 scalar_t__ IO_IDLE ; 
 scalar_t__ IO_RECEIVING ; 
 scalar_t__ IO_SENDING ; 
 int J_A ; 
 int J_B ; 
 int J_SELECT ; 
 int J_START ; 
 int _io_in ; 
 char _io_out ; 
 scalar_t__ _io_status ; 
 char* buffer ; 
 scalar_t__ joypad () ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  putchar (int) ; 
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/  receive_byte () ; 
 int /*<<< orphan*/  send_byte () ; 
 char* str ; 
 int waitpad (int) ; 
 int /*<<< orphan*/  waitpadup () ; 

void main(void)
{
  UBYTE i, n = 0;
  char *s;

  puts("Byte");
  puts("  A      : Send");
  puts("  B      : Receive");
  puts("String");
  puts("  START  : Send");
  puts("  SELECT : Receive");

  while(1) {
    i = waitpad(J_A | J_B | J_START | J_SELECT);
    waitpadup();

    if(i == J_A) {
      /* Send 1 byte */
      printf("Sending b... ");
      _io_out = n++;
      send_byte();
      /* Wait for IO completion... */
      while(_io_status == IO_SENDING && joypad() == 0)
	;
      if(_io_status == IO_IDLE)
	printf("OK\n");
      else
	printf("#%d\n", _io_status);
    } else if(i == J_B) {
      /* Receive 1 byte */
      printf("Receiving b... ");
      receive_byte();
      /* Wait for IO completion... */
      while(_io_status == IO_RECEIVING && joypad() == 0)
	;
      if(_io_status == IO_IDLE)
	printf("OK\n%d\n", _io_in);
      else
	printf("#%d\n", _io_status);
    } else if(i == J_START) {
      /* Send a string */
      printf("Sending s... ");
      s = str;
      while(1) {
	_io_out = *s;
	do {
	  send_byte();
	  /* Wait for IO completion... */
	  while(_io_status == IO_SENDING && joypad() == 0)
	    ;
	} while(_io_status != IO_IDLE && joypad() == 0);
	if(_io_status != IO_IDLE) {
	  printf("#%d\n", _io_status);
	  break;
	}
	if(*s == 0)
	  break;
	s++;
      }
      if(_io_status == IO_IDLE)
	printf("OK\n");
    } else if(i == J_SELECT) {
      /* Receive a string */
      printf("Receiving s... ");
      s = buffer;
      while(1) {
	receive_byte();
	/* Wait for IO completion... */
	while(_io_status == IO_RECEIVING && joypad() == 0)
	  ;
	if(_io_status != IO_IDLE) {
	  printf("#%d\n", _io_status);
	  break;
	}
	putchar(_io_in);
	*s = _io_in;
	if(*s == 0)
	  break;
	s++;
      }
      if(_io_status == IO_IDLE)
	printf("OK\n%s\n", buffer);
    }
    /* In case of user cancellation */
    waitpadup();
  }
}