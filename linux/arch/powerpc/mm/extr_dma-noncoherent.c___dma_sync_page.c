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
typedef  unsigned int phys_addr_t ;

/* Variables and functions */
 unsigned int PAGE_MASK ; 
 unsigned int PAGE_SHIFT ; 
 int /*<<< orphan*/  __dma_sync (void*,size_t,int) ; 
 int /*<<< orphan*/  __dma_sync_page_highmem (struct page*,unsigned int,size_t,int) ; 
 scalar_t__ page_address (struct page*) ; 
 struct page* pfn_to_page (unsigned int) ; 

__attribute__((used)) static void __dma_sync_page(phys_addr_t paddr, size_t size, int dir)
{
	struct page *page = pfn_to_page(paddr >> PAGE_SHIFT);
	unsigned offset = paddr & ~PAGE_MASK;

#ifdef CONFIG_HIGHMEM
	__dma_sync_page_highmem(page, offset, size, dir);
#else
	unsigned long start = (unsigned long)page_address(page) + offset;
	__dma_sync((void *)start, size, dir);
#endif
}