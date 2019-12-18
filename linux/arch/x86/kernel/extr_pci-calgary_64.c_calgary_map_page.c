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
struct page {int dummy; } ;
struct iommu_table {int dummy; } ;
struct device {int dummy; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct iommu_table* find_iommu_table (struct device*) ; 
 int /*<<< orphan*/  iommu_alloc (struct device*,struct iommu_table*,void*,unsigned int,int) ; 
 unsigned int iommu_num_pages (unsigned long,size_t,int /*<<< orphan*/ ) ; 
 void* page_address (struct page*) ; 

__attribute__((used)) static dma_addr_t calgary_map_page(struct device *dev, struct page *page,
				   unsigned long offset, size_t size,
				   enum dma_data_direction dir,
				   unsigned long attrs)
{
	void *vaddr = page_address(page) + offset;
	unsigned long uaddr;
	unsigned int npages;
	struct iommu_table *tbl = find_iommu_table(dev);

	uaddr = (unsigned long)vaddr;
	npages = iommu_num_pages(uaddr, size, PAGE_SIZE);

	return iommu_alloc(dev, tbl, vaddr, npages, dir);
}