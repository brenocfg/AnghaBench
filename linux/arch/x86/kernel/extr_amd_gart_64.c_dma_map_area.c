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
typedef  size_t dma_addr_t ;

/* Variables and functions */
 size_t DMA_MAPPING_ERROR ; 
 size_t GART_MAX_PHYS_ADDR ; 
 int /*<<< orphan*/  GPTE_ENCODE (size_t) ; 
 size_t PAGE_MASK ; 
 size_t PAGE_SIZE ; 
 unsigned long alloc_iommu (struct device*,unsigned long,unsigned long) ; 
 size_t iommu_bus_base ; 
 int /*<<< orphan*/  iommu_full (struct device*,size_t,int) ; 
 int /*<<< orphan*/ * iommu_gatt_base ; 
 unsigned long iommu_num_pages (size_t,size_t,size_t) ; 
 int /*<<< orphan*/  nonforced_iommu (struct device*,size_t,size_t) ; 
 int /*<<< orphan*/  panic (char*,size_t) ; 
 scalar_t__ panic_on_overflow ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static dma_addr_t dma_map_area(struct device *dev, dma_addr_t phys_mem,
				size_t size, int dir, unsigned long align_mask)
{
	unsigned long npages = iommu_num_pages(phys_mem, size, PAGE_SIZE);
	unsigned long iommu_page;
	int i;

	if (unlikely(phys_mem + size > GART_MAX_PHYS_ADDR))
		return DMA_MAPPING_ERROR;

	iommu_page = alloc_iommu(dev, npages, align_mask);
	if (iommu_page == -1) {
		if (!nonforced_iommu(dev, phys_mem, size))
			return phys_mem;
		if (panic_on_overflow)
			panic("dma_map_area overflow %lu bytes\n", size);
		iommu_full(dev, size, dir);
		return DMA_MAPPING_ERROR;
	}

	for (i = 0; i < npages; i++) {
		iommu_gatt_base[iommu_page + i] = GPTE_ENCODE(phys_mem);
		phys_mem += PAGE_SIZE;
	}
	return iommu_bus_base + iommu_page*PAGE_SIZE + (phys_mem & ~PAGE_MASK);
}