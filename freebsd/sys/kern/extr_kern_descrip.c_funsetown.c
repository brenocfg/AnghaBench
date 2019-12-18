#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sigio {scalar_t__ sio_pgid; int /*<<< orphan*/  sio_ucred; struct proc* sio_proc; struct pgrp* sio_pgrp; int /*<<< orphan*/ ** sio_myref; } ;
struct proc {int /*<<< orphan*/  p_sigiolst; } ;
struct pgrp {int /*<<< orphan*/  pg_sigiolst; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_SIGIO ; 
 int /*<<< orphan*/  PGRP_LOCK (struct pgrp*) ; 
 int /*<<< orphan*/  PGRP_UNLOCK (struct pgrp*) ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int /*<<< orphan*/  SIGIO_LOCK () ; 
 int /*<<< orphan*/  SIGIO_UNLOCK () ; 
 int /*<<< orphan*/  SLIST_REMOVE (int /*<<< orphan*/ *,struct sigio*,struct sigio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct sigio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sio_pgsigio ; 

void
funsetown(struct sigio **sigiop)
{
	struct sigio *sigio;

	if (*sigiop == NULL)
		return;
	SIGIO_LOCK();
	sigio = *sigiop;
	if (sigio == NULL) {
		SIGIO_UNLOCK();
		return;
	}
	*(sigio->sio_myref) = NULL;
	if ((sigio)->sio_pgid < 0) {
		struct pgrp *pg = (sigio)->sio_pgrp;
		PGRP_LOCK(pg);
		SLIST_REMOVE(&sigio->sio_pgrp->pg_sigiolst, sigio,
			    sigio, sio_pgsigio);
		PGRP_UNLOCK(pg);
	} else {
		struct proc *p = (sigio)->sio_proc;
		PROC_LOCK(p);
		SLIST_REMOVE(&sigio->sio_proc->p_sigiolst, sigio,
			    sigio, sio_pgsigio);
		PROC_UNLOCK(p);
	}
	SIGIO_UNLOCK();
	crfree(sigio->sio_ucred);
	free(sigio, M_SIGIO);
}