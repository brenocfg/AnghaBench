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
typedef  size_t szind_t ;
typedef  int /*<<< orphan*/  rtree_ctx_t ;
typedef  int /*<<< orphan*/  extent_t ;
typedef  int /*<<< orphan*/  cache_bin_t ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 void** cache_bin_bottom_item_get (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  extents_rtree ; 
 int /*<<< orphan*/  rtree_extent_szind_read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,uintptr_t,int,int /*<<< orphan*/ **,size_t*) ; 
 int /*<<< orphan*/  safety_check_fail (char*) ; 
 int /*<<< orphan*/ * tsdn_rtree_ctx (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
tbin_extents_lookup_size_check(tsdn_t *tsdn, cache_bin_t *tbin, szind_t binind,
    size_t nflush, extent_t **extents){
	rtree_ctx_t rtree_ctx_fallback;
	rtree_ctx_t *rtree_ctx = tsdn_rtree_ctx(tsdn, &rtree_ctx_fallback);

	/*
	 * Verify that the items in the tcache all have the correct size; this
	 * is useful for catching sized deallocation bugs, also to fail early
	 * instead of corrupting metadata.  Since this can be turned on for opt
	 * builds, avoid the branch in the loop.
	 */
	szind_t szind;
	size_t sz_sum = binind * nflush;
	void **bottom_item = cache_bin_bottom_item_get(tbin, binind);
	for (unsigned i = 0 ; i < nflush; i++) {
		rtree_extent_szind_read(tsdn, &extents_rtree,
		    rtree_ctx, (uintptr_t)*(bottom_item - i), true,
		    &extents[i], &szind);
		sz_sum -= szind;
	}
	if (sz_sum != 0) {
		safety_check_fail("<jemalloc>: size mismatch in thread cache "
		    "detected, likely caused by sized deallocation bugs by "
		    "application. Abort.\n");
		abort();
	}
}