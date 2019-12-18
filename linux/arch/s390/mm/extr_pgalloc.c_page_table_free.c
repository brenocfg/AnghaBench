#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct page {int /*<<< orphan*/  _refcount; int /*<<< orphan*/  lru; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  pgtable_list; } ;
struct mm_struct {TYPE_1__ context; } ;
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 int PAGE_MASK ; 
 int PAGE_SHIFT ; 
 int PTRS_PER_PTE ; 
 int /*<<< orphan*/  __free_page (struct page*) ; 
 int __pa (unsigned long*) ; 
 unsigned int atomic_xor_bits (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mm_alloc_pgste (struct mm_struct*) ; 
 struct page* pfn_to_page (int) ; 
 int /*<<< orphan*/  pgtable_pte_page_dtor (struct page*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void page_table_free(struct mm_struct *mm, unsigned long *table)
{
	struct page *page;
	unsigned int bit, mask;

	page = pfn_to_page(__pa(table) >> PAGE_SHIFT);
	if (!mm_alloc_pgste(mm)) {
		/* Free 2K page table fragment of a 4K page */
		bit = (__pa(table) & ~PAGE_MASK)/(PTRS_PER_PTE*sizeof(pte_t));
		spin_lock_bh(&mm->context.lock);
		mask = atomic_xor_bits(&page->_refcount, 1U << (bit + 24));
		mask >>= 24;
		if (mask & 3)
			list_add(&page->lru, &mm->context.pgtable_list);
		else
			list_del(&page->lru);
		spin_unlock_bh(&mm->context.lock);
		if (mask != 0)
			return;
	} else {
		atomic_xor_bits(&page->_refcount, 3U << 24);
	}

	pgtable_pte_page_dtor(page);
	__free_page(page);
}