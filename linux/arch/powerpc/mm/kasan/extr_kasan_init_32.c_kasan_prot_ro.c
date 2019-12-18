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
typedef  int /*<<< orphan*/  pgprot_t ;

/* Variables and functions */
 int /*<<< orphan*/  MMU_FTR_HPTE_TABLE ; 
 int /*<<< orphan*/  PAGE_KERNEL_RO ; 
 int /*<<< orphan*/  PAGE_READONLY ; 
 scalar_t__ early_mmu_has_feature (int /*<<< orphan*/ ) ; 

__attribute__((used)) static pgprot_t kasan_prot_ro(void)
{
	if (early_mmu_has_feature(MMU_FTR_HPTE_TABLE))
		return PAGE_READONLY;

	return PAGE_KERNEL_RO;
}