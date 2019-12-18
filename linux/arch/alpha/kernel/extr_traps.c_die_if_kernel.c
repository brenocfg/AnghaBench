#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pt_regs {int ps; scalar_t__ pc; } ;
struct TYPE_3__ {int /*<<< orphan*/  comm; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOCKDEP_NOW_UNRELIABLE ; 
 int /*<<< orphan*/  SIGSEGV ; 
 int /*<<< orphan*/  TAINT_DIE ; 
 int /*<<< orphan*/  TIF_DIE_IF_KERNEL ; 
 int /*<<< orphan*/  add_taint (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  dik_show_code (unsigned int*) ; 
 int /*<<< orphan*/  dik_show_regs (struct pt_regs*,unsigned long*) ; 
 int /*<<< orphan*/  dik_show_trace (unsigned long*) ; 
 int /*<<< orphan*/  do_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hard_smp_processor_id () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  task_pid_nr (TYPE_1__*) ; 
 scalar_t__ test_and_set_thread_flag (int /*<<< orphan*/ ) ; 

void
die_if_kernel(char * str, struct pt_regs *regs, long err, unsigned long *r9_15)
{
	if (regs->ps & 8)
		return;
#ifdef CONFIG_SMP
	printk("CPU %d ", hard_smp_processor_id());
#endif
	printk("%s(%d): %s %ld\n", current->comm, task_pid_nr(current), str, err);
	dik_show_regs(regs, r9_15);
	add_taint(TAINT_DIE, LOCKDEP_NOW_UNRELIABLE);
	dik_show_trace((unsigned long *)(regs+1));
	dik_show_code((unsigned int *)regs->pc);

	if (test_and_set_thread_flag (TIF_DIE_IF_KERNEL)) {
		printk("die_if_kernel recursion detected.\n");
		local_irq_enable();
		while (1);
	}
	do_exit(SIGSEGV);
}