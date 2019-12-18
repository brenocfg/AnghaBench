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
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGKILL ; 
 int /*<<< orphan*/  SIGTRAP ; 
 int /*<<< orphan*/  __die_if_kernel (char*,struct pt_regs*,int /*<<< orphan*/ ) ; 
 int check_hw_breakpoint (struct pt_regs*) ; 
 int /*<<< orphan*/  force_sig (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  preempt_enable () ; 

void
do_debug(struct pt_regs *regs)
{
#ifdef CONFIG_HAVE_HW_BREAKPOINT
	int ret = check_hw_breakpoint(regs);

	preempt_enable();
	if (ret == 0)
		return;
#endif
	__die_if_kernel("Breakpoint in kernel", regs, SIGKILL);

	/* If in user mode, send SIGTRAP signal to current process */

	force_sig(SIGTRAP);
}