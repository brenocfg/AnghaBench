#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct pt_regs {int* regs; int cp0_epc; } ;
struct mips_abi {int (* setup_rt_frame ) (void*,struct ksignal*,struct pt_regs*,int /*<<< orphan*/ *) ;int (* setup_frame ) (void*,struct ksignal*,struct pt_regs*,int /*<<< orphan*/ *) ;TYPE_5__* vdso; } ;
struct TYPE_11__ {int sa_flags; } ;
struct TYPE_13__ {TYPE_4__ sa; } ;
struct ksignal {TYPE_6__ ka; } ;
typedef  int /*<<< orphan*/  sigset_t ;
struct TYPE_8__ {struct mips_abi* abi; } ;
struct TYPE_14__ {TYPE_3__* mm; TYPE_1__ thread; } ;
struct TYPE_12__ {int off_rt_sigreturn; int off_sigreturn; } ;
struct TYPE_9__ {void* vdso; } ;
struct TYPE_10__ {TYPE_2__ context; } ;

/* Variables and functions */
 void* EINTR ; 
#define  ERESTARTNOHAND 131 
#define  ERESTARTNOINTR 130 
#define  ERESTARTSYS 129 
#define  ERESTART_RESTARTBLOCK 128 
 int SA_RESTART ; 
 TYPE_7__* current ; 
 int /*<<< orphan*/  dsemul_thread_rollback (struct pt_regs*) ; 
 int /*<<< orphan*/  rseq_signal_deliver (struct ksignal*,struct pt_regs*) ; 
 scalar_t__ sig_uses_siginfo (TYPE_6__*,struct mips_abi*) ; 
 int /*<<< orphan*/ * sigmask_to_save () ; 
 int /*<<< orphan*/  signal_setup_done (int,struct ksignal*,int /*<<< orphan*/ ) ; 
 int stub1 (void*,struct ksignal*,struct pt_regs*,int /*<<< orphan*/ *) ; 
 int stub2 (void*,struct ksignal*,struct pt_regs*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void handle_signal(struct ksignal *ksig, struct pt_regs *regs)
{
	sigset_t *oldset = sigmask_to_save();
	int ret;
	struct mips_abi *abi = current->thread.abi;
	void *vdso = current->mm->context.vdso;

	/*
	 * If we were emulating a delay slot instruction, exit that frame such
	 * that addresses in the sigframe are as expected for userland and we
	 * don't have a problem if we reuse the thread's frame for an
	 * instruction within the signal handler.
	 */
	dsemul_thread_rollback(regs);

	if (regs->regs[0]) {
		switch(regs->regs[2]) {
		case ERESTART_RESTARTBLOCK:
		case ERESTARTNOHAND:
			regs->regs[2] = EINTR;
			break;
		case ERESTARTSYS:
			if (!(ksig->ka.sa.sa_flags & SA_RESTART)) {
				regs->regs[2] = EINTR;
				break;
			}
		/* fallthrough */
		case ERESTARTNOINTR:
			regs->regs[7] = regs->regs[26];
			regs->regs[2] = regs->regs[0];
			regs->cp0_epc -= 4;
		}

		regs->regs[0] = 0;		/* Don't deal with this again.	*/
	}

	rseq_signal_deliver(ksig, regs);

	if (sig_uses_siginfo(&ksig->ka, abi))
		ret = abi->setup_rt_frame(vdso + abi->vdso->off_rt_sigreturn,
					  ksig, regs, oldset);
	else
		ret = abi->setup_frame(vdso + abi->vdso->off_sigreturn,
				       ksig, regs, oldset);

	signal_setup_done(ret, ksig, 0);
}