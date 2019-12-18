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
typedef  int /*<<< orphan*/  tcache_t ;
typedef  int /*<<< orphan*/  extent_t ;

/* Variables and functions */
 size_t SC_LARGE_MINCLASS ; 
 size_t arena_prof_demote (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  cassert (int /*<<< orphan*/ ) ; 
 scalar_t__ config_opt_safety_checks ; 
 int /*<<< orphan*/  config_prof ; 
 size_t extent_usize_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * iealloc (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  large_dalloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int opt_prof ; 
 int /*<<< orphan*/  safety_check_verify_redzone (void*,size_t,size_t) ; 
 int /*<<< orphan*/  sz_size2index (size_t) ; 
 int /*<<< orphan*/  tcache_dalloc_large (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int) ; 
 size_t tcache_maxclass ; 
 int /*<<< orphan*/  tsdn_tsd (int /*<<< orphan*/ *) ; 

void
arena_dalloc_promoted(tsdn_t *tsdn, void *ptr, tcache_t *tcache,
    bool slow_path) {
	cassert(config_prof);
	assert(opt_prof);

	extent_t *extent = iealloc(tsdn, ptr);
	size_t usize = extent_usize_get(extent);
	size_t bumped_usize = arena_prof_demote(tsdn, extent, ptr);
	if (config_opt_safety_checks && usize < SC_LARGE_MINCLASS) {
		/*
		 * Currently, we only do redzoning for small sampled
		 * allocations.
		 */
		assert(bumped_usize == SC_LARGE_MINCLASS);
		safety_check_verify_redzone(ptr, usize, bumped_usize);
	}
	if (bumped_usize <= tcache_maxclass && tcache != NULL) {
		tcache_dalloc_large(tsdn_tsd(tsdn), tcache, ptr,
		    sz_size2index(bumped_usize), slow_path);
	} else {
		large_dalloc(tsdn, extent);
	}
}