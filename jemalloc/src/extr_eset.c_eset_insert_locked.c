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
struct TYPE_4__ {scalar_t__ state; int /*<<< orphan*/  npages; int /*<<< orphan*/  lru; int /*<<< orphan*/ * heaps; int /*<<< orphan*/  bitmap; int /*<<< orphan*/  mtx; } ;
typedef  TYPE_1__ eset_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATOMIC_RELAXED ; 
 size_t LG_PAGE ; 
 int /*<<< orphan*/  assert (int) ; 
 size_t atomic_load_zu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_store_zu (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_unset (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ config_stats ; 
 int /*<<< orphan*/  eset_bitmap_info ; 
 int /*<<< orphan*/  eset_stats_add (TYPE_1__*,size_t,size_t) ; 
 scalar_t__ extent_heap_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_heap_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_list_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t extent_size_get (int /*<<< orphan*/ *) ; 
 scalar_t__ extent_state_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_assert_owner (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t sz_psz2ind (size_t) ; 
 size_t sz_psz_quantize_floor (size_t) ; 

void
eset_insert_locked(tsdn_t *tsdn, eset_t *eset, extent_t *extent) {
	malloc_mutex_assert_owner(tsdn, &eset->mtx);
	assert(extent_state_get(extent) == eset->state);

	size_t size = extent_size_get(extent);
	size_t psz = sz_psz_quantize_floor(size);
	pszind_t pind = sz_psz2ind(psz);
	if (extent_heap_empty(&eset->heaps[pind])) {
		bitmap_unset(eset->bitmap, &eset_bitmap_info,
		    (size_t)pind);
	}
	extent_heap_insert(&eset->heaps[pind], extent);

	if (config_stats) {
		eset_stats_add(eset, pind, size);
	}

	extent_list_append(&eset->lru, extent);
	size_t npages = size >> LG_PAGE;
	/*
	 * All modifications to npages hold the mutex (as asserted above), so we
	 * don't need an atomic fetch-add; we can get by with a load followed by
	 * a store.
	 */
	size_t cur_eset_npages =
	    atomic_load_zu(&eset->npages, ATOMIC_RELAXED);
	atomic_store_zu(&eset->npages, cur_eset_npages + npages,
	    ATOMIC_RELAXED);
}