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
typedef  enum ctx_state { ____Placeholder_ctx_state } ctx_state ;

/* Variables and functions */
 int /*<<< orphan*/  DIE_TRAP ; 
 scalar_t__ NOTIFY_STOP ; 
 int /*<<< orphan*/  SIGFPE ; 
 int /*<<< orphan*/  do_fpe_common (struct pt_regs*) ; 
 int exception_enter () ; 
 int /*<<< orphan*/  exception_exit (int) ; 
 scalar_t__ notify_die (int /*<<< orphan*/ ,char*,struct pt_regs*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void do_fpieee(struct pt_regs *regs)
{
	enum ctx_state prev_state = exception_enter();

	if (notify_die(DIE_TRAP, "fpu exception ieee", regs,
		       0, 0x24, SIGFPE) == NOTIFY_STOP)
		goto out;

	do_fpe_common(regs);
out:
	exception_exit(prev_state);
}