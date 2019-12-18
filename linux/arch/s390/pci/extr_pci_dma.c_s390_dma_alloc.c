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
struct zpci_dev {int /*<<< orphan*/  allocated_pages; } ;
struct page {int dummy; } ;
struct device {int dummy; } ;
typedef  int gfp_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 size_t PAGE_ALIGN (size_t) ; 
 size_t PAGE_SIZE ; 
 int __GFP_ZERO ; 
 struct page* alloc_pages (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic64_add (size_t,int /*<<< orphan*/ *) ; 
 scalar_t__ dma_mapping_error (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_pages (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_order (size_t) ; 
 unsigned long page_to_phys (struct page*) ; 
 int /*<<< orphan*/  s390_dma_map_pages (struct device*,struct page*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_pci_dev (struct device*) ; 
 struct zpci_dev* to_zpci (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *s390_dma_alloc(struct device *dev, size_t size,
			    dma_addr_t *dma_handle, gfp_t flag,
			    unsigned long attrs)
{
	struct zpci_dev *zdev = to_zpci(to_pci_dev(dev));
	struct page *page;
	unsigned long pa;
	dma_addr_t map;

	size = PAGE_ALIGN(size);
	page = alloc_pages(flag | __GFP_ZERO, get_order(size));
	if (!page)
		return NULL;

	pa = page_to_phys(page);
	map = s390_dma_map_pages(dev, page, 0, size, DMA_BIDIRECTIONAL, 0);
	if (dma_mapping_error(dev, map)) {
		free_pages(pa, get_order(size));
		return NULL;
	}

	atomic64_add(size / PAGE_SIZE, &zdev->allocated_pages);
	if (dma_handle)
		*dma_handle = map;
	return (void *) pa;
}