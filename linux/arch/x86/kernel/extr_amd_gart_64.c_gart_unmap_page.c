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
struct device {int dummy; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 scalar_t__ DMA_MAPPING_ERROR ; 
 scalar_t__ PAGE_SHIFT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  free_iommu (unsigned long,int) ; 
 int /*<<< orphan*/  gart_unmapped_entry ; 
 scalar_t__ iommu_bus_base ; 
 int /*<<< orphan*/ * iommu_gatt_base ; 
 int iommu_num_pages (scalar_t__,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ iommu_size ; 

__attribute__((used)) static void gart_unmap_page(struct device *dev, dma_addr_t dma_addr,
			    size_t size, enum dma_data_direction dir,
			    unsigned long attrs)
{
	unsigned long iommu_page;
	int npages;
	int i;

	if (WARN_ON_ONCE(dma_addr == DMA_MAPPING_ERROR))
		return;

	/*
	 * This driver will not always use a GART mapping, but might have
	 * created a direct mapping instead.  If that is the case there is
	 * nothing to unmap here.
	 */
	if (dma_addr < iommu_bus_base ||
	    dma_addr >= iommu_bus_base + iommu_size)
		return;

	iommu_page = (dma_addr - iommu_bus_base)>>PAGE_SHIFT;
	npages = iommu_num_pages(dma_addr, size, PAGE_SIZE);
	for (i = 0; i < npages; i++) {
		iommu_gatt_base[iommu_page + i] = gart_unmapped_entry;
	}
	free_iommu(iommu_page, npages);
}