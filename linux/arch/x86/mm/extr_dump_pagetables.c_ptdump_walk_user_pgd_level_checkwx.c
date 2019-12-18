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
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 int /*<<< orphan*/ * INIT_PGD ; 
 int /*<<< orphan*/  X86_FEATURE_PTI ; 
 int _PAGE_NX ; 
 int __supported_pte_mask ; 
 int /*<<< orphan*/  boot_cpu_has (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kernel_to_user_pgdp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  ptdump_walk_pgd_level_core (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 

void ptdump_walk_user_pgd_level_checkwx(void)
{
#ifdef CONFIG_PAGE_TABLE_ISOLATION
	pgd_t *pgd = INIT_PGD;

	if (!(__supported_pte_mask & _PAGE_NX) ||
	    !boot_cpu_has(X86_FEATURE_PTI))
		return;

	pr_info("x86/mm: Checking user space page tables\n");
	pgd = kernel_to_user_pgdp(pgd);
	ptdump_walk_pgd_level_core(NULL, pgd, true, false);
#endif
}