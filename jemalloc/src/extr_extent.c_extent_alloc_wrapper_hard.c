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
struct TYPE_5__ {void* (* alloc ) (TYPE_1__*,void*,size_t,size_t,int*,int*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ extent_hooks_t ;
typedef  int /*<<< orphan*/  arena_t ;

/* Variables and functions */
 size_t ALIGNMENT_CEILING (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXTENT_NOT_HEAD ; 
 int /*<<< orphan*/  PAGE ; 
 int /*<<< orphan*/  arena_extent_sn_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  arena_ind_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_addr_randomize (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/ * extent_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* extent_alloc_default_impl (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,size_t,size_t,int*,int*) ; 
 int /*<<< orphan*/  extent_dalloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_hook_post_reentrancy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_hook_pre_reentrancy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__ extent_hooks_default ; 
 int /*<<< orphan*/  extent_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,size_t,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ extent_register (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_state_active ; 
 void* stub1 (TYPE_1__*,void*,size_t,size_t,int*,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static extent_t *
extent_alloc_wrapper_hard(tsdn_t *tsdn, arena_t *arena,
    extent_hooks_t **r_extent_hooks, void *new_addr, size_t size, size_t pad,
    size_t alignment, bool slab, szind_t szind, bool *zero, bool *commit) {
	size_t esize = size + pad;
	extent_t *extent = extent_alloc(tsdn, arena);
	if (extent == NULL) {
		return NULL;
	}
	void *addr;
	size_t palignment = ALIGNMENT_CEILING(alignment, PAGE);
	if (*r_extent_hooks == &extent_hooks_default) {
		/* Call directly to propagate tsdn. */
		addr = extent_alloc_default_impl(tsdn, arena, new_addr, esize,
		    palignment, zero, commit);
	} else {
		extent_hook_pre_reentrancy(tsdn, arena);
		addr = (*r_extent_hooks)->alloc(*r_extent_hooks, new_addr,
		    esize, palignment, zero, commit, arena_ind_get(arena));
		extent_hook_post_reentrancy(tsdn);
	}
	if (addr == NULL) {
		extent_dalloc(tsdn, arena, extent);
		return NULL;
	}
	extent_init(extent, arena_ind_get(arena), addr, esize, slab, szind,
	    arena_extent_sn_next(arena), extent_state_active, *zero, *commit,
	    true, EXTENT_NOT_HEAD);
	if (pad != 0) {
		extent_addr_randomize(tsdn, arena, extent, alignment);
	}
	if (extent_register(tsdn, extent)) {
		extent_dalloc(tsdn, arena, extent);
		return NULL;
	}

	return extent;
}