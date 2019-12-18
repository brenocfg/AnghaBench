#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pud_t ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  pgprot_t ;
struct TYPE_4__ {int /*<<< orphan*/  pgd; } ;
typedef  TYPE_1__ pgd_t ;
typedef  int /*<<< orphan*/  p4d_t ;

/* Variables and functions */
 int /*<<< orphan*/  _PAGE_NX ; 
 int /*<<< orphan*/ * p4d_alloc (int /*<<< orphan*/ *,TYPE_1__*,unsigned long) ; 
 int /*<<< orphan*/  pfn_pte (unsigned long,int /*<<< orphan*/ ) ; 
 TYPE_1__* pgd_offset (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/ * pmd_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/ * pte_alloc_map (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  pte_unmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pud_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  set_pte_at (int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tboot_mm ; 

__attribute__((used)) static int map_tboot_page(unsigned long vaddr, unsigned long pfn,
			  pgprot_t prot)
{
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte;

	pgd = pgd_offset(&tboot_mm, vaddr);
	p4d = p4d_alloc(&tboot_mm, pgd, vaddr);
	if (!p4d)
		return -1;
	pud = pud_alloc(&tboot_mm, p4d, vaddr);
	if (!pud)
		return -1;
	pmd = pmd_alloc(&tboot_mm, pud, vaddr);
	if (!pmd)
		return -1;
	pte = pte_alloc_map(&tboot_mm, pmd, vaddr);
	if (!pte)
		return -1;
	set_pte_at(&tboot_mm, vaddr, pte, pfn_pte(pfn, prot));
	pte_unmap(pte);

	/*
	 * PTI poisons low addresses in the kernel page tables in the
	 * name of making them unusable for userspace.  To execute
	 * code at such a low address, the poison must be cleared.
	 *
	 * Note: 'pgd' actually gets set in p4d_alloc() _or_
	 * pud_alloc() depending on 4/5-level paging.
	 */
	pgd->pgd &= ~_PAGE_NX;

	return 0;
}