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
struct thread {struct seltd* td_sel; } ;
struct seltd {int st_flags; int /*<<< orphan*/  st_selq; struct selfd* st_free2; struct selfd* st_free1; } ;
struct selinfo {struct mtx* si_mtx; int /*<<< orphan*/  si_tdlist; } ;
struct selfd {int /*<<< orphan*/  sf_refs; struct mtx* sf_mtx; struct selinfo* sf_si; } ;
struct mtx {int dummy; } ;

/* Variables and functions */
 int SELTD_RESCAN ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct selfd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct selfd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (struct mtx*) ; 
 struct mtx* mtx_pool_find (int /*<<< orphan*/ ,struct selinfo*) ; 
 int /*<<< orphan*/  mtx_unlock (struct mtx*) ; 
 int /*<<< orphan*/  mtxpool_select ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  refcount_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sf_link ; 
 int /*<<< orphan*/  sf_threads ; 

void
selrecord(struct thread *selector, struct selinfo *sip)
{
	struct selfd *sfp;
	struct seltd *stp;
	struct mtx *mtxp;

	stp = selector->td_sel;
	/*
	 * Don't record when doing a rescan.
	 */
	if (stp->st_flags & SELTD_RESCAN)
		return;
	/*
	 * Grab one of the preallocated descriptors.
	 */
	sfp = NULL;
	if ((sfp = stp->st_free1) != NULL)
		stp->st_free1 = NULL;
	else if ((sfp = stp->st_free2) != NULL)
		stp->st_free2 = NULL;
	else
		panic("selrecord: No free selfd on selq");
	mtxp = sip->si_mtx;
	if (mtxp == NULL)
		mtxp = mtx_pool_find(mtxpool_select, sip);
	/*
	 * Initialize the sfp and queue it in the thread.
	 */
	sfp->sf_si = sip;
	sfp->sf_mtx = mtxp;
	refcount_init(&sfp->sf_refs, 2);
	STAILQ_INSERT_TAIL(&stp->st_selq, sfp, sf_link);
	/*
	 * Now that we've locked the sip, check for initialization.
	 */
	mtx_lock(mtxp);
	if (sip->si_mtx == NULL) {
		sip->si_mtx = mtxp;
		TAILQ_INIT(&sip->si_tdlist);
	}
	/*
	 * Add this thread to the list of selfds listening on this selinfo.
	 */
	TAILQ_INSERT_TAIL(&sip->si_tdlist, sfp, sf_threads);
	mtx_unlock(sip->si_mtx);
}