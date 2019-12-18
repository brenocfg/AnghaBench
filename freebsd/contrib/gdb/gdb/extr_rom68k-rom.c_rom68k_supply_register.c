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

/* Variables and functions */
 int M68K_A0_REGNUM ; 
 int M68K_D0_REGNUM ; 
 int PC_REGNUM ; 
 int PS_REGNUM ; 
 int SP_REGNUM ; 
 char* rom68k_supply_one_register (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
rom68k_supply_register (char *regname, int regnamelen, char *val, int vallen)
{
  int numregs;
  int regno;

  numregs = 1;
  regno = -1;

  if (regnamelen == 2)
    switch (regname[0])
      {
      case 'S':
	if (regname[1] == 'R')
	  regno = PS_REGNUM;
	break;
      case 'P':
	if (regname[1] == 'C')
	  regno = PC_REGNUM;
	break;
      case 'D':
	if (regname[1] != 'R')
	  break;
	regno = M68K_D0_REGNUM;
	numregs = 8;
	break;
      case 'A':
	if (regname[1] != 'R')
	  break;
	regno = M68K_A0_REGNUM;
	numregs = 7;
	break;
      }
  else if (regnamelen == 3)
    switch (regname[0])
      {
      case 'I':
	if (regname[1] == 'S' && regname[2] == 'P')
	  regno = SP_REGNUM;
      }

  if (regno >= 0)
    while (numregs-- > 0)
      val = rom68k_supply_one_register (regno++, val);
}