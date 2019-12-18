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
struct mm_struct {int /*<<< orphan*/  pgd; } ;
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 int /*<<< orphan*/  __set_huge_pte_at (struct mm_struct*,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgd_spinlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_same (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

int huge_ptep_set_access_flags(struct vm_area_struct *vma,
				unsigned long addr, pte_t *ptep,
				pte_t pte, int dirty)
{
	unsigned long flags;
	int changed;
	struct mm_struct *mm = vma->vm_mm;

	spin_lock_irqsave(pgd_spinlock((mm)->pgd), flags);
	changed = !pte_same(*ptep, pte);
	if (changed) {
		__set_huge_pte_at(mm, addr, ptep, pte);
	}
	spin_unlock_irqrestore(pgd_spinlock((mm)->pgd), flags);
	return changed;
}