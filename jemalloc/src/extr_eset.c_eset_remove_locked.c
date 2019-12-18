#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsdn_t ;
typedef  size_t pszind_t ;
typedef  int /*<<< orphan*/  extent_t ;
struct TYPE_4__ {scalar_t__ state; int /*<<< orphan*/  npages; int /*<<< orphan*/  lru; int /*<<< orphan*/  bitmap; int /*<<< orphan*/ * heaps; int /*<<< orphan*/  mtx; } ;
typedef  TYPE_1__ eset_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATOMIC_RELAXED ; 
 size_t LG_PAGE ; 
 int /*<<< orphan*/  assert (int) ; 
 size_t atomic_load_zu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_store_zu (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ config_stats ; 
 int /*<<< orphan*/  eset_bitmap_info ; 
 int /*<<< orphan*/  eset_stats_sub (TYPE_1__*,size_t,size_t) ; 
 scalar_t__ extent_heap_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_heap_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_list_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t extent_size_get (int /*<<< orphan*/ *) ; 
 scalar_t__ extent_state_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_assert_owner (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t sz_psz2ind (size_t) ; 
 size_t sz_psz_quantize_floor (size_t) ; 

void
eset_remove_locked(tsdn_t *tsdn, eset_t *eset, extent_t *extent) {
	malloc_mutex_assert_owner(tsdn, &eset->mtx);
	assert(extent_state_get(extent) == eset->state);

	size_t size = extent_size_get(extent);
	size_t psz = sz_psz_quantize_floor(size);
	pszind_t pind = sz_psz2ind(psz);
	extent_heap_remove(&eset->heaps[pind], extent);

	if (config_stats) {
		eset_stats_sub(eset, pind, size);
	}

	if (extent_heap_empty(&eset->heaps[pind])) {
		bitmap_set(eset->bitmap, &eset_bitmap_info,
		    (size_t)pind);
	}
	extent_list_remove(&eset->lru, extent);
	size_t npages = size >> LG_PAGE;
	/*
	 * As in eset_insert_locked, we hold eset->mtx and so don't need atomic
	 * operations for updating eset->npages.
	 */
	size_t cur_extents_npages =
	    atomic_load_zu(&eset->npages, ATOMIC_RELAXED);
	assert(cur_extents_npages >= npages);
	atomic_store_zu(&eset->npages,
	    cur_extents_npages - (size >> LG_PAGE), ATOMIC_RELAXED);
}