#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct iommu_table {unsigned long it_page_shift; TYPE_1__* it_ops; scalar_t__ it_offset; } ;
struct device {int dummy; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
typedef  unsigned long dma_addr_t ;
struct TYPE_2__ {int (* set ) (struct iommu_table*,unsigned long,unsigned int,unsigned long,int,unsigned long) ;int /*<<< orphan*/  (* flush ) (struct iommu_table*) ;} ;

/* Variables and functions */
 unsigned long DMA_MAPPING_ERROR ; 
 unsigned long IOMMU_PAGE_MASK (struct iommu_table*) ; 
 int /*<<< orphan*/  __iommu_free (struct iommu_table*,unsigned long,unsigned int) ; 
 unsigned long iommu_range_alloc (struct device*,struct iommu_table*,unsigned int,int /*<<< orphan*/ *,unsigned long,unsigned int) ; 
 int /*<<< orphan*/  mb () ; 
 int stub1 (struct iommu_table*,unsigned long,unsigned int,unsigned long,int,unsigned long) ; 
 int /*<<< orphan*/  stub2 (struct iommu_table*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static dma_addr_t iommu_alloc(struct device *dev, struct iommu_table *tbl,
			      void *page, unsigned int npages,
			      enum dma_data_direction direction,
			      unsigned long mask, unsigned int align_order,
			      unsigned long attrs)
{
	unsigned long entry;
	dma_addr_t ret = DMA_MAPPING_ERROR;
	int build_fail;

	entry = iommu_range_alloc(dev, tbl, npages, NULL, mask, align_order);

	if (unlikely(entry == DMA_MAPPING_ERROR))
		return DMA_MAPPING_ERROR;

	entry += tbl->it_offset;	/* Offset into real TCE table */
	ret = entry << tbl->it_page_shift;	/* Set the return dma address */

	/* Put the TCEs in the HW table */
	build_fail = tbl->it_ops->set(tbl, entry, npages,
				      (unsigned long)page &
				      IOMMU_PAGE_MASK(tbl), direction, attrs);

	/* tbl->it_ops->set() only returns non-zero for transient errors.
	 * Clean up the table bitmap in this case and return
	 * DMA_MAPPING_ERROR. For all other errors the functionality is
	 * not altered.
	 */
	if (unlikely(build_fail)) {
		__iommu_free(tbl, ret, npages);
		return DMA_MAPPING_ERROR;
	}

	/* Flush/invalidate TLB caches if necessary */
	if (tbl->it_ops->flush)
		tbl->it_ops->flush(tbl);

	/* Make sure updates are seen by hardware */
	mb();

	return ret;
}