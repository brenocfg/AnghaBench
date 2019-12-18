#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tty {TYPE_1__* t_session; int /*<<< orphan*/  t_flags; } ;
struct proc {int dummy; } ;
struct TYPE_2__ {struct proc* s_leader; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int NSIG ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int /*<<< orphan*/  TF_STOPPED ; 
 int /*<<< orphan*/  kern_psignal (struct proc*,int) ; 
 int /*<<< orphan*/  tty_lock_assert (struct tty*,int /*<<< orphan*/ ) ; 

void
tty_signal_sessleader(struct tty *tp, int sig)
{
	struct proc *p;

	tty_lock_assert(tp, MA_OWNED);
	MPASS(sig >= 1 && sig < NSIG);

	/* Make signals start output again. */
	tp->t_flags &= ~TF_STOPPED;

	if (tp->t_session != NULL && tp->t_session->s_leader != NULL) {
		p = tp->t_session->s_leader;
		PROC_LOCK(p);
		kern_psignal(p, sig);
		PROC_UNLOCK(p);
	}
}