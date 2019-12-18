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
typedef  int /*<<< orphan*/  tsdn_t ;
typedef  int /*<<< orphan*/  szind_t ;
typedef  int /*<<< orphan*/  extent_t ;
typedef  int /*<<< orphan*/  extent_hooks_t ;
struct TYPE_5__ {int /*<<< orphan*/  extent_grow_mtx; int /*<<< orphan*/  eset_retained; } ;
typedef  TYPE_1__ arena_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ config_prof ; 
 int /*<<< orphan*/  extent_gdump_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * extent_grow_retained (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ **,size_t,size_t,size_t,int,int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/ * extent_recycle (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ **,int /*<<< orphan*/ *,void*,size_t,size_t,size_t,int,int /*<<< orphan*/ ,int*,int*,int) ; 
 int /*<<< orphan*/  malloc_mutex_assert_not_owner (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ opt_retain ; 

__attribute__((used)) static extent_t *
extent_alloc_retained(tsdn_t *tsdn, arena_t *arena,
    extent_hooks_t **r_extent_hooks, void *new_addr, size_t size, size_t pad,
    size_t alignment, bool slab, szind_t szind, bool *zero, bool *commit) {
	assert(size != 0);
	assert(alignment != 0);

	malloc_mutex_lock(tsdn, &arena->extent_grow_mtx);

	extent_t *extent = extent_recycle(tsdn, arena, r_extent_hooks,
	    &arena->eset_retained, new_addr, size, pad, alignment, slab,
	    szind, zero, commit, true);
	if (extent != NULL) {
		malloc_mutex_unlock(tsdn, &arena->extent_grow_mtx);
		if (config_prof) {
			extent_gdump_add(tsdn, extent);
		}
	} else if (opt_retain && new_addr == NULL) {
		extent = extent_grow_retained(tsdn, arena, r_extent_hooks, size,
		    pad, alignment, slab, szind, zero, commit);
		/* extent_grow_retained() always releases extent_grow_mtx. */
	} else {
		malloc_mutex_unlock(tsdn, &arena->extent_grow_mtx);
	}
	malloc_mutex_assert_not_owner(tsdn, &arena->extent_grow_mtx);

	return extent;
}