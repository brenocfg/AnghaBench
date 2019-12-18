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
struct task_struct {char const* comm; int pid; } ;
struct pt_regs {int sp; } ;

/* Variables and functions */
 int PAGE_MASK ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  SIGSEGV ; 
 int /*<<< orphan*/  bust_spinlocks (int) ; 
 int /*<<< orphan*/  console_verbose () ; 
 struct task_struct* current ; 
 int /*<<< orphan*/  die_lock ; 
 int /*<<< orphan*/  do_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_instr (struct pt_regs*) ; 
 int /*<<< orphan*/  dump_mem (char*,int,int) ; 
 int /*<<< orphan*/  dump_stack () ; 
 int end_of_stack (struct task_struct*) ; 
 scalar_t__ in_interrupt () ; 
 int /*<<< orphan*/  pr_emerg (char*,char const*,...) ; 
 int /*<<< orphan*/  print_modules () ; 
 int /*<<< orphan*/  show_regs (struct pt_regs*) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  user_mode (struct pt_regs*) ; 

void die(const char *str, struct pt_regs *regs, int err)
{
	struct task_struct *tsk = current;
	static int die_counter;

	console_verbose();
	spin_lock_irq(&die_lock);
	bust_spinlocks(1);

	pr_emerg("Internal error: %s: %x [#%d]\n", str, err, ++die_counter);
	print_modules();
	pr_emerg("CPU: %i\n", smp_processor_id());
	show_regs(regs);
	pr_emerg("Process %s (pid: %d, stack limit = 0x%p)\n",
		 tsk->comm, tsk->pid, end_of_stack(tsk));

	if (!user_mode(regs) || in_interrupt()) {
		dump_mem("Stack: ", regs->sp, (regs->sp + PAGE_SIZE) & PAGE_MASK);
		dump_instr(regs);
		dump_stack();
	}

	bust_spinlocks(0);
	spin_unlock_irq(&die_lock);
	do_exit(SIGSEGV);
}