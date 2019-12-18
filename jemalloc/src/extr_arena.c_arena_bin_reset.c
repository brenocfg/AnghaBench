#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsd_t ;
typedef  int /*<<< orphan*/  extent_t ;
struct TYPE_5__ {scalar_t__ curslabs; scalar_t__ curregs; } ;
struct TYPE_6__ {int /*<<< orphan*/  lock; TYPE_1__ stats; int /*<<< orphan*/  slabs_full; int /*<<< orphan*/  slabs_nonfull; int /*<<< orphan*/ * slabcur; } ;
typedef  TYPE_2__ bin_t ;
typedef  int /*<<< orphan*/  arena_t ;

/* Variables and functions */
 int /*<<< orphan*/  arena_bin_slabs_full_remove (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  arena_slab_dalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ config_stats ; 
 int /*<<< orphan*/ * extent_heap_remove_first (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * extent_list_first (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_unlock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsd_tsdn (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
arena_bin_reset(tsd_t *tsd, arena_t *arena, bin_t *bin) {
	extent_t *slab;

	malloc_mutex_lock(tsd_tsdn(tsd), &bin->lock);
	if (bin->slabcur != NULL) {
		slab = bin->slabcur;
		bin->slabcur = NULL;
		malloc_mutex_unlock(tsd_tsdn(tsd), &bin->lock);
		arena_slab_dalloc(tsd_tsdn(tsd), arena, slab);
		malloc_mutex_lock(tsd_tsdn(tsd), &bin->lock);
	}
	while ((slab = extent_heap_remove_first(&bin->slabs_nonfull)) != NULL) {
		malloc_mutex_unlock(tsd_tsdn(tsd), &bin->lock);
		arena_slab_dalloc(tsd_tsdn(tsd), arena, slab);
		malloc_mutex_lock(tsd_tsdn(tsd), &bin->lock);
	}
	for (slab = extent_list_first(&bin->slabs_full); slab != NULL;
	     slab = extent_list_first(&bin->slabs_full)) {
		arena_bin_slabs_full_remove(arena, bin, slab);
		malloc_mutex_unlock(tsd_tsdn(tsd), &bin->lock);
		arena_slab_dalloc(tsd_tsdn(tsd), arena, slab);
		malloc_mutex_lock(tsd_tsdn(tsd), &bin->lock);
	}
	if (config_stats) {
		bin->stats.curregs = 0;
		bin->stats.curslabs = 0;
	}
	malloc_mutex_unlock(tsd_tsdn(tsd), &bin->lock);
}