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
struct zpci_dev {int /*<<< orphan*/  mapped_pages; } ;
struct scatterlist {scalar_t__ offset; scalar_t__ length; } ;
struct device {int dummy; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 scalar_t__ DMA_MAPPING_ERROR ; 
 int DMA_NONE ; 
 int DMA_TO_DEVICE ; 
 int ENOMEM ; 
 unsigned long PAGE_ALIGN (size_t) ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  ZPCI_PTE_INVALID ; 
 int ZPCI_PTE_VALID ; 
 int ZPCI_TABLE_PROTECTED ; 
 int __dma_purge_tlb (struct zpci_dev*,scalar_t__,size_t,int) ; 
 int __dma_update_trans (struct zpci_dev*,unsigned long,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  atomic64_add (unsigned long,int /*<<< orphan*/ *) ; 
 scalar_t__ dma_alloc_address (struct device*,unsigned long) ; 
 int /*<<< orphan*/  dma_free_address (struct device*,scalar_t__,unsigned long) ; 
 int /*<<< orphan*/  dma_update_trans (struct zpci_dev*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 unsigned long page_to_phys (int /*<<< orphan*/ ) ; 
 struct scatterlist* sg_next (struct scatterlist*) ; 
 int /*<<< orphan*/  sg_page (struct scatterlist*) ; 
 int /*<<< orphan*/  to_pci_dev (struct device*) ; 
 struct zpci_dev* to_zpci (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zpci_err (char*) ; 
 int /*<<< orphan*/  zpci_err_dma (int,unsigned long) ; 

__attribute__((used)) static int __s390_dma_map_sg(struct device *dev, struct scatterlist *sg,
			     size_t size, dma_addr_t *handle,
			     enum dma_data_direction dir)
{
	unsigned long nr_pages = PAGE_ALIGN(size) >> PAGE_SHIFT;
	struct zpci_dev *zdev = to_zpci(to_pci_dev(dev));
	dma_addr_t dma_addr_base, dma_addr;
	int flags = ZPCI_PTE_VALID;
	struct scatterlist *s;
	unsigned long pa = 0;
	int ret;

	dma_addr_base = dma_alloc_address(dev, nr_pages);
	if (dma_addr_base == DMA_MAPPING_ERROR)
		return -ENOMEM;

	dma_addr = dma_addr_base;
	if (dir == DMA_NONE || dir == DMA_TO_DEVICE)
		flags |= ZPCI_TABLE_PROTECTED;

	for (s = sg; dma_addr < dma_addr_base + size; s = sg_next(s)) {
		pa = page_to_phys(sg_page(s));
		ret = __dma_update_trans(zdev, pa, dma_addr,
					 s->offset + s->length, flags);
		if (ret)
			goto unmap;

		dma_addr += s->offset + s->length;
	}
	ret = __dma_purge_tlb(zdev, dma_addr_base, size, flags);
	if (ret)
		goto unmap;

	*handle = dma_addr_base;
	atomic64_add(nr_pages, &zdev->mapped_pages);

	return ret;

unmap:
	dma_update_trans(zdev, 0, dma_addr_base, dma_addr - dma_addr_base,
			 ZPCI_PTE_INVALID);
	dma_free_address(dev, dma_addr_base, nr_pages);
	zpci_err("map error:\n");
	zpci_err_dma(ret, pa);
	return ret;
}