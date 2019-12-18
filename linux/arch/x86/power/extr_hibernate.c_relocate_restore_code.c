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
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int _PAGE_NX ; 
 int /*<<< orphan*/  __flush_tlb_all () ; 
 int /*<<< orphan*/  __p4d (int) ; 
 int /*<<< orphan*/  __pmd (int) ; 
 int /*<<< orphan*/  __pte (int) ; 
 int /*<<< orphan*/  __pud (int) ; 
 scalar_t__ __va (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  core_restore_code ; 
 scalar_t__ get_safe_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ p4d_large (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * p4d_offset (int /*<<< orphan*/ *,scalar_t__) ; 
 int p4d_val (int /*<<< orphan*/ ) ; 
 int pgd_index (scalar_t__) ; 
 scalar_t__ pmd_large (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pmd_offset (int /*<<< orphan*/ *,scalar_t__) ; 
 int pmd_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pte_offset_kernel (int /*<<< orphan*/ *,scalar_t__) ; 
 int pte_val (int /*<<< orphan*/ ) ; 
 scalar_t__ pud_large (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pud_offset (int /*<<< orphan*/ *,scalar_t__) ; 
 int pud_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_cr3_pa () ; 
 scalar_t__ relocated_restore_code ; 
 int /*<<< orphan*/  set_p4d (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_pmd (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_pte (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_pud (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int relocate_restore_code(void)
{
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte;

	relocated_restore_code = get_safe_page(GFP_ATOMIC);
	if (!relocated_restore_code)
		return -ENOMEM;

	memcpy((void *)relocated_restore_code, core_restore_code, PAGE_SIZE);

	/* Make the page containing the relocated code executable */
	pgd = (pgd_t *)__va(read_cr3_pa()) +
		pgd_index(relocated_restore_code);
	p4d = p4d_offset(pgd, relocated_restore_code);
	if (p4d_large(*p4d)) {
		set_p4d(p4d, __p4d(p4d_val(*p4d) & ~_PAGE_NX));
		goto out;
	}
	pud = pud_offset(p4d, relocated_restore_code);
	if (pud_large(*pud)) {
		set_pud(pud, __pud(pud_val(*pud) & ~_PAGE_NX));
		goto out;
	}
	pmd = pmd_offset(pud, relocated_restore_code);
	if (pmd_large(*pmd)) {
		set_pmd(pmd, __pmd(pmd_val(*pmd) & ~_PAGE_NX));
		goto out;
	}
	pte = pte_offset_kernel(pmd, relocated_restore_code);
	set_pte(pte, __pte(pte_val(*pte) & ~_PAGE_NX));
out:
	__flush_tlb_all();
	return 0;
}