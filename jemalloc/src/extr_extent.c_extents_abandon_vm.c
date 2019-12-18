#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsdn_t ;
typedef  int /*<<< orphan*/  extent_t ;
typedef  int /*<<< orphan*/  extent_hooks_t ;
typedef  int /*<<< orphan*/  eset_t ;
struct TYPE_7__ {int /*<<< orphan*/  abandoned_vm; } ;
struct TYPE_8__ {TYPE_1__ stats; } ;
typedef  TYPE_2__ arena_t ;

/* Variables and functions */
 int /*<<< orphan*/  arena_stats_accum_zu (int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ config_stats ; 
 scalar_t__ eset_state_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_dalloc (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_purge_forced_impl (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t,int) ; 
 scalar_t__ extent_purge_lazy_impl (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t,int) ; 
 size_t extent_size_get (int /*<<< orphan*/ *) ; 
 scalar_t__ extent_state_dirty ; 

__attribute__((used)) static void
extents_abandon_vm(tsdn_t *tsdn, arena_t *arena, extent_hooks_t **r_extent_hooks,
    eset_t *eset, extent_t *extent, bool growing_retained) {
	size_t sz = extent_size_get(extent);
	if (config_stats) {
		arena_stats_accum_zu(&arena->stats.abandoned_vm, sz);
	}
	/*
	 * Leak extent after making sure its pages have already been purged, so
	 * that this is only a virtual memory leak.
	 */
	if (eset_state_get(eset) == extent_state_dirty) {
		if (extent_purge_lazy_impl(tsdn, arena, r_extent_hooks,
		    extent, 0, sz, growing_retained)) {
			extent_purge_forced_impl(tsdn, arena, r_extent_hooks,
			    extent, 0, extent_size_get(extent),
			    growing_retained);
		}
	}
	extent_dalloc(tsdn, arena, extent);
}