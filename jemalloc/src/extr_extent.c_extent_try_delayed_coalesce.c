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
typedef  int /*<<< orphan*/  rtree_ctx_t ;
typedef  int /*<<< orphan*/  extent_t ;
typedef  int /*<<< orphan*/  extent_hooks_t ;
typedef  int /*<<< orphan*/  eset_t ;
typedef  int /*<<< orphan*/  arena_t ;

/* Variables and functions */
 int /*<<< orphan*/  eset_insert_locked (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eset_state_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_state_active ; 
 int /*<<< orphan*/  extent_state_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * extent_try_coalesce (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int) ; 

__attribute__((used)) static bool
extent_try_delayed_coalesce(tsdn_t *tsdn, arena_t *arena,
    extent_hooks_t **r_extent_hooks, rtree_ctx_t *rtree_ctx, eset_t *eset,
    extent_t *extent) {
	extent_state_set(extent, extent_state_active);
	bool coalesced;
	extent = extent_try_coalesce(tsdn, arena, r_extent_hooks, rtree_ctx,
	    eset, extent, &coalesced, false);
	extent_state_set(extent, eset_state_get(eset));

	if (!coalesced) {
		return true;
	}
	eset_insert_locked(tsdn, eset, extent);
	return false;
}