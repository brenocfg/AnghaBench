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
struct sigio {int /*<<< orphan*/  sio_ucred; struct pgrp* sio_pgrp; struct proc* sio_proc; struct sigio** sio_myref; int /*<<< orphan*/  sio_pgid; } ;
struct proc {scalar_t__ p_session; int p_flag; int /*<<< orphan*/  p_sigiolst; } ;
struct pgrp {scalar_t__ pg_session; int /*<<< orphan*/  pg_sigiolst; } ;
typedef  int /*<<< orphan*/  pid_t ;
struct TYPE_4__ {TYPE_1__* td_proc; int /*<<< orphan*/  td_ucred; } ;
struct TYPE_3__ {scalar_t__ p_session; } ;

/* Variables and functions */
 int EPERM ; 
 int ESRCH ; 
 int /*<<< orphan*/  M_SIGIO ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  PGRP_LOCK (struct pgrp*) ; 
 int /*<<< orphan*/  PGRP_UNLOCK (struct pgrp*) ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int P_WEXIT ; 
 int /*<<< orphan*/  SIGIO_LOCK () ; 
 int /*<<< orphan*/  SIGIO_UNLOCK () ; 
 int /*<<< orphan*/  SLIST_INSERT_HEAD (int /*<<< orphan*/ *,struct sigio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crhold (int /*<<< orphan*/ ) ; 
 TYPE_2__* curthread ; 
 int /*<<< orphan*/  free (struct sigio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  funsetown (struct sigio**) ; 
 struct sigio* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct proc* pfind (int /*<<< orphan*/ ) ; 
 struct pgrp* pgfind (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proctree_lock ; 
 int /*<<< orphan*/  sio_pgsigio ; 
 int /*<<< orphan*/  sx_slock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_sunlock (int /*<<< orphan*/ *) ; 

int
fsetown(pid_t pgid, struct sigio **sigiop)
{
	struct proc *proc;
	struct pgrp *pgrp;
	struct sigio *sigio;
	int ret;

	if (pgid == 0) {
		funsetown(sigiop);
		return (0);
	}

	ret = 0;

	/* Allocate and fill in the new sigio out of locks. */
	sigio = malloc(sizeof(struct sigio), M_SIGIO, M_WAITOK);
	sigio->sio_pgid = pgid;
	sigio->sio_ucred = crhold(curthread->td_ucred);
	sigio->sio_myref = sigiop;

	sx_slock(&proctree_lock);
	if (pgid > 0) {
		proc = pfind(pgid);
		if (proc == NULL) {
			ret = ESRCH;
			goto fail;
		}

		/*
		 * Policy - Don't allow a process to FSETOWN a process
		 * in another session.
		 *
		 * Remove this test to allow maximum flexibility or
		 * restrict FSETOWN to the current process or process
		 * group for maximum safety.
		 */
		PROC_UNLOCK(proc);
		if (proc->p_session != curthread->td_proc->p_session) {
			ret = EPERM;
			goto fail;
		}

		pgrp = NULL;
	} else /* if (pgid < 0) */ {
		pgrp = pgfind(-pgid);
		if (pgrp == NULL) {
			ret = ESRCH;
			goto fail;
		}
		PGRP_UNLOCK(pgrp);

		/*
		 * Policy - Don't allow a process to FSETOWN a process
		 * in another session.
		 *
		 * Remove this test to allow maximum flexibility or
		 * restrict FSETOWN to the current process or process
		 * group for maximum safety.
		 */
		if (pgrp->pg_session != curthread->td_proc->p_session) {
			ret = EPERM;
			goto fail;
		}

		proc = NULL;
	}
	funsetown(sigiop);
	if (pgid > 0) {
		PROC_LOCK(proc);
		/*
		 * Since funsetownlst() is called without the proctree
		 * locked, we need to check for P_WEXIT.
		 * XXX: is ESRCH correct?
		 */
		if ((proc->p_flag & P_WEXIT) != 0) {
			PROC_UNLOCK(proc);
			ret = ESRCH;
			goto fail;
		}
		SLIST_INSERT_HEAD(&proc->p_sigiolst, sigio, sio_pgsigio);
		sigio->sio_proc = proc;
		PROC_UNLOCK(proc);
	} else {
		PGRP_LOCK(pgrp);
		SLIST_INSERT_HEAD(&pgrp->pg_sigiolst, sigio, sio_pgsigio);
		sigio->sio_pgrp = pgrp;
		PGRP_UNLOCK(pgrp);
	}
	sx_sunlock(&proctree_lock);
	SIGIO_LOCK();
	*sigiop = sigio;
	SIGIO_UNLOCK();
	return (0);

fail:
	sx_sunlock(&proctree_lock);
	crfree(sigio->sio_ucred);
	free(sigio, M_SIGIO);
	return (ret);
}