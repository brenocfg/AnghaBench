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
struct iommu_table {scalar_t__ it_base; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;

/* Variables and functions */
 unsigned int DARTMAP_RPNMASK ; 
 unsigned int DARTMAP_VALID ; 
 unsigned int DART_PAGE_SHIFT ; 
 scalar_t__ DART_PAGE_SIZE ; 
 int /*<<< orphan*/  DBG (char*,long,long,unsigned long) ; 
 unsigned int __pa (unsigned long) ; 
 int /*<<< orphan*/  dart_cache_sync (unsigned int*,long) ; 
 int dart_dirty ; 
 scalar_t__ dart_is_u4 ; 
 int /*<<< orphan*/  dart_tlb_invalidate_one (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dart_build(struct iommu_table *tbl, long index,
		       long npages, unsigned long uaddr,
		       enum dma_data_direction direction,
		       unsigned long attrs)
{
	unsigned int *dp, *orig_dp;
	unsigned int rpn;
	long l;

	DBG("dart: build at: %lx, %lx, addr: %x\n", index, npages, uaddr);

	orig_dp = dp = ((unsigned int*)tbl->it_base) + index;

	/* On U3, all memory is contiguous, so we can move this
	 * out of the loop.
	 */
	l = npages;
	while (l--) {
		rpn = __pa(uaddr) >> DART_PAGE_SHIFT;

		*(dp++) = DARTMAP_VALID | (rpn & DARTMAP_RPNMASK);

		uaddr += DART_PAGE_SIZE;
	}
	dart_cache_sync(orig_dp, npages);

	if (dart_is_u4) {
		rpn = index;
		while (npages--)
			dart_tlb_invalidate_one(rpn++);
	} else {
		dart_dirty = 1;
	}
	return 0;
}