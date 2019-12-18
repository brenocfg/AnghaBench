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
typedef  int /*<<< orphan*/  tsdn_t ;
typedef  int /*<<< orphan*/  extent_hooks_t ;
typedef  int /*<<< orphan*/  arena_t ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGNMENT_CEILING (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGE ; 
 int /*<<< orphan*/ * arena_get (int /*<<< orphan*/ *,unsigned int,int) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 void* extent_alloc_default_impl (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,size_t,int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/ * tsdn_fetch () ; 

__attribute__((used)) static void *
extent_alloc_default(extent_hooks_t *extent_hooks, void *new_addr, size_t size,
    size_t alignment, bool *zero, bool *commit, unsigned arena_ind) {
	tsdn_t *tsdn;
	arena_t *arena;

	tsdn = tsdn_fetch();
	arena = arena_get(tsdn, arena_ind, false);
	/*
	 * The arena we're allocating on behalf of must have been initialized
	 * already.
	 */
	assert(arena != NULL);

	return extent_alloc_default_impl(tsdn, arena, new_addr, size,
	    ALIGNMENT_CEILING(alignment, PAGE), zero, commit);
}