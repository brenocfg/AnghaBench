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
typedef  int /*<<< orphan*/  pud_t ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  pgd_t ;
typedef  int /*<<< orphan*/  p4d_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_KERNEL_EXEC ; 
 unsigned long PAGE_SHIFT ; 
 int _PAGE_PRESENT ; 
 int _PAGE_TABLE ; 
 int __pa (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __pgd (int) ; 
 int /*<<< orphan*/  __pmd (int) ; 
 int /*<<< orphan*/ * p4d_offset (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  pfn_pte (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgd_index (unsigned long) ; 
 int pgd_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pmd_offset (int /*<<< orphan*/ *,unsigned long) ; 
 int pmd_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pte_offset_kernel (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/ * pud_offset (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  set_pgd (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_pmd (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_pte (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void machine_kexec_page_table_set_one(
	pgd_t *pgd, pmd_t *pmd, pte_t *pte,
	unsigned long vaddr, unsigned long paddr)
{
	p4d_t *p4d;
	pud_t *pud;

	pgd += pgd_index(vaddr);
#ifdef CONFIG_X86_PAE
	if (!(pgd_val(*pgd) & _PAGE_PRESENT))
		set_pgd(pgd, __pgd(__pa(pmd) | _PAGE_PRESENT));
#endif
	p4d = p4d_offset(pgd, vaddr);
	pud = pud_offset(p4d, vaddr);
	pmd = pmd_offset(pud, vaddr);
	if (!(pmd_val(*pmd) & _PAGE_PRESENT))
		set_pmd(pmd, __pmd(__pa(pte) | _PAGE_TABLE));
	pte = pte_offset_kernel(pmd, vaddr);
	set_pte(pte, pfn_pte(paddr >> PAGE_SHIFT, PAGE_KERNEL_EXEC));
}