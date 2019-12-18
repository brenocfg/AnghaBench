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
struct pt_regs {int int_code; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIE_OOPS ; 
 int /*<<< orphan*/  LOCKDEP_NOW_UNRELIABLE ; 
 int /*<<< orphan*/  SIGSEGV ; 
 int /*<<< orphan*/  TAINT_DIE ; 
 int /*<<< orphan*/  add_taint (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bust_spinlocks (int) ; 
 int /*<<< orphan*/  console_verbose () ; 
 scalar_t__ debug_pagealloc_enabled () ; 
 int /*<<< orphan*/  debug_stop_all () ; 
 int /*<<< orphan*/  die_lock ; 
 int /*<<< orphan*/  do_exit (int /*<<< orphan*/ ) ; 
 scalar_t__ in_interrupt () ; 
 int /*<<< orphan*/  lgr_info_log () ; 
 int /*<<< orphan*/  notify_die (int /*<<< orphan*/ ,char const*,struct pt_regs*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oops_enter () ; 
 int /*<<< orphan*/  oops_exit () ; 
 int /*<<< orphan*/  panic (char*) ; 
 scalar_t__ panic_on_oops ; 
 int /*<<< orphan*/  pr_cont (char*) ; 
 int /*<<< orphan*/  print_modules () ; 
 int /*<<< orphan*/  printk (char*,char const*,int,int,int) ; 
 int /*<<< orphan*/  show_regs (struct pt_regs*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void die(struct pt_regs *regs, const char *str)
{
	static int die_counter;

	oops_enter();
	lgr_info_log();
	debug_stop_all();
	console_verbose();
	spin_lock_irq(&die_lock);
	bust_spinlocks(1);
	printk("%s: %04x ilc:%d [#%d] ", str, regs->int_code & 0xffff,
	       regs->int_code >> 17, ++die_counter);
#ifdef CONFIG_PREEMPT
	pr_cont("PREEMPT ");
#endif
	pr_cont("SMP ");
	if (debug_pagealloc_enabled())
		pr_cont("DEBUG_PAGEALLOC");
	pr_cont("\n");
	notify_die(DIE_OOPS, str, regs, 0, regs->int_code & 0xffff, SIGSEGV);
	print_modules();
	show_regs(regs);
	bust_spinlocks(0);
	add_taint(TAINT_DIE, LOCKDEP_NOW_UNRELIABLE);
	spin_unlock_irq(&die_lock);
	if (in_interrupt())
		panic("Fatal exception in interrupt");
	if (panic_on_oops)
		panic("Fatal exception: panic_on_oops");
	oops_exit();
	do_exit(SIGSEGV);
}