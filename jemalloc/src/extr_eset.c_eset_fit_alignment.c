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
typedef  size_t pszind_t ;
typedef  int /*<<< orphan*/  extent_t ;
struct TYPE_3__ {int /*<<< orphan*/ * heaps; int /*<<< orphan*/  bitmap; } ;
typedef  TYPE_1__ eset_t ;

/* Variables and functions */
 uintptr_t ALIGNMENT_CEILING (uintptr_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGE_CEILING (size_t) ; 
 size_t SC_NPSIZES ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ bitmap_ffu (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  eset_bitmap_info ; 
 scalar_t__ extent_base_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_heap_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * extent_heap_first (int /*<<< orphan*/ *) ; 
 size_t extent_size_get (int /*<<< orphan*/ *) ; 
 size_t sz_psz2ind (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sz_psz_quantize_ceil (size_t) ; 

__attribute__((used)) static extent_t *
eset_fit_alignment(eset_t *eset, size_t min_size, size_t max_size,
    size_t alignment) {
        pszind_t pind = sz_psz2ind(sz_psz_quantize_ceil(min_size));
        pszind_t pind_max = sz_psz2ind(sz_psz_quantize_ceil(max_size));

	for (pszind_t i = (pszind_t)bitmap_ffu(eset->bitmap,
	    &eset_bitmap_info, (size_t)pind); i < pind_max; i =
	    (pszind_t)bitmap_ffu(eset->bitmap, &eset_bitmap_info,
	    (size_t)i+1)) {
		assert(i < SC_NPSIZES);
		assert(!extent_heap_empty(&eset->heaps[i]));
		extent_t *extent = extent_heap_first(&eset->heaps[i]);
		uintptr_t base = (uintptr_t)extent_base_get(extent);
		size_t candidate_size = extent_size_get(extent);
		assert(candidate_size >= min_size);

		uintptr_t next_align = ALIGNMENT_CEILING((uintptr_t)base,
		    PAGE_CEILING(alignment));
		if (base > next_align || base + candidate_size <= next_align) {
			/* Overflow or not crossing the next alignment. */
			continue;
		}

		size_t leadsize = next_align - base;
		if (candidate_size - leadsize >= min_size) {
			return extent;
		}
	}

	return NULL;
}