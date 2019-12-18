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
struct fpreg {int /*<<< orphan*/  fpr_fpsr; int /*<<< orphan*/ * fpr; } ;
typedef  int /*<<< orphan*/  PTRACE_ARG3_TYPE ;

/* Variables and functions */
 int ARM_F0_REGNUM ; 
 int ARM_F7_REGNUM ; 
 int ARM_FPS_REGNUM ; 
 int /*<<< orphan*/  PIDGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PT_SETFPREGS ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int ptrace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regcache_collect (int,char*) ; 
 int /*<<< orphan*/  warning (char*) ; 

__attribute__((used)) static void
store_fp_regs (void)
{
  struct fpreg inferior_fp_registers;
  int ret;
  int regno;


  for (regno = ARM_F0_REGNUM; regno <= ARM_F7_REGNUM; regno++)
    regcache_collect
      (regno, (char *) &inferior_fp_registers.fpr[regno - ARM_F0_REGNUM]);

  regcache_collect (ARM_FPS_REGNUM, (char *) &inferior_fp_registers.fpr_fpsr);

#ifndef CROSS_DEBUGGER
  ret = ptrace (PT_SETFPREGS, PIDGET (inferior_ptid),
		(PTRACE_ARG3_TYPE) &inferior_fp_registers, 0);

  if (ret < 0)
    warning ("unable to store floating-point registers");
#endif
}