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
 unsigned int FPU_DISABLE_EXCEPTION ; 
 unsigned int FPU_EXCEPTION ; 
 int /*<<< orphan*/  do_fpu_context_switch (struct pt_regs*) ; 
 int /*<<< orphan*/  handle_fpu_exception (struct pt_regs*) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 

bool do_fpu_exception(unsigned int subtype, struct pt_regs *regs)
{
	int done = true;
	/* Coprocessor disabled exception */
	if (subtype == FPU_DISABLE_EXCEPTION) {
		preempt_disable();
		do_fpu_context_switch(regs);
		preempt_enable();
	}
	/* Coprocessor exception such as underflow and overflow */
	else if (subtype == FPU_EXCEPTION)
		handle_fpu_exception(regs);
	else
		done = false;
	return done;
}