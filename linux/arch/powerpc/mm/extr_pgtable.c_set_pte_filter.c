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
struct page {int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 int /*<<< orphan*/  MMU_FTR_HPTE_TABLE ; 
 int /*<<< orphan*/  PG_arch_1 ; 
 int /*<<< orphan*/  flush_dcache_icache_page (struct page*) ; 
 scalar_t__ is_exec_fault () ; 
 struct page* maybe_pte_to_page (int /*<<< orphan*/ ) ; 
 scalar_t__ mmu_has_feature (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_exec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_exprotect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_looks_normal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_pte_filter_hash (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static pte_t set_pte_filter(pte_t pte)
{
	struct page *pg;

	if (mmu_has_feature(MMU_FTR_HPTE_TABLE))
		return set_pte_filter_hash(pte);

	/* No exec permission in the first place, move on */
	if (!pte_exec(pte) || !pte_looks_normal(pte))
		return pte;

	/* If you set _PAGE_EXEC on weird pages you're on your own */
	pg = maybe_pte_to_page(pte);
	if (unlikely(!pg))
		return pte;

	/* If the page clean, we move on */
	if (test_bit(PG_arch_1, &pg->flags))
		return pte;

	/* If it's an exec fault, we flush the cache and make it clean */
	if (is_exec_fault()) {
		flush_dcache_icache_page(pg);
		set_bit(PG_arch_1, &pg->flags);
		return pte;
	}

	/* Else, we filter out _PAGE_EXEC */
	return pte_exprotect(pte);
}