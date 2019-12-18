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
struct fpreg {int dummy; } ;
typedef  int /*<<< orphan*/  PTRACE_ARG3_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  PIDGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PT_GETFPREGS ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int ptrace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  supply_fpregset (struct fpreg*) ; 
 int /*<<< orphan*/  warning (char*) ; 

__attribute__((used)) static void
fetch_fp_regs (void)
{
  struct fpreg inferior_fp_registers;
#ifndef CROSS_DEBUGGER
  int ret;
#endif
  int regno;

#ifndef CROSS_DEBUGGER
  ret = ptrace (PT_GETFPREGS, PIDGET (inferior_ptid),
		(PTRACE_ARG3_TYPE) &inferior_fp_registers, 0);

  if (ret < 0)
    {
      warning ("unable to fetch general registers");
      return;
    }
#endif

  supply_fpregset (&inferior_fp_registers);
}