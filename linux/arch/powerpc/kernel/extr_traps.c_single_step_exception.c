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
struct pt_regs {int /*<<< orphan*/  nip; } ;
typedef  enum ctx_state { ____Placeholder_ctx_state } ctx_state ;

/* Variables and functions */
 int /*<<< orphan*/  DIE_SSTEP ; 
 scalar_t__ NOTIFY_STOP ; 
 int /*<<< orphan*/  SIGTRAP ; 
 int /*<<< orphan*/  TRAP_TRACE ; 
 int /*<<< orphan*/  _exception (int /*<<< orphan*/ ,struct pt_regs*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_br_trace (struct pt_regs*) ; 
 int /*<<< orphan*/  clear_single_step (struct pt_regs*) ; 
 scalar_t__ debugger_sstep (struct pt_regs*) ; 
 int exception_enter () ; 
 int /*<<< orphan*/  exception_exit (int) ; 
 scalar_t__ kprobe_post_handler (struct pt_regs*) ; 
 scalar_t__ notify_die (int /*<<< orphan*/ ,char*,struct pt_regs*,int,int,int /*<<< orphan*/ ) ; 

void single_step_exception(struct pt_regs *regs)
{
	enum ctx_state prev_state = exception_enter();

	clear_single_step(regs);
	clear_br_trace(regs);

	if (kprobe_post_handler(regs))
		return;

	if (notify_die(DIE_SSTEP, "single_step", regs, 5,
					5, SIGTRAP) == NOTIFY_STOP)
		goto bail;
	if (debugger_sstep(regs))
		goto bail;

	_exception(SIGTRAP, regs, TRAP_TRACE, regs->nip);

bail:
	exception_exit(prev_state);
}