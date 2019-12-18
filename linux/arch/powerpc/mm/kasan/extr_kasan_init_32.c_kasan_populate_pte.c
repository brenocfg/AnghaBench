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
typedef  int /*<<< orphan*/  phys_addr_t ;
typedef  int /*<<< orphan*/  pgprot_t ;

/* Variables and functions */
 int /*<<< orphan*/  PHYS_PFN (int /*<<< orphan*/ ) ; 
 int PTRS_PER_PTE ; 
 int /*<<< orphan*/  __pa (scalar_t__) ; 
 int /*<<< orphan*/  __set_pte_at (int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_mm ; 
 scalar_t__ kasan_early_shadow_page ; 
 int /*<<< orphan*/  pfn_pte (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kasan_populate_pte(pte_t *ptep, pgprot_t prot)
{
	unsigned long va = (unsigned long)kasan_early_shadow_page;
	phys_addr_t pa = __pa(kasan_early_shadow_page);
	int i;

	for (i = 0; i < PTRS_PER_PTE; i++, ptep++)
		__set_pte_at(&init_mm, va, ptep, pfn_pte(PHYS_PFN(pa), prot), 0);
}