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

/* Variables and functions */
 int LG_PAGE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ extent_base_get (int /*<<< orphan*/ *) ; 
 int extent_size_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_slab_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extents_rtree ; 
 int /*<<< orphan*/  rtree_clear (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,uintptr_t) ; 

__attribute__((used)) static void
extent_interior_deregister(tsdn_t *tsdn, rtree_ctx_t *rtree_ctx,
    extent_t *extent) {
	size_t i;

	assert(extent_slab_get(extent));

	for (i = 1; i < (extent_size_get(extent) >> LG_PAGE) - 1; i++) {
		rtree_clear(tsdn, &extents_rtree, rtree_ctx,
		    (uintptr_t)extent_base_get(extent) + (uintptr_t)(i <<
		    LG_PAGE));
	}
}