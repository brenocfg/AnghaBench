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
struct task_struct {int dummy; } ;
struct pt_regs {int /*<<< orphan*/  user_regs; } ;
struct TYPE_4__ {int sa_flags; } ;
struct TYPE_3__ {TYPE_2__ sa; } ;
struct ksignal {int sig; TYPE_1__ ka; } ;
typedef  int /*<<< orphan*/  sigset_t ;

/* Variables and functions */
 int SA_SIGINFO ; 
 int compat_setup_frame (int,struct ksignal*,int /*<<< orphan*/ *,struct pt_regs*) ; 
 int compat_setup_rt_frame (int,struct ksignal*,int /*<<< orphan*/ *,struct pt_regs*) ; 
 struct task_struct* current ; 
 scalar_t__ is_compat_task () ; 
 int /*<<< orphan*/  rseq_signal_deliver (struct ksignal*,struct pt_regs*) ; 
 int setup_rt_frame (int,struct ksignal*,int /*<<< orphan*/ *,struct pt_regs*) ; 
 int /*<<< orphan*/ * sigmask_to_save () ; 
 int /*<<< orphan*/  signal_setup_done (int,struct ksignal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  user_fastforward_single_step (struct task_struct*) ; 
 int /*<<< orphan*/  valid_user_regs (int /*<<< orphan*/ *,struct task_struct*) ; 

__attribute__((used)) static void handle_signal(struct ksignal *ksig, struct pt_regs *regs)
{
	struct task_struct *tsk = current;
	sigset_t *oldset = sigmask_to_save();
	int usig = ksig->sig;
	int ret;

	rseq_signal_deliver(ksig, regs);

	/*
	 * Set up the stack frame
	 */
	if (is_compat_task()) {
		if (ksig->ka.sa.sa_flags & SA_SIGINFO)
			ret = compat_setup_rt_frame(usig, ksig, oldset, regs);
		else
			ret = compat_setup_frame(usig, ksig, oldset, regs);
	} else {
		ret = setup_rt_frame(usig, ksig, oldset, regs);
	}

	/*
	 * Check that the resulting registers are actually sane.
	 */
	ret |= !valid_user_regs(&regs->user_regs, current);

	/*
	 * Fast forward the stepping logic so we step into the signal
	 * handler.
	 */
	if (!ret)
		user_fastforward_single_step(tsk);

	signal_setup_done(ret, ksig, 0);
}