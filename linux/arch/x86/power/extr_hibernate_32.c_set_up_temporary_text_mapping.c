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
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  PAGE_KERNEL_EXEC ; 
 int /*<<< orphan*/  PAGE_KERNEL_LARGE_EXEC ; 
 int PAGE_MASK ; 
 int PMD_MASK ; 
 int /*<<< orphan*/  X86_FEATURE_PSE ; 
 int /*<<< orphan*/  __pmd (int) ; 
 int /*<<< orphan*/  __pte (int) ; 
 scalar_t__ boot_cpu_has (int /*<<< orphan*/ ) ; 
 int jump_address_phys ; 
 int pgd_index (int /*<<< orphan*/ ) ; 
 int pgprot_val (int /*<<< orphan*/ ) ; 
 int pmd_index (int /*<<< orphan*/ ) ; 
 int pte_index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  restore_jump_address ; 
 int /*<<< orphan*/ * resume_one_md_table_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * resume_one_page_table_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_pmd (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_pte (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_up_temporary_text_mapping(pgd_t *pgd_base)
{
	pgd_t *pgd;
	pmd_t *pmd;
	pte_t *pte;

	pgd = pgd_base + pgd_index(restore_jump_address);

	pmd = resume_one_md_table_init(pgd);
	if (!pmd)
		return -ENOMEM;

	if (boot_cpu_has(X86_FEATURE_PSE)) {
		set_pmd(pmd + pmd_index(restore_jump_address),
		__pmd((jump_address_phys & PMD_MASK) | pgprot_val(PAGE_KERNEL_LARGE_EXEC)));
	} else {
		pte = resume_one_page_table_init(pmd);
		if (!pte)
			return -ENOMEM;
		set_pte(pte + pte_index(restore_jump_address),
		__pte((jump_address_phys & PAGE_MASK) | pgprot_val(PAGE_KERNEL_EXEC)));
	}

	return 0;
}