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
typedef  int /*<<< orphan*/  tsd_t ;
struct TYPE_5__ {int /*<<< orphan*/  base; int /*<<< orphan*/  extents_muzzy; int /*<<< orphan*/  extents_dirty; } ;
typedef  TYPE_1__ arena_t ;

/* Variables and functions */
 int /*<<< orphan*/  arena_destroy_retained (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ arena_nthreads_get (TYPE_1__*,int) ; 
 int /*<<< orphan*/  arena_set (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  base_delete (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ base_ind_get (int /*<<< orphan*/ ) ; 
 scalar_t__ extents_npages_get (int /*<<< orphan*/ *) ; 
 scalar_t__ narenas_auto ; 
 int /*<<< orphan*/  tsd_tsdn (int /*<<< orphan*/ *) ; 

void
arena_destroy(tsd_t *tsd, arena_t *arena) {
	assert(base_ind_get(arena->base) >= narenas_auto);
	assert(arena_nthreads_get(arena, false) == 0);
	assert(arena_nthreads_get(arena, true) == 0);

	/*
	 * No allocations have occurred since arena_reset() was called.
	 * Furthermore, the caller (arena_i_destroy_ctl()) purged all cached
	 * extents, so only retained extents may remain.
	 */
	assert(extents_npages_get(&arena->extents_dirty) == 0);
	assert(extents_npages_get(&arena->extents_muzzy) == 0);

	/* Deallocate retained memory. */
	arena_destroy_retained(tsd_tsdn(tsd), arena);

	/*
	 * Remove the arena pointer from the arenas array.  We rely on the fact
	 * that there is no way for the application to get a dirty read from the
	 * arenas array unless there is an inherent race in the application
	 * involving access of an arena being concurrently destroyed.  The
	 * application must synchronize knowledge of the arena's validity, so as
	 * long as we use an atomic write to update the arenas array, the
	 * application will get a clean read any time after it synchronizes
	 * knowledge that the arena is no longer valid.
	 */
	arena_set(base_ind_get(arena->base), NULL);

	/*
	 * Destroy the base allocator, which manages all metadata ever mapped by
	 * this arena.
	 */
	base_delete(tsd_tsdn(tsd), arena->base);
}