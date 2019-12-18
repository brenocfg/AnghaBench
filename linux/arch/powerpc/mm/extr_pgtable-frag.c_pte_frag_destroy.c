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
struct page {int /*<<< orphan*/  pt_frag_refcount; } ;

/* Variables and functions */
 unsigned long PAGE_MASK ; 
 scalar_t__ PTE_FRAG_NR ; 
 unsigned long PTE_FRAG_SIZE_SHIFT ; 
 int /*<<< orphan*/  __free_page (struct page*) ; 
 scalar_t__ atomic_sub_and_test (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pgtable_pte_page_dtor (struct page*) ; 
 struct page* virt_to_page (void*) ; 

void pte_frag_destroy(void *pte_frag)
{
	int count;
	struct page *page;

	page = virt_to_page(pte_frag);
	/* drop all the pending references */
	count = ((unsigned long)pte_frag & ~PAGE_MASK) >> PTE_FRAG_SIZE_SHIFT;
	/* We allow PTE_FRAG_NR fragments from a PTE page */
	if (atomic_sub_and_test(PTE_FRAG_NR - count, &page->pt_frag_refcount)) {
		pgtable_pte_page_dtor(page);
		__free_page(page);
	}
}