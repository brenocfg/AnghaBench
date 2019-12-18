#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsdn_t ;
typedef  int /*<<< orphan*/  extent_t ;
struct TYPE_2__ {size_t reg_size; } ;

/* Variables and functions */
 size_t LARGE_MAXCLASS ; 
 size_t LARGE_MINCLASS ; 
 size_t SMALL_MAXCLASS ; 
 int /*<<< orphan*/  arena_decay_tick (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* bin_infos ; 
 int /*<<< orphan*/  extent_arena_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * iealloc (int /*<<< orphan*/ *,void*) ; 
 int large_ralloc_no_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,size_t,int) ; 
 scalar_t__ likely (int) ; 
 size_t sz_s2u (size_t) ; 
 size_t sz_size2index (size_t) ; 
 scalar_t__ unlikely (int) ; 

bool
arena_ralloc_no_move(tsdn_t *tsdn, void *ptr, size_t oldsize, size_t size,
    size_t extra, bool zero) {
	/* Calls with non-zero extra had to clamp extra. */
	assert(extra == 0 || size + extra <= LARGE_MAXCLASS);

	if (unlikely(size > LARGE_MAXCLASS)) {
		return true;
	}

	extent_t *extent = iealloc(tsdn, ptr);
	size_t usize_min = sz_s2u(size);
	size_t usize_max = sz_s2u(size + extra);
	if (likely(oldsize <= SMALL_MAXCLASS && usize_min <= SMALL_MAXCLASS)) {
		/*
		 * Avoid moving the allocation if the size class can be left the
		 * same.
		 */
		assert(bin_infos[sz_size2index(oldsize)].reg_size ==
		    oldsize);
		if ((usize_max > SMALL_MAXCLASS || sz_size2index(usize_max) !=
		    sz_size2index(oldsize)) && (size > oldsize || usize_max <
		    oldsize)) {
			return true;
		}

		arena_decay_tick(tsdn, extent_arena_get(extent));
		return false;
	} else if (oldsize >= LARGE_MINCLASS && usize_max >= LARGE_MINCLASS) {
		return large_ralloc_no_move(tsdn, extent, usize_min, usize_max,
		    zero);
	}

	return true;
}