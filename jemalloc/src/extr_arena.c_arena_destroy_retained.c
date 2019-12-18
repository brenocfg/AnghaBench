#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsdn_t ;
typedef  int /*<<< orphan*/  extent_t ;
typedef  int /*<<< orphan*/  extent_hooks_t ;
struct TYPE_6__ {int /*<<< orphan*/  eset_retained; } ;
typedef  TYPE_1__ arena_t ;

/* Variables and functions */
 int /*<<< orphan*/  extent_destroy_wrapper (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * extent_hooks_get (TYPE_1__*) ; 
 int /*<<< orphan*/ * extents_evict (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
arena_destroy_retained(tsdn_t *tsdn, arena_t *arena) {
	/*
	 * Iterate over the retained extents and destroy them.  This gives the
	 * extent allocator underlying the extent hooks an opportunity to unmap
	 * all retained memory without having to keep its own metadata
	 * structures.  In practice, virtual memory for dss-allocated extents is
	 * leaked here, so best practice is to avoid dss for arenas to be
	 * destroyed, or provide custom extent hooks that track retained
	 * dss-based extents for later reuse.
	 */
	extent_hooks_t *extent_hooks = extent_hooks_get(arena);
	extent_t *extent;
	while ((extent = extents_evict(tsdn, arena, &extent_hooks,
	    &arena->eset_retained, 0)) != NULL) {
		extent_destroy_wrapper(tsdn, arena, &extent_hooks, extent);
	}
}