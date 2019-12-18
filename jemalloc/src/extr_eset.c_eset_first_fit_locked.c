#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsdn_t ;
typedef  size_t pszind_t ;
typedef  int /*<<< orphan*/  extent_t ;
struct TYPE_3__ {scalar_t__ delay_coalesce; int /*<<< orphan*/ * heaps; int /*<<< orphan*/  bitmap; } ;
typedef  TYPE_1__ eset_t ;

/* Variables and functions */
 int SC_NPSIZES ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ bitmap_ffu (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  eset_bitmap_info ; 
 scalar_t__ extent_heap_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * extent_heap_first (int /*<<< orphan*/ *) ; 
 size_t extent_size_get (int /*<<< orphan*/ *) ; 
 scalar_t__ extent_snad_comp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  maps_coalesce ; 
 size_t opt_lg_extent_max_active_fit ; 
 int /*<<< orphan*/  opt_retain ; 
 size_t sz_pind2sz (size_t) ; 
 size_t sz_psz2ind (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sz_psz_quantize_ceil (size_t) ; 

__attribute__((used)) static extent_t *
eset_first_fit_locked(tsdn_t *tsdn, eset_t *eset, size_t size) {
	extent_t *ret = NULL;

	pszind_t pind = sz_psz2ind(sz_psz_quantize_ceil(size));

	if (!maps_coalesce && !opt_retain) {
		/*
		 * No split / merge allowed (Windows w/o retain). Try exact fit
		 * only.
		 */
		return extent_heap_empty(&eset->heaps[pind]) ? NULL :
		    extent_heap_first(&eset->heaps[pind]);
	}

	for (pszind_t i = (pszind_t)bitmap_ffu(eset->bitmap,
	    &eset_bitmap_info, (size_t)pind);
	    i < SC_NPSIZES + 1;
	    i = (pszind_t)bitmap_ffu(eset->bitmap, &eset_bitmap_info,
	    (size_t)i+1)) {
		assert(!extent_heap_empty(&eset->heaps[i]));
		extent_t *extent = extent_heap_first(&eset->heaps[i]);
		assert(extent_size_get(extent) >= size);
		/*
		 * In order to reduce fragmentation, avoid reusing and splitting
		 * large eset for much smaller sizes.
		 *
		 * Only do check for dirty eset (delay_coalesce).
		 */
		if (eset->delay_coalesce &&
		    (sz_pind2sz(i) >> opt_lg_extent_max_active_fit) > size) {
			break;
		}
		if (ret == NULL || extent_snad_comp(extent, ret) < 0) {
			ret = extent;
		}
		if (i == SC_NPSIZES) {
			break;
		}
		assert(i < SC_NPSIZES);
	}

	return ret;
}