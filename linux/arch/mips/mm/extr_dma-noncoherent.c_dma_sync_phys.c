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
typedef  unsigned long phys_addr_t ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;

/* Variables and functions */
 unsigned long PAGE_MASK ; 
 unsigned long PAGE_SHIFT ; 
 unsigned long PAGE_SIZE ; 
 scalar_t__ PageHighMem (struct page*) ; 
 int /*<<< orphan*/  dma_sync_virt (void*,size_t,int) ; 
 void* kmap_atomic (struct page*) ; 
 int /*<<< orphan*/  kunmap_atomic (void*) ; 
 void* page_address (struct page*) ; 
 struct page* pfn_to_page (unsigned long) ; 

__attribute__((used)) static inline void dma_sync_phys(phys_addr_t paddr, size_t size,
		enum dma_data_direction dir)
{
	struct page *page = pfn_to_page(paddr >> PAGE_SHIFT);
	unsigned long offset = paddr & ~PAGE_MASK;
	size_t left = size;

	do {
		size_t len = left;

		if (PageHighMem(page)) {
			void *addr;

			if (offset + len > PAGE_SIZE)
				len = PAGE_SIZE - offset;

			addr = kmap_atomic(page);
			dma_sync_virt(addr + offset, len, dir);
			kunmap_atomic(addr);
		} else
			dma_sync_virt(page_address(page) + offset, size, dir);
		offset = 0;
		page++;
		left -= len;
	} while (left);
}