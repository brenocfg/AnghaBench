#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  uc_sigmask; int /*<<< orphan*/  uc_stack; int /*<<< orphan*/  uc_link; int /*<<< orphan*/  uc_flags; } ;
struct rt_sigframe {TYPE_3__ uc; int /*<<< orphan*/  info; } ;
struct pt_regs {unsigned long sp; unsigned long ra; unsigned long r4; unsigned long r5; unsigned long r6; unsigned long ea; } ;
struct TYPE_4__ {int sa_flags; scalar_t__ sa_handler; } ;
struct TYPE_5__ {TYPE_1__ sa; } ;
struct ksignal {scalar_t__ sig; TYPE_2__ ka; int /*<<< orphan*/  info; } ;
typedef  int /*<<< orphan*/  sigset_t ;

/* Variables and functions */
 int EFAULT ; 
 int SA_SIGINFO ; 
 int __put_user (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int __save_altstack (int /*<<< orphan*/ *,unsigned long) ; 
 int copy_siginfo_to_user (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int copy_to_user (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  force_sigsegv (scalar_t__) ; 
 struct rt_sigframe* get_sigframe (struct ksignal*,struct pt_regs*,int) ; 
 int rt_setup_ucontext (TYPE_3__*,struct pt_regs*) ; 

__attribute__((used)) static int setup_rt_frame(struct ksignal *ksig, sigset_t *set,
			  struct pt_regs *regs)
{
	struct rt_sigframe *frame;
	int err = 0;

	frame = get_sigframe(ksig, regs, sizeof(*frame));

	if (ksig->ka.sa.sa_flags & SA_SIGINFO)
		err |= copy_siginfo_to_user(&frame->info, &ksig->info);

	/* Create the ucontext.  */
	err |= __put_user(0, &frame->uc.uc_flags);
	err |= __put_user(0, &frame->uc.uc_link);
	err |= __save_altstack(&frame->uc.uc_stack, regs->sp);
	err |= rt_setup_ucontext(&frame->uc, regs);
	err |= copy_to_user(&frame->uc.uc_sigmask, set, sizeof(*set));

	if (err)
		goto give_sigsegv;

	/* Set up to return from userspace; jump to fixed address sigreturn
	   trampoline on kuser page.  */
	regs->ra = (unsigned long) (0x1044);

	/* Set up registers for signal handler */
	regs->sp = (unsigned long) frame;
	regs->r4 = (unsigned long) ksig->sig;
	regs->r5 = (unsigned long) &frame->info;
	regs->r6 = (unsigned long) &frame->uc;
	regs->ea = (unsigned long) ksig->ka.sa.sa_handler;
	return 0;

give_sigsegv:
	force_sigsegv(ksig->sig);
	return -EFAULT;
}