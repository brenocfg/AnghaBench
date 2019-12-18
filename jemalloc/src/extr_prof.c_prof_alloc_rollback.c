#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsd_t ;
typedef  int /*<<< orphan*/  prof_tdata_t ;
struct TYPE_7__ {int prepared; TYPE_1__* tdata; } ;
typedef  TYPE_2__ prof_tctx_t ;
struct TYPE_6__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  cassert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  config_prof ; 
 int /*<<< orphan*/  malloc_mutex_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  malloc_mutex_unlock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prof_sample_threshold_update (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prof_tctx_destroy (int /*<<< orphan*/ *,TYPE_2__*) ; 
 scalar_t__ prof_tctx_should_destroy (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/ * prof_tdata_get (int /*<<< orphan*/ *,int) ; 
 scalar_t__ tsd_reentrancy_level_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsd_tsdn (int /*<<< orphan*/ *) ; 

void
prof_alloc_rollback(tsd_t *tsd, prof_tctx_t *tctx, bool updated) {
	cassert(config_prof);

	if (tsd_reentrancy_level_get(tsd) > 0) {
		assert((uintptr_t)tctx == (uintptr_t)1U);
		return;
	}

	prof_tdata_t *tdata;

	if (updated) {
		/*
		 * Compute a new sample threshold.  This isn't very important in
		 * practice, because this function is rarely executed, so the
		 * potential for sample bias is minimal except in contrived
		 * programs.
		 */
		tdata = prof_tdata_get(tsd, true);
		if (tdata != NULL) {
			prof_sample_threshold_update(tsd);
		}
	}

	if ((uintptr_t)tctx > (uintptr_t)1U) {
		malloc_mutex_lock(tsd_tsdn(tsd), tctx->tdata->lock);
		tctx->prepared = false;
		if (prof_tctx_should_destroy(tsd_tsdn(tsd), tctx)) {
			prof_tctx_destroy(tsd, tctx);
		} else {
			malloc_mutex_unlock(tsd_tsdn(tsd), tctx->tdata->lock);
		}
	}
}