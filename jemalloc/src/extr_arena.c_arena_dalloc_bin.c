#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsdn_t ;
typedef  size_t szind_t ;
typedef  int /*<<< orphan*/  extent_t ;
struct TYPE_8__ {int /*<<< orphan*/  lock; } ;
typedef  TYPE_2__ bin_t ;
struct TYPE_9__ {TYPE_1__* bins; } ;
typedef  TYPE_3__ arena_t ;
struct TYPE_7__ {TYPE_2__* bin_shards; } ;

/* Variables and functions */
 int /*<<< orphan*/  arena_dalloc_bin_locked_impl (int /*<<< orphan*/ *,TYPE_3__*,TYPE_2__*,size_t,int /*<<< orphan*/ *,void*,int) ; 
 unsigned int extent_binshard_get (int /*<<< orphan*/ *) ; 
 size_t extent_szind_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
arena_dalloc_bin(tsdn_t *tsdn, arena_t *arena, extent_t *extent, void *ptr) {
	szind_t binind = extent_szind_get(extent);
	unsigned binshard = extent_binshard_get(extent);
	bin_t *bin = &arena->bins[binind].bin_shards[binshard];

	malloc_mutex_lock(tsdn, &bin->lock);
	arena_dalloc_bin_locked_impl(tsdn, arena, bin, binind, extent, ptr,
	    false);
	malloc_mutex_unlock(tsdn, &bin->lock);
}