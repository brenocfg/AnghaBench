#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  uc_sigmask; int /*<<< orphan*/  uc_stack; int /*<<< orphan*/  uc_link; int /*<<< orphan*/  uc_flags; } ;
struct rt_sigframe {TYPE_3__ uc; int /*<<< orphan*/  info; scalar_t__ retcode; } ;
struct pt_regs {unsigned long* areg; int depc; unsigned long threadptr; unsigned long ps; int /*<<< orphan*/  pc; } ;
struct TYPE_5__ {int sa_flags; scalar_t__ sa_handler; scalar_t__ sa_restorer; } ;
struct TYPE_6__ {TYPE_1__ sa; } ;
struct ksignal {int sig; TYPE_2__ ka; int /*<<< orphan*/  info; } ;
typedef  int /*<<< orphan*/  sigset_t ;
struct TYPE_8__ {unsigned long sas_ss_sp; unsigned long sas_ss_size; int /*<<< orphan*/  pid; int /*<<< orphan*/  comm; } ;

/* Variables and functions */
 int EFAULT ; 
 unsigned long PS_CALLINC_MASK ; 
 int PS_CALLINC_SHIFT ; 
 unsigned long PS_OWB_MASK ; 
 unsigned long PS_WOE_MASK ; 
 int SA_ONSTACK ; 
 int SA_RESTORER ; 
 int SA_SIGINFO ; 
 int __copy_to_user (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int __put_user (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int __save_altstack (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  access_ok (struct rt_sigframe*,int) ; 
 int copy_siginfo_to_user (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_4__* current ; 
 int gen_return_code (scalar_t__) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct rt_sigframe*,int /*<<< orphan*/ ) ; 
 scalar_t__ sas_ss_flags (unsigned long) ; 
 int setup_sigcontext (struct rt_sigframe*,struct pt_regs*) ; 
 int /*<<< orphan*/  start_thread (struct pt_regs*,unsigned long,unsigned long) ; 

__attribute__((used)) static int setup_frame(struct ksignal *ksig, sigset_t *set,
		       struct pt_regs *regs)
{
	struct rt_sigframe *frame;
	int err = 0, sig = ksig->sig;
	unsigned long sp, ra, tp, ps;
	unsigned int base;

	sp = regs->areg[1];

	if ((ksig->ka.sa.sa_flags & SA_ONSTACK) != 0 && sas_ss_flags(sp) == 0) {
		sp = current->sas_ss_sp + current->sas_ss_size;
	}

	frame = (void *)((sp - sizeof(*frame)) & -16ul);

	if (regs->depc > 64)
		panic ("Double exception sys_sigreturn\n");

	if (!access_ok(frame, sizeof(*frame))) {
		return -EFAULT;
	}

	if (ksig->ka.sa.sa_flags & SA_SIGINFO) {
		err |= copy_siginfo_to_user(&frame->info, &ksig->info);
	}

	/* Create the user context.  */

	err |= __put_user(0, &frame->uc.uc_flags);
	err |= __put_user(0, &frame->uc.uc_link);
	err |= __save_altstack(&frame->uc.uc_stack, regs->areg[1]);
	err |= setup_sigcontext(frame, regs);
	err |= __copy_to_user(&frame->uc.uc_sigmask, set, sizeof(*set));

	if (ksig->ka.sa.sa_flags & SA_RESTORER) {
		ra = (unsigned long)ksig->ka.sa.sa_restorer;
	} else {

		/* Create sys_rt_sigreturn syscall in stack frame */

		err |= gen_return_code(frame->retcode);

		if (err) {
			return -EFAULT;
		}
		ra = (unsigned long) frame->retcode;
	}

	/* 
	 * Create signal handler execution context.
	 * Return context not modified until this point.
	 */

	/* Set up registers for signal handler; preserve the threadptr */
	tp = regs->threadptr;
	ps = regs->ps;
	start_thread(regs, (unsigned long) ksig->ka.sa.sa_handler,
		     (unsigned long) frame);

	/* Set up a stack frame for a call4 if userspace uses windowed ABI */
	if (ps & PS_WOE_MASK) {
		base = 4;
		regs->areg[base] =
			(((unsigned long) ra) & 0x3fffffff) | 0x40000000;
		ps = (ps & ~(PS_CALLINC_MASK | PS_OWB_MASK)) |
			(1 << PS_CALLINC_SHIFT);
	} else {
		base = 0;
		regs->areg[base] = (unsigned long) ra;
	}
	regs->areg[base + 2] = (unsigned long) sig;
	regs->areg[base + 3] = (unsigned long) &frame->info;
	regs->areg[base + 4] = (unsigned long) &frame->uc;
	regs->threadptr = tp;
	regs->ps = ps;

	pr_debug("SIG rt deliver (%s:%d): signal=%d sp=%p pc=%08lx\n",
		 current->comm, current->pid, sig, frame, regs->pc);

	return 0;
}