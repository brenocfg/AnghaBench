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
typedef  int /*<<< orphan*/  rtree_leaf_elm_t ;
typedef  int /*<<< orphan*/  rtree_ctx_t ;
typedef  int /*<<< orphan*/  extent_t ;

/* Variables and functions */
 int /*<<< orphan*/  SC_NSIZES ; 
 scalar_t__ config_prof ; 
 int /*<<< orphan*/  extent_gdump_sub (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_interior_deregister (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_rtree_leaf_elms_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  extent_rtree_write_acquired (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ extent_slab_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_slab_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  extent_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * tsdn_rtree_ctx (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
extent_deregister_impl(tsdn_t *tsdn, extent_t *extent, bool gdump) {
	rtree_ctx_t rtree_ctx_fallback;
	rtree_ctx_t *rtree_ctx = tsdn_rtree_ctx(tsdn, &rtree_ctx_fallback);
	rtree_leaf_elm_t *elm_a, *elm_b;
	extent_rtree_leaf_elms_lookup(tsdn, rtree_ctx, extent, true, false,
	    &elm_a, &elm_b);

	extent_lock(tsdn, extent);

	extent_rtree_write_acquired(tsdn, elm_a, elm_b, NULL, SC_NSIZES, false);
	if (extent_slab_get(extent)) {
		extent_interior_deregister(tsdn, rtree_ctx, extent);
		extent_slab_set(extent, false);
	}

	extent_unlock(tsdn, extent);

	if (config_prof && gdump) {
		extent_gdump_sub(tsdn, extent);
	}
}