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

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  PageCompound (struct page*) ; 
 int /*<<< orphan*/  PageHighMem (struct page*) ; 
 int /*<<< orphan*/  __flush_dcache_icache (void*) ; 
 int compound_nr (struct page*) ; 
 void* kmap_atomic (struct page*) ; 
 int /*<<< orphan*/  kunmap_atomic (void*) ; 
 void* page_address (struct page*) ; 

void flush_dcache_icache_hugepage(struct page *page)
{
	int i;
	void *start;

	BUG_ON(!PageCompound(page));

	for (i = 0; i < compound_nr(page); i++) {
		if (!PageHighMem(page)) {
			__flush_dcache_icache(page_address(page+i));
		} else {
			start = kmap_atomic(page+i);
			__flush_dcache_icache(start);
			kunmap_atomic(start);
		}
	}
}