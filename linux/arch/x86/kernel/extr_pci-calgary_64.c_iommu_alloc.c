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
struct iommu_table {int dummy; } ;
struct device {int dummy; } ;
typedef  unsigned long dma_addr_t ;

/* Variables and functions */
 unsigned long DMA_MAPPING_ERROR ; 
 unsigned long PAGE_MASK ; 
 unsigned long PAGE_SHIFT ; 
 unsigned long iommu_range_alloc (struct device*,struct iommu_table*,unsigned int) ; 
 int /*<<< orphan*/  pr_warn (char*,unsigned int,struct iommu_table*) ; 
 int /*<<< orphan*/  tce_build (struct iommu_table*,unsigned long,unsigned int,unsigned long,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static dma_addr_t iommu_alloc(struct device *dev, struct iommu_table *tbl,
			      void *vaddr, unsigned int npages, int direction)
{
	unsigned long entry;
	dma_addr_t ret;

	entry = iommu_range_alloc(dev, tbl, npages);
	if (unlikely(entry == DMA_MAPPING_ERROR)) {
		pr_warn("failed to allocate %u pages in iommu %p\n",
			npages, tbl);
		return DMA_MAPPING_ERROR;
	}

	/* set the return dma address */
	ret = (entry << PAGE_SHIFT) | ((unsigned long)vaddr & ~PAGE_MASK);

	/* put the TCEs in the HW table */
	tce_build(tbl, entry, npages, (unsigned long)vaddr & PAGE_MASK,
		  direction);
	return ret;
}