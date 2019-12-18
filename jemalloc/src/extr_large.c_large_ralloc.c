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
typedef  int /*<<< orphan*/  tcache_t ;
struct TYPE_3__ {int /*<<< orphan*/  args; scalar_t__ is_realloc; } ;
typedef  TYPE_1__ hook_ralloc_args_t ;
typedef  int /*<<< orphan*/  extent_t ;
typedef  int /*<<< orphan*/  arena_t ;

/* Variables and functions */
 size_t SC_LARGE_MAXCLASS ; 
 size_t SC_LARGE_MINCLASS ; 
 int /*<<< orphan*/  assert (int) ; 
 void* extent_addr_get (int /*<<< orphan*/ *) ; 
 size_t extent_usize_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hook_alloc_rallocx ; 
 int /*<<< orphan*/  hook_alloc_realloc ; 
 int /*<<< orphan*/  hook_dalloc_rallocx ; 
 int /*<<< orphan*/  hook_dalloc_realloc ; 
 int /*<<< orphan*/  hook_expand_rallocx ; 
 int /*<<< orphan*/  hook_expand_realloc ; 
 int /*<<< orphan*/  hook_invoke_alloc (int /*<<< orphan*/ ,void*,uintptr_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hook_invoke_dalloc (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hook_invoke_expand (int /*<<< orphan*/ ,void*,size_t,size_t,uintptr_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * iealloc (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  isdalloct (int /*<<< orphan*/ *,void*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 void* large_ralloc_move_helper (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,size_t,int) ; 
 int /*<<< orphan*/  large_ralloc_no_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,size_t,int) ; 
 int /*<<< orphan*/  memcpy (void*,void*,size_t) ; 

void *
large_ralloc(tsdn_t *tsdn, arena_t *arena, void *ptr, size_t usize,
    size_t alignment, bool zero, tcache_t *tcache,
    hook_ralloc_args_t *hook_args) {
	extent_t *extent = iealloc(tsdn, ptr);

	size_t oldusize = extent_usize_get(extent);
	/* The following should have been caught by callers. */
	assert(usize > 0 && usize <= SC_LARGE_MAXCLASS);
	/* Both allocation sizes must be large to avoid a move. */
	assert(oldusize >= SC_LARGE_MINCLASS
	    && usize >= SC_LARGE_MINCLASS);

	/* Try to avoid moving the allocation. */
	if (!large_ralloc_no_move(tsdn, extent, usize, usize, zero)) {
		hook_invoke_expand(hook_args->is_realloc
		    ? hook_expand_realloc : hook_expand_rallocx, ptr, oldusize,
		    usize, (uintptr_t)ptr, hook_args->args);
		return extent_addr_get(extent);
	}

	/*
	 * usize and old size are different enough that we need to use a
	 * different size class.  In that case, fall back to allocating new
	 * space and copying.
	 */
	void *ret = large_ralloc_move_helper(tsdn, arena, usize, alignment,
	    zero);
	if (ret == NULL) {
		return NULL;
	}

	hook_invoke_alloc(hook_args->is_realloc
	    ? hook_alloc_realloc : hook_alloc_rallocx, ret, (uintptr_t)ret,
	    hook_args->args);
	hook_invoke_dalloc(hook_args->is_realloc
	    ? hook_dalloc_realloc : hook_dalloc_rallocx, ptr, hook_args->args);

	size_t copysize = (usize < oldusize) ? usize : oldusize;
	memcpy(ret, extent_addr_get(extent), copysize);
	isdalloct(tsdn, extent_addr_get(extent), oldusize, tcache, NULL, true);
	return ret;
}