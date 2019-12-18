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
struct device {scalar_t__ coherent_dma_mask; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 scalar_t__ DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  DMA_MAPPING_ERROR ; 
 void* dma_direct_alloc_pages (struct device*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  dma_direct_free_pages (struct device*,size_t,void*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  dma_map_area (struct device*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  flush_gart () ; 
 int /*<<< orphan*/  force_iommu ; 
 unsigned long get_order (size_t) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  virt_to_phys (void*) ; 

__attribute__((used)) static void *
gart_alloc_coherent(struct device *dev, size_t size, dma_addr_t *dma_addr,
		    gfp_t flag, unsigned long attrs)
{
	void *vaddr;

	vaddr = dma_direct_alloc_pages(dev, size, dma_addr, flag, attrs);
	if (!vaddr ||
	    !force_iommu || dev->coherent_dma_mask <= DMA_BIT_MASK(24))
		return vaddr;

	*dma_addr = dma_map_area(dev, virt_to_phys(vaddr), size,
			DMA_BIDIRECTIONAL, (1UL << get_order(size)) - 1);
	flush_gart();
	if (unlikely(*dma_addr == DMA_MAPPING_ERROR))
		goto out_free;
	return vaddr;
out_free:
	dma_direct_free_pages(dev, size, vaddr, *dma_addr, attrs);
	return NULL;
}