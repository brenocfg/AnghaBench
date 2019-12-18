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
typedef  size_t szind_t ;
typedef  int /*<<< orphan*/  extent_t ;
struct TYPE_3__ {scalar_t__ allocated; scalar_t__ resident; scalar_t__ mapped; scalar_t__ n_thp; scalar_t__ auto_thp_switched; int /*<<< orphan*/ * avail; } ;
typedef  TYPE_1__ base_t ;

/* Variables and functions */
 int HUGEPAGE_CEILING (uintptr_t) ; 
 int LG_HUGEPAGE ; 
 scalar_t__ PAGE_CEILING (uintptr_t) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ config_stats ; 
 scalar_t__ extent_bsize_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_heap_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ metadata_thp_always ; 
 scalar_t__ metadata_thp_madvise () ; 
 scalar_t__ opt_metadata_thp ; 
 size_t sz_size2index (scalar_t__) ; 

__attribute__((used)) static void
base_extent_bump_alloc_post(base_t *base, extent_t *extent, size_t gap_size,
    void *addr, size_t size) {
	if (extent_bsize_get(extent) > 0) {
		/*
		 * Compute the index for the largest size class that does not
		 * exceed extent's size.
		 */
		szind_t index_floor =
		    sz_size2index(extent_bsize_get(extent) + 1) - 1;
		extent_heap_insert(&base->avail[index_floor], extent);
	}

	if (config_stats) {
		base->allocated += size;
		/*
		 * Add one PAGE to base_resident for every page boundary that is
		 * crossed by the new allocation. Adjust n_thp similarly when
		 * metadata_thp is enabled.
		 */
		base->resident += PAGE_CEILING((uintptr_t)addr + size) -
		    PAGE_CEILING((uintptr_t)addr - gap_size);
		assert(base->allocated <= base->resident);
		assert(base->resident <= base->mapped);
		if (metadata_thp_madvise() && (opt_metadata_thp ==
		    metadata_thp_always || base->auto_thp_switched)) {
			base->n_thp += (HUGEPAGE_CEILING((uintptr_t)addr + size)
			    - HUGEPAGE_CEILING((uintptr_t)addr - gap_size)) >>
			    LG_HUGEPAGE;
			assert(base->mapped >= base->n_thp << LG_HUGEPAGE);
		}
	}
}