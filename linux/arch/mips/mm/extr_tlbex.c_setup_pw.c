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

/* Variables and functions */
 int PAGE_SHIFT ; 
 int PGDIR_SHIFT ; 
 int PGD_ORDER ; 
 int PMD_SHIFT ; 
 int /*<<< orphan*/  _PAGE_GLOBAL ; 
 int /*<<< orphan*/  _PAGE_HUGE ; 
 unsigned long ilog2 (int /*<<< orphan*/ ) ; 
 int kscratch_used_mask ; 
 scalar_t__ swapper_pg_dir ; 
 int /*<<< orphan*/  write_c0_kpgd (long) ; 
 int /*<<< orphan*/  write_c0_pwctl (int) ; 
 int /*<<< orphan*/  write_c0_pwfield (unsigned long) ; 
 int /*<<< orphan*/  write_c0_pwsize (int) ; 

__attribute__((used)) static void setup_pw(void)
{
	unsigned long pgd_i, pgd_w;
#ifndef __PAGETABLE_PMD_FOLDED
	unsigned long pmd_i, pmd_w;
#endif
	unsigned long pt_i, pt_w;
	unsigned long pte_i, pte_w;
#ifdef CONFIG_MIPS_HUGE_TLB_SUPPORT
	unsigned long psn;

	psn = ilog2(_PAGE_HUGE);     /* bit used to indicate huge page */
#endif
	pgd_i = PGDIR_SHIFT;  /* 1st level PGD */
#ifndef __PAGETABLE_PMD_FOLDED
	pgd_w = PGDIR_SHIFT - PMD_SHIFT + PGD_ORDER;

	pmd_i = PMD_SHIFT;    /* 2nd level PMD */
	pmd_w = PMD_SHIFT - PAGE_SHIFT;
#else
	pgd_w = PGDIR_SHIFT - PAGE_SHIFT + PGD_ORDER;
#endif

	pt_i  = PAGE_SHIFT;    /* 3rd level PTE */
	pt_w  = PAGE_SHIFT - 3;

	pte_i = ilog2(_PAGE_GLOBAL);
	pte_w = 0;

#ifndef __PAGETABLE_PMD_FOLDED
	write_c0_pwfield(pgd_i << 24 | pmd_i << 12 | pt_i << 6 | pte_i);
	write_c0_pwsize(1 << 30 | pgd_w << 24 | pmd_w << 12 | pt_w << 6 | pte_w);
#else
	write_c0_pwfield(pgd_i << 24 | pt_i << 6 | pte_i);
	write_c0_pwsize(1 << 30 | pgd_w << 24 | pt_w << 6 | pte_w);
#endif

#ifdef CONFIG_MIPS_HUGE_TLB_SUPPORT
	write_c0_pwctl(1 << 6 | psn);
#endif
	write_c0_kpgd((long)swapper_pg_dir);
	kscratch_used_mask |= (1 << 7); /* KScratch6 is used for KPGD */
}