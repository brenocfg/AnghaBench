#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct tty {scalar_t__ t_pgrp; int /*<<< orphan*/  t_bgwait; } ;
struct thread {int /*<<< orphan*/  td_sigmask; struct proc* td_proc; } ;
struct proc {scalar_t__ p_pgrp; int p_flag; TYPE_1__* p_sigacts; } ;
struct pgrp {scalar_t__ pg_jobc; } ;
struct TYPE_6__ {int ksi_signo; int /*<<< orphan*/  ksi_code; } ;
typedef  TYPE_2__ ksiginfo_t ;
struct TYPE_5__ {int /*<<< orphan*/  ps_sigignore; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  PGRP_LOCK (struct pgrp*) ; 
 int /*<<< orphan*/  PGRP_UNLOCK (struct pgrp*) ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int P_PPWAIT ; 
 scalar_t__ SIGISMEMBER (int /*<<< orphan*/ ,int) ; 
 int SIGTTIN ; 
 int SIGTTOU ; 
 int /*<<< orphan*/  SI_KERNEL ; 
 int /*<<< orphan*/  ksiginfo_init (TYPE_2__*) ; 
 int /*<<< orphan*/  pgsignal (struct pgrp*,int,int,TYPE_2__*) ; 
 int /*<<< orphan*/  tty_is_ctty (struct tty*,struct proc*) ; 
 int /*<<< orphan*/  tty_lock_assert (struct tty*,int /*<<< orphan*/ ) ; 
 int tty_wait (struct tty*,int /*<<< orphan*/ *) ; 

int
tty_wait_background(struct tty *tp, struct thread *td, int sig)
{
	struct proc *p = td->td_proc;
	struct pgrp *pg;
	ksiginfo_t ksi;
	int error;

	MPASS(sig == SIGTTIN || sig == SIGTTOU);
	tty_lock_assert(tp, MA_OWNED);

	for (;;) {
		PROC_LOCK(p);
		/*
		 * The process should only sleep, when:
		 * - This terminal is the controlling terminal
		 * - Its process group is not the foreground process
		 *   group
		 * - The parent process isn't waiting for the child to
		 *   exit
		 * - the signal to send to the process isn't masked
		 */
		if (!tty_is_ctty(tp, p) || p->p_pgrp == tp->t_pgrp) {
			/* Allow the action to happen. */
			PROC_UNLOCK(p);
			return (0);
		}

		if (SIGISMEMBER(p->p_sigacts->ps_sigignore, sig) ||
		    SIGISMEMBER(td->td_sigmask, sig)) {
			/* Only allow them in write()/ioctl(). */
			PROC_UNLOCK(p);
			return (sig == SIGTTOU ? 0 : EIO);
		}

		pg = p->p_pgrp;
		if (p->p_flag & P_PPWAIT || pg->pg_jobc == 0) {
			/* Don't allow the action to happen. */
			PROC_UNLOCK(p);
			return (EIO);
		}
		PROC_UNLOCK(p);

		/*
		 * Send the signal and sleep until we're the new
		 * foreground process group.
		 */
		if (sig != 0) {
			ksiginfo_init(&ksi);
			ksi.ksi_code = SI_KERNEL;
			ksi.ksi_signo = sig;
			sig = 0;
		}
		PGRP_LOCK(pg);
		pgsignal(pg, ksi.ksi_signo, 1, &ksi);
		PGRP_UNLOCK(pg);

		error = tty_wait(tp, &tp->t_bgwait);
		if (error)
			return (error);
	}
}