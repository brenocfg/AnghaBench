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
struct pt_regs {int dummy; } ;
struct TYPE_3__ {int trap_nr; } ;
struct TYPE_4__ {TYPE_1__ thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  arch_irq_disabled_regs (struct pt_regs*) ; 
 scalar_t__ arch_irqs_disabled () ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  die (char*,struct pt_regs*,int) ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  show_signal_msg (int,struct pt_regs*,int,unsigned long) ; 
 int /*<<< orphan*/  thread_pkey_regs_save (TYPE_1__*) ; 
 int /*<<< orphan*/  user_mode (struct pt_regs*) ; 

__attribute__((used)) static bool exception_common(int signr, struct pt_regs *regs, int code,
			      unsigned long addr)
{
	if (!user_mode(regs)) {
		die("Exception in kernel mode", regs, signr);
		return false;
	}

	show_signal_msg(signr, regs, code, addr);

	if (arch_irqs_disabled() && !arch_irq_disabled_regs(regs))
		local_irq_enable();

	current->thread.trap_nr = code;

	/*
	 * Save all the pkey registers AMR/IAMR/UAMOR. Eg: Core dumps need
	 * to capture the content, if the task gets killed.
	 */
	thread_pkey_regs_save(&current->thread);

	return true;
}