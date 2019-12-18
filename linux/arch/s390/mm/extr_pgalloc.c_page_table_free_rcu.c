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
struct page {int /*<<< orphan*/  lru; int /*<<< orphan*/  _refcount; } ;
struct mmu_gather {struct mm_struct* mm; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  pgtable_list; } ;
struct mm_struct {TYPE_1__ context; } ;
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 int PAGE_MASK ; 
 unsigned int PAGE_SHIFT ; 
 int PTRS_PER_PTE ; 
 unsigned int __pa (unsigned long*) ; 
 unsigned int atomic_xor_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  gmap_unlink (struct mm_struct*,unsigned long*,unsigned long) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 scalar_t__ mm_alloc_pgste (struct mm_struct*) ; 
 struct page* pfn_to_page (unsigned int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tlb_remove_table (struct mmu_gather*,unsigned long*) ; 

void page_table_free_rcu(struct mmu_gather *tlb, unsigned long *table,
			 unsigned long vmaddr)
{
	struct mm_struct *mm;
	struct page *page;
	unsigned int bit, mask;

	mm = tlb->mm;
	page = pfn_to_page(__pa(table) >> PAGE_SHIFT);
	if (mm_alloc_pgste(mm)) {
		gmap_unlink(mm, table, vmaddr);
		table = (unsigned long *) (__pa(table) | 3);
		tlb_remove_table(tlb, table);
		return;
	}
	bit = (__pa(table) & ~PAGE_MASK) / (PTRS_PER_PTE*sizeof(pte_t));
	spin_lock_bh(&mm->context.lock);
	mask = atomic_xor_bits(&page->_refcount, 0x11U << (bit + 24));
	mask >>= 24;
	if (mask & 3)
		list_add_tail(&page->lru, &mm->context.pgtable_list);
	else
		list_del(&page->lru);
	spin_unlock_bh(&mm->context.lock);
	table = (unsigned long *) (__pa(table) | (1U << bit));
	tlb_remove_table(tlb, table);
}