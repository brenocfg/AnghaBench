#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pt_regs {int /*<<< orphan*/  msr; scalar_t__ nip; } ;
struct perf_event {int dummy; } ;
struct TYPE_3__ {struct perf_event* last_hit_ubp; } ;
struct TYPE_4__ {TYPE_1__ thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_SE ; 
 int /*<<< orphan*/  WARN (int,char*,unsigned long) ; 
 scalar_t__ __get_user_inatomic (unsigned int,unsigned int*) ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  emulate_step (struct pt_regs*,unsigned int) ; 
 scalar_t__ is_larx_stcx_instr (struct pt_regs*,unsigned int) ; 
 int /*<<< orphan*/  perf_event_disable_inatomic (struct perf_event*) ; 
 int /*<<< orphan*/  printk_ratelimited (char*,unsigned long) ; 
 scalar_t__ user_mode (struct pt_regs*) ; 

__attribute__((used)) static bool stepping_handler(struct pt_regs *regs, struct perf_event *bp,
			     unsigned long addr)
{
	unsigned int instr = 0;

	if (__get_user_inatomic(instr, (unsigned int *)regs->nip))
		goto fail;

	if (is_larx_stcx_instr(regs, instr)) {
		printk_ratelimited("Breakpoint hit on instruction that can't be emulated."
				   " Breakpoint at 0x%lx will be disabled.\n", addr);
		goto disable;
	}

	/* Do not emulate user-space instructions, instead single-step them */
	if (user_mode(regs)) {
		current->thread.last_hit_ubp = bp;
		regs->msr |= MSR_SE;
		return false;
	}

	if (!emulate_step(regs, instr))
		goto fail;

	return true;

fail:
	/*
	 * We've failed in reliably handling the hw-breakpoint. Unregister
	 * it and throw a warning message to let the user know about it.
	 */
	WARN(1, "Unable to handle hardware breakpoint. Breakpoint at "
		"0x%lx will be disabled.", addr);

disable:
	perf_event_disable_inatomic(bp);
	return false;
}