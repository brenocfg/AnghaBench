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
 scalar_t__ DBG_HOOK_HANDLED ; 
 int /*<<< orphan*/  TRAP_TRACE ; 
 scalar_t__ call_step_hook (struct pt_regs*,unsigned int) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  reinstall_suspended_bps (struct pt_regs*) ; 
 int /*<<< orphan*/  send_user_sigtrap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_regs_spsr_ss (struct pt_regs*) ; 
 scalar_t__ user_mode (struct pt_regs*) ; 
 int /*<<< orphan*/  user_rewind_single_step (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int single_step_handler(unsigned long unused, unsigned int esr,
			       struct pt_regs *regs)
{
	bool handler_found = false;

	/*
	 * If we are stepping a pending breakpoint, call the hw_breakpoint
	 * handler first.
	 */
	if (!reinstall_suspended_bps(regs))
		return 0;

	if (!handler_found && call_step_hook(regs, esr) == DBG_HOOK_HANDLED)
		handler_found = true;

	if (!handler_found && user_mode(regs)) {
		send_user_sigtrap(TRAP_TRACE);

		/*
		 * ptrace will disable single step unless explicitly
		 * asked to re-enable it. For other clients, it makes
		 * sense to leave it enabled (i.e. rewind the controls
		 * to the active-not-pending state).
		 */
		user_rewind_single_step(current);
	} else if (!handler_found) {
		pr_warn("Unexpected kernel single-step exception at EL1\n");
		/*
		 * Re-enable stepping since we know that we will be
		 * returning to regs.
		 */
		set_regs_spsr_ss(regs);
	}

	return 0;
}