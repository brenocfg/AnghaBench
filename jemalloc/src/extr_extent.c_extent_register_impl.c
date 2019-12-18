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
typedef  int /*<<< orphan*/  rtree_leaf_elm_t ;
typedef  int /*<<< orphan*/  rtree_ctx_t ;
typedef  int /*<<< orphan*/  extent_t ;

/* Variables and functions */
 scalar_t__ config_prof ; 
 int /*<<< orphan*/  extent_gdump_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_interior_register (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  extent_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ extent_rtree_leaf_elms_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  extent_rtree_write_acquired (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int extent_slab_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_szind_get_maybe_invalid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * tsdn_rtree_ctx (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
extent_register_impl(tsdn_t *tsdn, extent_t *extent, bool gdump_add) {
	rtree_ctx_t rtree_ctx_fallback;
	rtree_ctx_t *rtree_ctx = tsdn_rtree_ctx(tsdn, &rtree_ctx_fallback);
	rtree_leaf_elm_t *elm_a, *elm_b;

	/*
	 * We need to hold the lock to protect against a concurrent coalesce
	 * operation that sees us in a partial state.
	 */
	extent_lock(tsdn, extent);

	if (extent_rtree_leaf_elms_lookup(tsdn, rtree_ctx, extent, false, true,
	    &elm_a, &elm_b)) {
		extent_unlock(tsdn, extent);
		return true;
	}

	szind_t szind = extent_szind_get_maybe_invalid(extent);
	bool slab = extent_slab_get(extent);
	extent_rtree_write_acquired(tsdn, elm_a, elm_b, extent, szind, slab);
	if (slab) {
		extent_interior_register(tsdn, rtree_ctx, extent, szind);
	}

	extent_unlock(tsdn, extent);

	if (config_prof && gdump_add) {
		extent_gdump_add(tsdn, extent);
	}

	return false;
}