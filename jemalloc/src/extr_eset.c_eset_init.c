#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsdn_t ;
typedef  int /*<<< orphan*/  extent_state_t ;
struct TYPE_3__ {int delay_coalesce; int /*<<< orphan*/  state; int /*<<< orphan*/  npages; int /*<<< orphan*/  lru; int /*<<< orphan*/  bitmap; int /*<<< orphan*/ * heaps; int /*<<< orphan*/  mtx; } ;
typedef  TYPE_1__ eset_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATOMIC_RELAXED ; 
 int SC_NPSIZES ; 
 int /*<<< orphan*/  WITNESS_RANK_EXTENTS ; 
 int /*<<< orphan*/  atomic_store_zu (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  eset_bitmap_info ; 
 int /*<<< orphan*/  extent_heap_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_list_init (int /*<<< orphan*/ *) ; 
 scalar_t__ malloc_mutex_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  malloc_mutex_rank_exclusive ; 

bool
eset_init(tsdn_t *tsdn, eset_t *eset, extent_state_t state,
    bool delay_coalesce) {
	if (malloc_mutex_init(&eset->mtx, "extents", WITNESS_RANK_EXTENTS,
	    malloc_mutex_rank_exclusive)) {
		return true;
	}
	for (unsigned i = 0; i < SC_NPSIZES + 1; i++) {
		extent_heap_new(&eset->heaps[i]);
	}
	bitmap_init(eset->bitmap, &eset_bitmap_info, true);
	extent_list_init(&eset->lru);
	atomic_store_zu(&eset->npages, 0, ATOMIC_RELAXED);
	eset->state = state;
	eset->delay_coalesce = delay_coalesce;
	return false;
}