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
struct reg {unsigned int r_pc; int /*<<< orphan*/  r_cpsr; int /*<<< orphan*/  r_lr; int /*<<< orphan*/  r_sp; int /*<<< orphan*/ * r; } ;
typedef  int /*<<< orphan*/  PTRACE_ARG3_TYPE ;

/* Variables and functions */
 unsigned int ADDR_BITS_REMOVE (unsigned int) ; 
 int ARM_A1_REGNUM ; 
 int ARM_LR_REGNUM ; 
 int ARM_PC_REGNUM ; 
 int ARM_PS_REGNUM ; 
 int ARM_SP_REGNUM ; 
 int /*<<< orphan*/  PIDGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PT_SETREGS ; 
 scalar_t__ arm_apcs_32 ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int ptrace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regcache_collect (int,char*) ; 
 int /*<<< orphan*/  warning (char*) ; 

__attribute__((used)) static void
store_regs (void)
{
  struct reg inferior_registers;
  int ret;
  int regno;


  for (regno = ARM_A1_REGNUM; regno < ARM_SP_REGNUM; regno++)
    regcache_collect (regno, (char *) &inferior_registers.r[regno]);

  regcache_collect (ARM_SP_REGNUM, (char *) &inferior_registers.r_sp);
  regcache_collect (ARM_LR_REGNUM, (char *) &inferior_registers.r_lr);

  if (arm_apcs_32)
    {
      regcache_collect (ARM_PC_REGNUM, (char *) &inferior_registers.r_pc);
      regcache_collect (ARM_PS_REGNUM, (char *) &inferior_registers.r_cpsr);
    }
  else
    {
      unsigned pc_val;
      unsigned psr_val;

      regcache_collect (ARM_PC_REGNUM, (char *) &pc_val);
      regcache_collect (ARM_PS_REGNUM, (char *) &psr_val);
	  
      pc_val = ADDR_BITS_REMOVE (pc_val);
      psr_val ^= ADDR_BITS_REMOVE (psr_val);

      inferior_registers.r_pc = pc_val | psr_val;
    }

#ifndef CROSS_DEBUGGER
  ret = ptrace (PT_SETREGS, PIDGET (inferior_ptid),
		(PTRACE_ARG3_TYPE) &inferior_registers, 0);

  if (ret < 0)
    warning ("unable to store general registers");
#endif
}