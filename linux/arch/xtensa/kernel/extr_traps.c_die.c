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
struct pt_regs {scalar_t__* areg; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_PREEMPT ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOCKDEP_NOW_UNRELIABLE ; 
 int /*<<< orphan*/  TAINT_DIE ; 
 int /*<<< orphan*/  add_taint (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  console_verbose () ; 
 int /*<<< orphan*/  die_lock ; 
 int /*<<< orphan*/  do_exit (long) ; 
 scalar_t__ in_interrupt () ; 
 int /*<<< orphan*/  panic (char*) ; 
 scalar_t__ panic_on_oops ; 
 int /*<<< orphan*/  pr_info (char*,char const*,long,int,char*) ; 
 int /*<<< orphan*/  show_regs (struct pt_regs*) ; 
 int /*<<< orphan*/  show_stack (int /*<<< orphan*/ *,unsigned long*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  user_mode (struct pt_regs*) ; 

void die(const char * str, struct pt_regs * regs, long err)
{
	static int die_counter;

	console_verbose();
	spin_lock_irq(&die_lock);

	pr_info("%s: sig: %ld [#%d]%s\n", str, err, ++die_counter,
		IS_ENABLED(CONFIG_PREEMPT) ? " PREEMPT" : "");
	show_regs(regs);
	if (!user_mode(regs))
		show_stack(NULL, (unsigned long*)regs->areg[1]);

	add_taint(TAINT_DIE, LOCKDEP_NOW_UNRELIABLE);
	spin_unlock_irq(&die_lock);

	if (in_interrupt())
		panic("Fatal exception in interrupt");

	if (panic_on_oops)
		panic("Fatal exception");

	do_exit(err);
}