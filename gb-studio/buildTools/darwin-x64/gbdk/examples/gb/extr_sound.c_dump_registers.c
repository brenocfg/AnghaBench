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
 scalar_t__ FIRST_X ; 
 scalar_t__ FIRST_Y ; 
 scalar_t__ TITLE_Y ; 
 int /*<<< orphan*/  UNSIGNED ; 
 scalar_t__ VAL_X ; 
 int /*<<< orphan*/  cls () ; 
 int /*<<< orphan*/  gotoxy (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  print (char*) ; 
 int /*<<< orphan*/  printn (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  putchar (char) ; 
 scalar_t__ soundReg ; 

void dump_registers()
{
  UBYTE reg;
  UBYTE i, j;

  cls();
  gotoxy(FIRST_X, TITLE_Y);
  print("Register Dump");

  for(i = 0, j = 0; i <= 0x16; i++, j++) {
    if(i == 0x05 || i == 0x0F)
      i++;
    if(j%2 == 0) {
      gotoxy(FIRST_X, FIRST_Y+j/2);
      print("0xFF");
    } else {
      gotoxy(FIRST_X+6, FIRST_Y+j/2);
      putchar('-');
    }
    printn(i+0x10, 16, UNSIGNED);
    if(j%2 == 0) {
      gotoxy(VAL_X, FIRST_Y+j/2);
    } else {
      gotoxy(VAL_X+2, FIRST_Y+j/2);
      putchar('-');
    }
    reg = ((UBYTE *)soundReg)[i];
    if(!(reg & 0xF0U)) putchar('0');
    printn(reg, 16, UNSIGNED);
  }
}