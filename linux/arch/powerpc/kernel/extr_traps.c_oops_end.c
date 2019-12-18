#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pt_regs {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOCKDEP_NOW_UNRELIABLE ; 
 int /*<<< orphan*/  MSEC_PER_SEC ; 
 int /*<<< orphan*/  TAINT_DIE ; 
 int TRAP (struct pt_regs*) ; 
 int /*<<< orphan*/  add_taint (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arch_spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bust_spinlocks (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crash_fadump (struct pt_regs*,char*) ; 
 int /*<<< orphan*/  crash_kexec (struct pt_regs*) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  die_lock ; 
 int /*<<< orphan*/  die_nest_count ; 
 int die_owner ; 
 int /*<<< orphan*/  do_exit (int) ; 
 scalar_t__ in_interrupt () ; 
 scalar_t__ is_global_init (TYPE_1__*) ; 
 scalar_t__ kexec_should_crash (TYPE_1__*) ; 
 int /*<<< orphan*/  mdelay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oops_exit () ; 
 int /*<<< orphan*/  panic (char*) ; 
 scalar_t__ panic_on_oops ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  raw_local_irq_restore (unsigned long) ; 

__attribute__((used)) static void oops_end(unsigned long flags, struct pt_regs *regs,
			       int signr)
{
	bust_spinlocks(0);
	add_taint(TAINT_DIE, LOCKDEP_NOW_UNRELIABLE);
	die_nest_count--;
	oops_exit();
	printk("\n");
	if (!die_nest_count) {
		/* Nest count reaches zero, release the lock. */
		die_owner = -1;
		arch_spin_unlock(&die_lock);
	}
	raw_local_irq_restore(flags);

	/*
	 * system_reset_excption handles debugger, crash dump, panic, for 0x100
	 */
	if (TRAP(regs) == 0x100)
		return;

	crash_fadump(regs, "die oops");

	if (kexec_should_crash(current))
		crash_kexec(regs);

	if (!signr)
		return;

	/*
	 * While our oops output is serialised by a spinlock, output
	 * from panic() called below can race and corrupt it. If we
	 * know we are going to panic, delay for 1 second so we have a
	 * chance to get clean backtraces from all CPUs that are oopsing.
	 */
	if (in_interrupt() || panic_on_oops || !current->pid ||
	    is_global_init(current)) {
		mdelay(MSEC_PER_SEC);
	}

	if (panic_on_oops)
		panic("Fatal exception");
	do_exit(signr);
}