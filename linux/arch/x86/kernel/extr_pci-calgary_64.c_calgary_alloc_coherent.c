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
typedef  int /*<<< orphan*/  gfp_t ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 scalar_t__ DMA_MAPPING_ERROR ; 
 size_t PAGE_ALIGN (size_t) ; 
 size_t PAGE_SHIFT ; 
 scalar_t__ __get_free_pages (int /*<<< orphan*/ ,unsigned int) ; 
 struct iommu_table* find_iommu_table (struct device*) ; 
 int /*<<< orphan*/  free_pages (unsigned long,unsigned int) ; 
 unsigned int get_order (size_t) ; 
 scalar_t__ iommu_alloc (struct device*,struct iommu_table*,void*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static void* calgary_alloc_coherent(struct device *dev, size_t size,
	dma_addr_t *dma_handle, gfp_t flag, unsigned long attrs)
{
	void *ret = NULL;
	dma_addr_t mapping;
	unsigned int npages, order;
	struct iommu_table *tbl = find_iommu_table(dev);

	size = PAGE_ALIGN(size); /* size rounded up to full pages */
	npages = size >> PAGE_SHIFT;
	order = get_order(size);

	/* alloc enough pages (and possibly more) */
	ret = (void *)__get_free_pages(flag, order);
	if (!ret)
		goto error;
	memset(ret, 0, size);

	/* set up tces to cover the allocated range */
	mapping = iommu_alloc(dev, tbl, ret, npages, DMA_BIDIRECTIONAL);
	if (mapping == DMA_MAPPING_ERROR)
		goto free;
	*dma_handle = mapping;
	return ret;
free:
	free_pages((unsigned long)ret, get_order(size));
	ret = NULL;
error:
	return ret;
}