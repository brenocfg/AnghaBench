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
typedef  int /*<<< orphan*/  szind_t ;
typedef  int /*<<< orphan*/  arena_t ;

/* Variables and functions */
 size_t SMALL_MAXCLASS ; 
 int /*<<< orphan*/ * arena_choose (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* arena_malloc_small (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 void* large_malloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  sz_index2size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsdn_null (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsdn_tsd (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

void *
arena_malloc_hard(tsdn_t *tsdn, arena_t *arena, size_t size, szind_t ind,
    bool zero) {
	assert(!tsdn_null(tsdn) || arena != NULL);

	if (likely(!tsdn_null(tsdn))) {
		arena = arena_choose(tsdn_tsd(tsdn), arena);
	}
	if (unlikely(arena == NULL)) {
		return NULL;
	}

	if (likely(size <= SMALL_MAXCLASS)) {
		return arena_malloc_small(tsdn, arena, ind, zero);
	}
	return large_malloc(tsdn, arena, sz_index2size(ind), zero);
}