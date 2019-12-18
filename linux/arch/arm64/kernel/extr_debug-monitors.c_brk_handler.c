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
 int EFAULT ; 
 int /*<<< orphan*/  TRAP_BRKPT ; 
 scalar_t__ call_break_hook (struct pt_regs*,unsigned int) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  send_user_sigtrap (int /*<<< orphan*/ ) ; 
 scalar_t__ user_mode (struct pt_regs*) ; 

__attribute__((used)) static int brk_handler(unsigned long unused, unsigned int esr,
		       struct pt_regs *regs)
{
	if (call_break_hook(regs, esr) == DBG_HOOK_HANDLED)
		return 0;

	if (user_mode(regs)) {
		send_user_sigtrap(TRAP_BRKPT);
	} else {
		pr_warn("Unexpected kernel BRK exception at EL1\n");
		return -EFAULT;
	}

	return 0;
}