#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pt_regs {int nip; int /*<<< orphan*/  dar; } ;
typedef  enum ctx_state { ____Placeholder_ctx_state } ctx_state ;
struct TYPE_3__ {int align_ctl; } ;
struct TYPE_4__ {TYPE_1__ thread; } ;

/* Variables and functions */
 int BUS_ADRALN ; 
 int EFAULT ; 
 int PR_UNALIGN_SIGBUS ; 
 int SEGV_ACCERR ; 
 int SIGBUS ; 
 int SIGSEGV ; 
 int TM_CAUSE_ALIGNMENT ; 
 int TM_CAUSE_PERSISTENT ; 
 int /*<<< orphan*/  _exception (int,struct pt_regs*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arch_irq_disabled_regs (struct pt_regs*) ; 
 int /*<<< orphan*/  bad_page_fault (struct pt_regs*,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  emulate_single_step (struct pt_regs*) ; 
 int exception_enter () ; 
 int /*<<< orphan*/  exception_exit (int) ; 
 int fix_alignment (struct pt_regs*) ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 scalar_t__ tm_abort_check (struct pt_regs*,int) ; 
 scalar_t__ user_mode (struct pt_regs*) ; 

void alignment_exception(struct pt_regs *regs)
{
	enum ctx_state prev_state = exception_enter();
	int sig, code, fixed = 0;

	/* We restore the interrupt state now */
	if (!arch_irq_disabled_regs(regs))
		local_irq_enable();

	if (tm_abort_check(regs, TM_CAUSE_ALIGNMENT | TM_CAUSE_PERSISTENT))
		goto bail;

	/* we don't implement logging of alignment exceptions */
	if (!(current->thread.align_ctl & PR_UNALIGN_SIGBUS))
		fixed = fix_alignment(regs);

	if (fixed == 1) {
		regs->nip += 4;	/* skip over emulated instruction */
		emulate_single_step(regs);
		goto bail;
	}

	/* Operand address was bad */
	if (fixed == -EFAULT) {
		sig = SIGSEGV;
		code = SEGV_ACCERR;
	} else {
		sig = SIGBUS;
		code = BUS_ADRALN;
	}
	if (user_mode(regs))
		_exception(sig, regs, code, regs->dar);
	else
		bad_page_fault(regs, regs->dar, sig);

bail:
	exception_exit(prev_state);
}