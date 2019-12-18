#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint64_t ;
typedef  int /*<<< orphan*/  tsd_t ;
struct TYPE_5__ {char* thread_name; int attached; int expired; int enq; int enq_idump; int enq_gdump; int dumping; int active; int /*<<< orphan*/  bt2tctx; scalar_t__ tctx_uid_next; void* thr_discrim; void* thr_uid; int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ prof_tdata_t ;

/* Variables and functions */
 int /*<<< orphan*/  PROF_CKH_MINITEMS ; 
 int /*<<< orphan*/  TSDN_NULL ; 
 int /*<<< orphan*/  arena_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  cassert (int /*<<< orphan*/ ) ; 
 scalar_t__ ckh_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  config_prof ; 
 scalar_t__ iallocztm (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  idalloctm (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  malloc_mutex_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_unlock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prof_bt_hash ; 
 int /*<<< orphan*/  prof_bt_keycomp ; 
 int /*<<< orphan*/  prof_sample_threshold_update (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prof_tdata_mutex_choose (void*) ; 
 int /*<<< orphan*/  sz_size2index (int) ; 
 int /*<<< orphan*/  tdata_tree_insert (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  tdatas ; 
 int /*<<< orphan*/  tdatas_mtx ; 
 scalar_t__ tsd_reentrancy_level_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsd_tsdn (int /*<<< orphan*/ *) ; 

prof_tdata_t *
prof_tdata_init_impl(tsd_t *tsd, uint64_t thr_uid, uint64_t thr_discrim,
    char *thread_name, bool active, bool reset_interval) {
	assert(tsd_reentrancy_level_get(tsd) == 0);

	prof_tdata_t *tdata;

	cassert(config_prof);

	/* Initialize an empty cache for this thread. */
	tdata = (prof_tdata_t *)iallocztm(tsd_tsdn(tsd), sizeof(prof_tdata_t),
	    sz_size2index(sizeof(prof_tdata_t)), false, NULL, true,
	    arena_get(TSDN_NULL, 0, true), true);
	if (tdata == NULL) {
		return NULL;
	}

	tdata->lock = prof_tdata_mutex_choose(thr_uid);
	tdata->thr_uid = thr_uid;
	tdata->thr_discrim = thr_discrim;
	tdata->thread_name = thread_name;
	tdata->attached = true;
	tdata->expired = false;
	tdata->tctx_uid_next = 0;

	if (ckh_new(tsd, &tdata->bt2tctx, PROF_CKH_MINITEMS, prof_bt_hash,
	    prof_bt_keycomp)) {
		idalloctm(tsd_tsdn(tsd), tdata, NULL, NULL, true, true);
		return NULL;
	}

	if (reset_interval) {
		prof_sample_threshold_update(tsd);
	}

	tdata->enq = false;
	tdata->enq_idump = false;
	tdata->enq_gdump = false;

	tdata->dumping = false;
	tdata->active = active;

	malloc_mutex_lock(tsd_tsdn(tsd), &tdatas_mtx);
	tdata_tree_insert(&tdatas, tdata);
	malloc_mutex_unlock(tsd_tsdn(tsd), &tdatas_mtx);

	return tdata;
}