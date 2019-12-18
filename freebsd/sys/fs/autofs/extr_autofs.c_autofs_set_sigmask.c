#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sigset_t ;
struct TYPE_9__ {TYPE_1__* p_sigacts; } ;
struct TYPE_8__ {int /*<<< orphan*/  td_sigmask; } ;
struct TYPE_7__ {int /*<<< orphan*/  ps_mtx; int /*<<< orphan*/  ps_sigignore; } ;

/* Variables and functions */
 int /*<<< orphan*/  PROC_LOCK (TYPE_4__*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (TYPE_4__*) ; 
 int /*<<< orphan*/  SIGDELSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIGFILLSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIGISMEMBER (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIGPROCMASK_PROC_LOCKED ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 int /*<<< orphan*/ * autofs_sig_set ; 
 TYPE_4__* curproc ; 
 TYPE_2__* curthread ; 
 int /*<<< orphan*/  kern_sigprocmask (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int nitems (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
autofs_set_sigmask(sigset_t *oldset)
{
	sigset_t newset;
	int i;

	SIGFILLSET(newset);
	/* Remove the autofs set of signals from newset */
	PROC_LOCK(curproc);
	mtx_lock(&curproc->p_sigacts->ps_mtx);
	for (i = 0 ; i < nitems(autofs_sig_set); i++) {
		/*
		 * But make sure we leave the ones already masked
		 * by the process, i.e. remove the signal from the
		 * temporary signalmask only if it wasn't already
		 * in p_sigmask.
		 */
		if (!SIGISMEMBER(curthread->td_sigmask, autofs_sig_set[i]) &&
		    !SIGISMEMBER(curproc->p_sigacts->ps_sigignore,
		    autofs_sig_set[i])) {
			SIGDELSET(newset, autofs_sig_set[i]);
		}
	}
	mtx_unlock(&curproc->p_sigacts->ps_mtx);
	kern_sigprocmask(curthread, SIG_SETMASK, &newset, oldset,
	    SIGPROCMASK_PROC_LOCKED);
	PROC_UNLOCK(curproc);
}