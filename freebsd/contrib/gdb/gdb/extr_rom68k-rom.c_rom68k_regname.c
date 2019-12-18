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
typedef  int /*<<< orphan*/  regnames ;

/* Variables and functions */
 int NUM_REGS ; 

__attribute__((used)) static const char *
rom68k_regname (int index) 
{

  static char *regnames[] =
  {
    "D0", "D1", "D2", "D3", "D4", "D5", "D6", "D7",
    "A0", "A1", "A2", "A3", "A4", "A5", "A6", "ISP",
    "SR", "PC"
  };
  
  if ((index >= (sizeof (regnames) / sizeof(regnames[0]))) 
       || (index < 0) || (index >= NUM_REGS))
    return NULL;
  else
    return regnames[index];

}