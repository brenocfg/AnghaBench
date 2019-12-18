#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsd_t ;
struct TYPE_14__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  bt2tctx; } ;
typedef  TYPE_2__ prof_tdata_t ;
struct TYPE_13__ {scalar_t__ curobjs; scalar_t__ curbytes; scalar_t__ accumobjs; scalar_t__ accumbytes; } ;
struct TYPE_15__ {int state; TYPE_2__* tdata; TYPE_1__ cnts; TYPE_4__* gctx; } ;
typedef  TYPE_3__ prof_tctx_t ;
struct TYPE_16__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  nlimbo; int /*<<< orphan*/  tctxs; int /*<<< orphan*/  bt; } ;
typedef  TYPE_4__ prof_gctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ckh_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idalloctm (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  malloc_mutex_assert_not_owner (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  malloc_mutex_assert_owner (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  malloc_mutex_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  malloc_mutex_unlock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  not_reached () ; 
 int /*<<< orphan*/  opt_prof_accum ; 
 int /*<<< orphan*/  prof_gctx_should_destroy (TYPE_4__*) ; 
 int /*<<< orphan*/  prof_gctx_try_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_4__*,TYPE_2__*) ; 
#define  prof_tctx_state_dumping 129 
#define  prof_tctx_state_nominal 128 
 int prof_tctx_state_purgatory ; 
 int /*<<< orphan*/  prof_tdata_destroy (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int /*<<< orphan*/  prof_tdata_get (int /*<<< orphan*/ *,int) ; 
 int prof_tdata_should_destroy (int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 int /*<<< orphan*/  tctx_tree_remove (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  tsd_tsdn (int /*<<< orphan*/ *) ; 

void
prof_tctx_destroy(tsd_t *tsd, prof_tctx_t *tctx) {
	prof_tdata_t *tdata = tctx->tdata;
	prof_gctx_t *gctx = tctx->gctx;
	bool destroy_tdata, destroy_tctx, destroy_gctx;

	malloc_mutex_assert_owner(tsd_tsdn(tsd), tctx->tdata->lock);

	assert(tctx->cnts.curobjs == 0);
	assert(tctx->cnts.curbytes == 0);
	assert(!opt_prof_accum);
	assert(tctx->cnts.accumobjs == 0);
	assert(tctx->cnts.accumbytes == 0);

	ckh_remove(tsd, &tdata->bt2tctx, &gctx->bt, NULL, NULL);
	destroy_tdata = prof_tdata_should_destroy(tsd_tsdn(tsd), tdata, false);
	malloc_mutex_unlock(tsd_tsdn(tsd), tdata->lock);

	malloc_mutex_lock(tsd_tsdn(tsd), gctx->lock);
	switch (tctx->state) {
	case prof_tctx_state_nominal:
		tctx_tree_remove(&gctx->tctxs, tctx);
		destroy_tctx = true;
		if (prof_gctx_should_destroy(gctx)) {
			/*
			 * Increment gctx->nlimbo in order to keep another
			 * thread from winning the race to destroy gctx while
			 * this one has gctx->lock dropped.  Without this, it
			 * would be possible for another thread to:
			 *
			 * 1) Sample an allocation associated with gctx.
			 * 2) Deallocate the sampled object.
			 * 3) Successfully prof_gctx_try_destroy(gctx).
			 *
			 * The result would be that gctx no longer exists by the
			 * time this thread accesses it in
			 * prof_gctx_try_destroy().
			 */
			gctx->nlimbo++;
			destroy_gctx = true;
		} else {
			destroy_gctx = false;
		}
		break;
	case prof_tctx_state_dumping:
		/*
		 * A dumping thread needs tctx to remain valid until dumping
		 * has finished.  Change state such that the dumping thread will
		 * complete destruction during a late dump iteration phase.
		 */
		tctx->state = prof_tctx_state_purgatory;
		destroy_tctx = false;
		destroy_gctx = false;
		break;
	default:
		not_reached();
		destroy_tctx = false;
		destroy_gctx = false;
	}
	malloc_mutex_unlock(tsd_tsdn(tsd), gctx->lock);
	if (destroy_gctx) {
		prof_gctx_try_destroy(tsd, prof_tdata_get(tsd, false), gctx,
		    tdata);
	}

	malloc_mutex_assert_not_owner(tsd_tsdn(tsd), tctx->tdata->lock);

	if (destroy_tdata) {
		prof_tdata_destroy(tsd, tdata, false);
	}

	if (destroy_tctx) {
		idalloctm(tsd_tsdn(tsd), tctx, NULL, NULL, true, true);
	}
}