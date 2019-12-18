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
struct reg {int /*<<< orphan*/  r_pc; int /*<<< orphan*/  r_cpsr; int /*<<< orphan*/  r_lr; int /*<<< orphan*/  r_sp; int /*<<< orphan*/ * r; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int ARM_A1_REGNUM ; 
 int ARM_LR_REGNUM ; 
 int ARM_PC_REGNUM ; 
 int ARM_PS_REGNUM ; 
 int ARM_SP_REGNUM ; 
 scalar_t__ arm_apcs_32 ; 
 int /*<<< orphan*/  supply_register (int,char*) ; 

void
supply_gregset (struct reg *gregset)
{
  int regno;
  CORE_ADDR r_pc;

  /* Integer registers.  */
  for (regno = ARM_A1_REGNUM; regno < ARM_SP_REGNUM; regno++)
    supply_register (regno, (char *) &gregset->r[regno]);

  supply_register (ARM_SP_REGNUM, (char *) &gregset->r_sp);
  supply_register (ARM_LR_REGNUM, (char *) &gregset->r_lr);
  supply_register (ARM_PC_REGNUM, (char *) &gregset->r_pc);

  if (arm_apcs_32)
    supply_register (ARM_PS_REGNUM, (char *) &gregset->r_cpsr);
  else
    supply_register (ARM_PS_REGNUM, (char *) &gregset->r_pc);
}