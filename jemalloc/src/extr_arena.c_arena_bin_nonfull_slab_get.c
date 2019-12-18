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
typedef  int /*<<< orphan*/  tsdn_t ;
typedef  size_t szind_t ;
typedef  int /*<<< orphan*/  extent_t ;
struct TYPE_5__ {int /*<<< orphan*/  curslabs; int /*<<< orphan*/  nslabs; } ;
struct TYPE_6__ {TYPE_1__ stats; int /*<<< orphan*/  lock; } ;
typedef  TYPE_2__ bin_t ;
typedef  int /*<<< orphan*/  bin_info_t ;
typedef  int /*<<< orphan*/  arena_t ;

/* Variables and functions */
 int /*<<< orphan*/ * arena_bin_slabs_nonfull_tryget (TYPE_2__*) ; 
 int /*<<< orphan*/ * arena_slab_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,unsigned int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * bin_infos ; 
 scalar_t__ config_stats ; 
 int /*<<< orphan*/  malloc_mutex_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static extent_t *
arena_bin_nonfull_slab_get(tsdn_t *tsdn, arena_t *arena, bin_t *bin,
    szind_t binind, unsigned binshard) {
	extent_t *slab;
	const bin_info_t *bin_info;

	/* Look for a usable slab. */
	slab = arena_bin_slabs_nonfull_tryget(bin);
	if (slab != NULL) {
		return slab;
	}
	/* No existing slabs have any space available. */

	bin_info = &bin_infos[binind];

	/* Allocate a new slab. */
	malloc_mutex_unlock(tsdn, &bin->lock);
	/******************************/
	slab = arena_slab_alloc(tsdn, arena, binind, binshard, bin_info);
	/********************************/
	malloc_mutex_lock(tsdn, &bin->lock);
	if (slab != NULL) {
		if (config_stats) {
			bin->stats.nslabs++;
			bin->stats.curslabs++;
		}
		return slab;
	}

	/*
	 * arena_slab_alloc() failed, but another thread may have made
	 * sufficient memory available while this one dropped bin->lock above,
	 * so search one more time.
	 */
	slab = arena_bin_slabs_nonfull_tryget(bin);
	if (slab != NULL) {
		return slab;
	}

	return NULL;
}