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
struct sigiolst {int dummy; } ;
struct sigio {scalar_t__ sio_pgid; int /*<<< orphan*/  sio_ucred; struct proc* sio_proc; struct pgrp* sio_pgrp; int /*<<< orphan*/ ** sio_myref; } ;
struct proc {int /*<<< orphan*/  p_sigiolst; } ;
struct pgrp {int /*<<< orphan*/  pg_sigiolst; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MA_NOTOWNED ; 
 int /*<<< orphan*/  M_SIGIO ; 
 int /*<<< orphan*/  PGRP_LOCK (struct pgrp*) ; 
 int /*<<< orphan*/  PGRP_LOCK_ASSERT (struct pgrp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PGRP_UNLOCK (struct pgrp*) ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_LOCK_ASSERT (struct proc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int /*<<< orphan*/  SIGIO_LOCK () ; 
 int /*<<< orphan*/  SIGIO_UNLOCK () ; 
 struct sigio* SLIST_FIRST (struct sigiolst*) ; 
 int /*<<< orphan*/  SLIST_REMOVE (int /*<<< orphan*/ *,struct sigio*,struct sigio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct sigio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sio_pgsigio ; 

void
funsetownlst(struct sigiolst *sigiolst)
{
	struct proc *p;
	struct pgrp *pg;
	struct sigio *sigio;

	sigio = SLIST_FIRST(sigiolst);
	if (sigio == NULL)
		return;
	p = NULL;
	pg = NULL;

	/*
	 * Every entry of the list should belong
	 * to a single proc or pgrp.
	 */
	if (sigio->sio_pgid < 0) {
		pg = sigio->sio_pgrp;
		PGRP_LOCK_ASSERT(pg, MA_NOTOWNED);
	} else /* if (sigio->sio_pgid > 0) */ {
		p = sigio->sio_proc;
		PROC_LOCK_ASSERT(p, MA_NOTOWNED);
	}

	SIGIO_LOCK();
	while ((sigio = SLIST_FIRST(sigiolst)) != NULL) {
		*(sigio->sio_myref) = NULL;
		if (pg != NULL) {
			KASSERT(sigio->sio_pgid < 0,
			    ("Proc sigio in pgrp sigio list"));
			KASSERT(sigio->sio_pgrp == pg,
			    ("Bogus pgrp in sigio list"));
			PGRP_LOCK(pg);
			SLIST_REMOVE(&pg->pg_sigiolst, sigio, sigio,
			    sio_pgsigio);
			PGRP_UNLOCK(pg);
		} else /* if (p != NULL) */ {
			KASSERT(sigio->sio_pgid > 0,
			    ("Pgrp sigio in proc sigio list"));
			KASSERT(sigio->sio_proc == p,
			    ("Bogus proc in sigio list"));
			PROC_LOCK(p);
			SLIST_REMOVE(&p->p_sigiolst, sigio, sigio,
			    sio_pgsigio);
			PROC_UNLOCK(p);
		}
		SIGIO_UNLOCK();
		crfree(sigio->sio_ucred);
		free(sigio, M_SIGIO);
		SIGIO_LOCK();
	}
	SIGIO_UNLOCK();
}