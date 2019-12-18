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
 int SPARC32_NPC_REGNUM ; 
 int SPARC32_PC_REGNUM ; 
 int SPARC32_PSR_REGNUM ; 
 int SPARC32_Y_REGNUM ; 
 int SPARC_G1_REGNUM ; 
 int SPARC_G7_REGNUM ; 
 int SPARC_I0_REGNUM ; 
 int SPARC_I7_REGNUM ; 
 int SPARC_L0_REGNUM ; 
 int SPARC_L7_REGNUM ; 
 int SPARC_O0_REGNUM ; 
 int SPARC_O7_REGNUM ; 

int
sparc32_gregset_supplies_p (int regnum)
{
  /* Integer registers.  */
  if ((regnum >= SPARC_G1_REGNUM && regnum <= SPARC_G7_REGNUM)
      || (regnum >= SPARC_O0_REGNUM && regnum <= SPARC_O7_REGNUM)
      || (regnum >= SPARC_L0_REGNUM && regnum <= SPARC_L7_REGNUM)
      || (regnum >= SPARC_I0_REGNUM && regnum <= SPARC_I7_REGNUM))
    return 1;

  /* Control registers.  */
  if (regnum == SPARC32_PC_REGNUM
      || regnum == SPARC32_NPC_REGNUM
      || regnum == SPARC32_PSR_REGNUM
      || regnum == SPARC32_Y_REGNUM)
    return 1;

  return 0;
}