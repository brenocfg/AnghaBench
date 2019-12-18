#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pt_regs {int dummy; } ;
struct TYPE_4__ {unsigned long fault_address; } ;
struct TYPE_5__ {TYPE_1__ thread; } ;

/* Variables and functions */
 TYPE_2__* current ; 
 int /*<<< orphan*/  pr_info (char*,char const*) ; 
 int /*<<< orphan*/  show_regs (struct pt_regs*) ; 
 int /*<<< orphan*/  show_stacktrace (TYPE_2__*,struct pt_regs*) ; 
 int /*<<< orphan*/  user_mode (struct pt_regs*) ; 

void show_kernel_fault_diag(const char *str, struct pt_regs *regs,
			    unsigned long address)
{
	current->thread.fault_address = address;

	/* Show fault description */
	pr_info("\n%s\n", str);

	/* Caller and Callee regs */
	show_regs(regs);

	/* Show stack trace if this Fatality happened in kernel mode */
	if (!user_mode(regs))
		show_stacktrace(current, regs);
}