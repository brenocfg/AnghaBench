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
struct vm_area_struct {int /*<<< orphan*/  vm_mm; } ;
typedef  int /*<<< orphan*/  spinlock_t ;
typedef  int /*<<< orphan*/  pud_t ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 int do_adjust_pte (struct vm_area_struct*,unsigned long,unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_pte_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_pte_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ pgd_none_or_clear_bad (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pgd_offset (int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ pmd_none_or_clear_bad (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pmd_offset (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/ * pte_lockptr (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pte_offset_map (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  pte_unmap (int /*<<< orphan*/ *) ; 
 scalar_t__ pud_none_or_clear_bad (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pud_offset (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int adjust_pte(struct vm_area_struct *vma, unsigned long address,
	unsigned long pfn)
{
	spinlock_t *ptl;
	pgd_t *pgd;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte;
	int ret;

	pgd = pgd_offset(vma->vm_mm, address);
	if (pgd_none_or_clear_bad(pgd))
		return 0;

	pud = pud_offset(pgd, address);
	if (pud_none_or_clear_bad(pud))
		return 0;

	pmd = pmd_offset(pud, address);
	if (pmd_none_or_clear_bad(pmd))
		return 0;

	/*
	 * This is called while another page table is mapped, so we
	 * must use the nested version.  This also means we need to
	 * open-code the spin-locking.
	 */
	ptl = pte_lockptr(vma->vm_mm, pmd);
	pte = pte_offset_map(pmd, address);
	do_pte_lock(ptl);

	ret = do_adjust_pte(vma, address, pfn, pte);

	do_pte_unlock(ptl);
	pte_unmap(pte);

	return ret;
}