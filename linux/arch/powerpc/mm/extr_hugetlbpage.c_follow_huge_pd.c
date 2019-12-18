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
struct vm_area_struct {struct mm_struct* vm_mm; } ;
struct page {int dummy; } ;
struct mm_struct {int /*<<< orphan*/  page_table_lock; } ;
typedef  int /*<<< orphan*/  spinlock_t ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  hugepd_t ;

/* Variables and functions */
 int FOLL_GET ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  __migration_entry_wait (struct mm_struct*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 int hugepd_shift (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * hugepte_offset (int /*<<< orphan*/ ,unsigned long,int) ; 
 scalar_t__ is_hugetlb_entry_migration (int /*<<< orphan*/ ) ; 
 struct page* pte_page (int /*<<< orphan*/ ) ; 
 scalar_t__ pte_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

struct page *follow_huge_pd(struct vm_area_struct *vma,
			    unsigned long address, hugepd_t hpd,
			    int flags, int pdshift)
{
	pte_t *ptep;
	spinlock_t *ptl;
	struct page *page = NULL;
	unsigned long mask;
	int shift = hugepd_shift(hpd);
	struct mm_struct *mm = vma->vm_mm;

retry:
	/*
	 * hugepage directory entries are protected by mm->page_table_lock
	 * Use this instead of huge_pte_lockptr
	 */
	ptl = &mm->page_table_lock;
	spin_lock(ptl);

	ptep = hugepte_offset(hpd, address, pdshift);
	if (pte_present(*ptep)) {
		mask = (1UL << shift) - 1;
		page = pte_page(*ptep);
		page += ((address & mask) >> PAGE_SHIFT);
		if (flags & FOLL_GET)
			get_page(page);
	} else {
		if (is_hugetlb_entry_migration(*ptep)) {
			spin_unlock(ptl);
			__migration_entry_wait(mm, ptep, ptl);
			goto retry;
		}
	}
	spin_unlock(ptl);
	return page;
}