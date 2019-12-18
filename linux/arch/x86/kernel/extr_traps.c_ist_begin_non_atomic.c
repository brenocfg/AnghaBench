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
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  on_thread_stack () ; 
 int /*<<< orphan*/  preempt_enable_no_resched () ; 
 int /*<<< orphan*/  user_mode (struct pt_regs*) ; 

void ist_begin_non_atomic(struct pt_regs *regs)
{
	BUG_ON(!user_mode(regs));

	/*
	 * Sanity check: we need to be on the normal thread stack.  This
	 * will catch asm bugs and any attempt to use ist_preempt_enable
	 * from double_fault.
	 */
	BUG_ON(!on_thread_stack());

	preempt_enable_no_resched();
}