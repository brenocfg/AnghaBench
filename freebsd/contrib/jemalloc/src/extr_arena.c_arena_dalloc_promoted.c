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
 size_t arena_prof_demote (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cassert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  config_prof ; 
 int /*<<< orphan*/ * iealloc (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  large_dalloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opt_prof ; 
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
	size_t usize = arena_prof_demote(tsdn, extent, ptr);
	if (usize <= tcache_maxclass) {
		tcache_dalloc_large(tsdn_tsd(tsdn), tcache, ptr,
		    sz_size2index(usize), slow_path);
	} else {
		large_dalloc(tsdn, extent);
	}
}