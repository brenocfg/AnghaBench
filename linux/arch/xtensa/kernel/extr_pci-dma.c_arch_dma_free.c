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
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 unsigned long PAGE_ALIGN (size_t) ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  PHYS_PFN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __free_pages (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_common_free_remap (void*,size_t) ; 
 int /*<<< orphan*/  dma_release_from_contiguous (struct device*,struct page*,unsigned long) ; 
 int /*<<< orphan*/  dma_to_phys (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_order (size_t) ; 
 struct page* pfn_to_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_vaddr_to_cached (void*) ; 
 scalar_t__ platform_vaddr_uncached (void*) ; 
 struct page* virt_to_page (int /*<<< orphan*/ ) ; 

void arch_dma_free(struct device *dev, size_t size, void *vaddr,
		dma_addr_t dma_handle, unsigned long attrs)
{
	unsigned long count = PAGE_ALIGN(size) >> PAGE_SHIFT;
	struct page *page;

	if (platform_vaddr_uncached(vaddr)) {
		page = virt_to_page(platform_vaddr_to_cached(vaddr));
	} else {
#ifdef CONFIG_MMU
		dma_common_free_remap(vaddr, size);
#endif
		page = pfn_to_page(PHYS_PFN(dma_to_phys(dev, dma_handle)));
	}

	if (!dma_release_from_contiguous(dev, page, count))
		__free_pages(page, get_order(size));
}