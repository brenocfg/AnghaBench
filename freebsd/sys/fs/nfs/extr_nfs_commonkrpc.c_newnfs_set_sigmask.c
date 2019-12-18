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
struct thread {int /*<<< orphan*/  td_sigmask; struct proc* td_proc; } ;
struct proc {TYPE_1__* p_sigacts; } ;
typedef  int /*<<< orphan*/  sigset_t ;
struct TYPE_2__ {int /*<<< orphan*/  ps_mtx; int /*<<< orphan*/  ps_sigignore; } ;

/* Variables and functions */
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int /*<<< orphan*/  SIGDELSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIGFILLSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIGISMEMBER (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIGPROCMASK_PROC_LOCKED ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  kern_sigprocmask (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * newnfs_sig_set ; 
 int nitems (int /*<<< orphan*/ *) ; 

void
newnfs_set_sigmask(struct thread *td, sigset_t *oldset)
{
	sigset_t newset;
	int i;
	struct proc *p;
	
	SIGFILLSET(newset);
	if (td == NULL)
		td = curthread; /* XXX */
	p = td->td_proc;
	/* Remove the NFS set of signals from newset */
	PROC_LOCK(p);
	mtx_lock(&p->p_sigacts->ps_mtx);
	for (i = 0 ; i < nitems(newnfs_sig_set); i++) {
		/*
		 * But make sure we leave the ones already masked
		 * by the process, ie. remove the signal from the
		 * temporary signalmask only if it wasn't already
		 * in p_sigmask.
		 */
		if (!SIGISMEMBER(td->td_sigmask, newnfs_sig_set[i]) &&
		    !SIGISMEMBER(p->p_sigacts->ps_sigignore, newnfs_sig_set[i]))
			SIGDELSET(newset, newnfs_sig_set[i]);
	}
	mtx_unlock(&p->p_sigacts->ps_mtx);
	kern_sigprocmask(td, SIG_SETMASK, &newset, oldset,
	    SIGPROCMASK_PROC_LOCKED);
	PROC_UNLOCK(p);
}