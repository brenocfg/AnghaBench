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
typedef  int /*<<< orphan*/  tsd_t ;

/* Variables and functions */
 int /*<<< orphan*/  PROF_CKH_MINITEMS ; 
 int /*<<< orphan*/  WITNESS_RANK_PROF_LOG ; 
 int /*<<< orphan*/  abort () ; 
 scalar_t__ atexit (int /*<<< orphan*/ ) ; 
 scalar_t__ ckh_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_bt_node_set ; 
 int /*<<< orphan*/  log_mtx ; 
 int log_tables_initialized ; 
 int /*<<< orphan*/  log_thr_node_set ; 
 scalar_t__ malloc_mutex_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  malloc_mutex_rank_exclusive ; 
 int /*<<< orphan*/  malloc_write (char*) ; 
 scalar_t__ opt_abort ; 
 scalar_t__ opt_prof_log ; 
 int /*<<< orphan*/  prof_bt_node_hash ; 
 int /*<<< orphan*/  prof_bt_node_keycomp ; 
 int /*<<< orphan*/  prof_log_start (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prof_log_stop_final ; 
 int /*<<< orphan*/  prof_thr_node_hash ; 
 int /*<<< orphan*/  prof_thr_node_keycomp ; 
 int /*<<< orphan*/  tsd_tsdn (int /*<<< orphan*/ *) ; 

bool prof_log_init(tsd_t *tsd) {
	if (opt_prof_log) {
		prof_log_start(tsd_tsdn(tsd), NULL);
	}

	if (atexit(prof_log_stop_final) != 0) {
		malloc_write("<jemalloc>: Error in atexit() "
			     "for logging\n");
		if (opt_abort) {
			abort();
		}
	}

	if (malloc_mutex_init(&log_mtx, "prof_log",
	    WITNESS_RANK_PROF_LOG, malloc_mutex_rank_exclusive)) {
		return true;
	}

	if (ckh_new(tsd, &log_bt_node_set, PROF_CKH_MINITEMS,
	    prof_bt_node_hash, prof_bt_node_keycomp)) {
		return true;
	}

	if (ckh_new(tsd, &log_thr_node_set, PROF_CKH_MINITEMS,
	    prof_thr_node_hash, prof_thr_node_keycomp)) {
		return true;
	}

	log_tables_initialized = true;
	return false;
}