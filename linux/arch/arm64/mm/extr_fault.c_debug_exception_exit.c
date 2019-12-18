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
 scalar_t__ interrupts_enabled (struct pt_regs*) ; 
 int /*<<< orphan*/  preempt_enable_no_resched () ; 
 int /*<<< orphan*/  rcu_nmi_exit () ; 
 int /*<<< orphan*/  trace_hardirqs_on () ; 
 int /*<<< orphan*/  user_mode (struct pt_regs*) ; 

__attribute__((used)) static void debug_exception_exit(struct pt_regs *regs)
{
	preempt_enable_no_resched();

	if (!user_mode(regs))
		rcu_nmi_exit();

	if (interrupts_enabled(regs))
		trace_hardirqs_on();
}