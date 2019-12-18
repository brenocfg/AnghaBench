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
typedef  int /*<<< orphan*/  extent_t ;

/* Variables and functions */
 int /*<<< orphan*/  extents_rtree ; 
 int /*<<< orphan*/  rtree_leaf_elm_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
extent_rtree_write_acquired(tsdn_t *tsdn, rtree_leaf_elm_t *elm_a,
    rtree_leaf_elm_t *elm_b, extent_t *extent, szind_t szind, bool slab) {
	rtree_leaf_elm_write(tsdn, &extents_rtree, elm_a, extent, szind, slab);
	if (elm_b != NULL) {
		rtree_leaf_elm_write(tsdn, &extents_rtree, elm_b, extent, szind,
		    slab);
	}
}