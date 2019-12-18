#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsd_t ;
struct TYPE_12__ {int /*<<< orphan*/  thr_uid; int /*<<< orphan*/  vec; } ;
typedef  TYPE_3__ prof_tdata_t ;
struct TYPE_13__ {TYPE_2__* tdata; TYPE_1__* gctx; } ;
typedef  TYPE_4__ prof_tctx_t ;
typedef  int /*<<< orphan*/  prof_bt_t ;
struct TYPE_14__ {size_t usize; struct TYPE_14__* next; void* free_time_ns; void* alloc_time_ns; void* free_bt_ind; void* alloc_bt_ind; void* free_thr_ind; void* alloc_thr_ind; } ;
typedef  TYPE_5__ prof_alloc_node_t ;
typedef  int /*<<< orphan*/  nstime_t ;
struct TYPE_11__ {char* thread_name; int /*<<< orphan*/  thr_uid; int /*<<< orphan*/  lock; } ;
struct TYPE_10__ {int /*<<< orphan*/  bt; } ;

/* Variables and functions */
 int /*<<< orphan*/  NSTIME_ZERO_INITIALIZER ; 
 int /*<<< orphan*/  PROF_CKH_MINITEMS ; 
 int /*<<< orphan*/  TSDN_NULL ; 
 int /*<<< orphan*/  arena_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bt_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ckh_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ iallocztm (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 
 TYPE_5__* log_alloc_first ; 
 TYPE_5__* log_alloc_last ; 
 int /*<<< orphan*/  log_bt_node_set ; 
 int /*<<< orphan*/  log_mtx ; 
 int log_tables_initialized ; 
 int /*<<< orphan*/  log_thr_node_set ; 
 int /*<<< orphan*/  malloc_mutex_assert_owner (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  malloc_mutex_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_unlock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* nstime_ns (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nstime_update (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prof_alloc_time_get (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  prof_backtrace (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prof_bt_node_hash ; 
 int /*<<< orphan*/  prof_bt_node_keycomp ; 
 void* prof_log_bt_index (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* prof_log_thr_index (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ prof_logging_state ; 
 scalar_t__ prof_logging_state_started ; 
 TYPE_3__* prof_tdata_get (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  prof_thr_node_hash ; 
 int /*<<< orphan*/  prof_thr_node_keycomp ; 
 char* prof_thread_name_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sz_size2index (size_t) ; 
 int /*<<< orphan*/  tsd_tsdn (int /*<<< orphan*/ *) ; 

void
prof_try_log(tsd_t *tsd, const void *ptr, size_t usize, prof_tctx_t *tctx) {
	malloc_mutex_assert_owner(tsd_tsdn(tsd), tctx->tdata->lock);

	prof_tdata_t *cons_tdata = prof_tdata_get(tsd, false);
	if (cons_tdata == NULL) {
		/*
		 * We decide not to log these allocations. cons_tdata will be
		 * NULL only when the current thread is in a weird state (e.g.
		 * it's being destroyed).
		 */
		return;
	}

	malloc_mutex_lock(tsd_tsdn(tsd), &log_mtx);

	if (prof_logging_state != prof_logging_state_started) {
		goto label_done;
	}

	if (!log_tables_initialized) {
		bool err1 = ckh_new(tsd, &log_bt_node_set, PROF_CKH_MINITEMS,
				prof_bt_node_hash, prof_bt_node_keycomp);
		bool err2 = ckh_new(tsd, &log_thr_node_set, PROF_CKH_MINITEMS,
				prof_thr_node_hash, prof_thr_node_keycomp);
		if (err1 || err2) {
			goto label_done;
		}
		log_tables_initialized = true;
	}

	nstime_t alloc_time = prof_alloc_time_get(tsd_tsdn(tsd), ptr);
	nstime_t free_time = NSTIME_ZERO_INITIALIZER;
	nstime_update(&free_time);

	size_t sz = sizeof(prof_alloc_node_t);
	prof_alloc_node_t *new_node = (prof_alloc_node_t *)
	    iallocztm(tsd_tsdn(tsd), sz, sz_size2index(sz), false, NULL, true,
	    arena_get(TSDN_NULL, 0, true), true);

	const char *prod_thr_name = (tctx->tdata->thread_name == NULL)?
				        "" : tctx->tdata->thread_name;
	const char *cons_thr_name = prof_thread_name_get(tsd);

	prof_bt_t bt;
	/* Initialize the backtrace, using the buffer in tdata to store it. */
	bt_init(&bt, cons_tdata->vec);
	prof_backtrace(tsd, &bt);
	prof_bt_t *cons_bt = &bt;

	/* We haven't destroyed tctx yet, so gctx should be good to read. */
	prof_bt_t *prod_bt = &tctx->gctx->bt;

	new_node->next = NULL;
	new_node->alloc_thr_ind = prof_log_thr_index(tsd, tctx->tdata->thr_uid,
				      prod_thr_name);
	new_node->free_thr_ind = prof_log_thr_index(tsd, cons_tdata->thr_uid,
				     cons_thr_name);
	new_node->alloc_bt_ind = prof_log_bt_index(tsd, prod_bt);
	new_node->free_bt_ind = prof_log_bt_index(tsd, cons_bt);
	new_node->alloc_time_ns = nstime_ns(&alloc_time);
	new_node->free_time_ns = nstime_ns(&free_time);
	new_node->usize = usize;

	if (log_alloc_first == NULL) {
		log_alloc_first = new_node;
		log_alloc_last = new_node;
	} else {
		log_alloc_last->next = new_node;
		log_alloc_last = new_node;
	}

label_done:
	malloc_mutex_unlock(tsd_tsdn(tsd), &log_mtx);
}