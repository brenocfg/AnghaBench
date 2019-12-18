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
typedef  int /*<<< orphan*/  extent_t ;
struct TYPE_5__ {int /*<<< orphan*/  large; int /*<<< orphan*/  large_mtx; } ;
typedef  TYPE_1__ arena_t ;

/* Variables and functions */
 int /*<<< orphan*/  arena_extent_dalloc_large_prep (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  arena_is_auto (TYPE_1__*) ; 
 int /*<<< orphan*/  extent_addr_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_list_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_usize_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  large_dalloc_maybe_junk (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  malloc_mutex_assert_owner (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
large_dalloc_prep_impl(tsdn_t *tsdn, arena_t *arena, extent_t *extent,
    bool junked_locked) {
	if (!junked_locked) {
		/* See comments in arena_bin_slabs_full_insert(). */
		if (!arena_is_auto(arena)) {
			malloc_mutex_lock(tsdn, &arena->large_mtx);
			extent_list_remove(&arena->large, extent);
			malloc_mutex_unlock(tsdn, &arena->large_mtx);
		}
		large_dalloc_maybe_junk(extent_addr_get(extent),
		    extent_usize_get(extent));
	} else {
		/* Only hold the large_mtx if necessary. */
		if (!arena_is_auto(arena)) {
			malloc_mutex_assert_owner(tsdn, &arena->large_mtx);
			extent_list_remove(&arena->large, extent);
		}
	}
	arena_extent_dalloc_large_prep(tsdn, arena, extent);
}