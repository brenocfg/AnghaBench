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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  tsd_t ;
typedef  int /*<<< orphan*/  prof_tdata_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 size_t lg_prof_sample ; 
 int /*<<< orphan*/  malloc_mutex_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_unlock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prof_dump_mtx ; 
 int /*<<< orphan*/  prof_tdata_destroy_locked (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  prof_tdata_reset_iter ; 
 int /*<<< orphan*/ * tdata_tree_iter (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/ * tdata_tree_next (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tdatas ; 
 int /*<<< orphan*/  tdatas_mtx ; 
 int /*<<< orphan*/  tsd_tsdn (int /*<<< orphan*/ *) ; 

void
prof_reset(tsd_t *tsd, size_t lg_sample) {
	prof_tdata_t *next;

	assert(lg_sample < (sizeof(uint64_t) << 3));

	malloc_mutex_lock(tsd_tsdn(tsd), &prof_dump_mtx);
	malloc_mutex_lock(tsd_tsdn(tsd), &tdatas_mtx);

	lg_prof_sample = lg_sample;

	next = NULL;
	do {
		prof_tdata_t *to_destroy = tdata_tree_iter(&tdatas, next,
		    prof_tdata_reset_iter, (void *)tsd);
		if (to_destroy != NULL) {
			next = tdata_tree_next(&tdatas, to_destroy);
			prof_tdata_destroy_locked(tsd, to_destroy, false);
		} else {
			next = NULL;
		}
	} while (next != NULL);

	malloc_mutex_unlock(tsd_tsdn(tsd), &tdatas_mtx);
	malloc_mutex_unlock(tsd_tsdn(tsd), &prof_dump_mtx);
}