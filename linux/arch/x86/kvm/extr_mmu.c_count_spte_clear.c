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
typedef  int /*<<< orphan*/  u64 ;
struct kvm_mmu_page {int /*<<< orphan*/  clear_spte_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  __pa (int /*<<< orphan*/ *) ; 
 scalar_t__ is_shadow_present_pte (int /*<<< orphan*/ ) ; 
 struct kvm_mmu_page* page_header (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_wmb () ; 

__attribute__((used)) static void count_spte_clear(u64 *sptep, u64 spte)
{
	struct kvm_mmu_page *sp =  page_header(__pa(sptep));

	if (is_shadow_present_pte(spte))
		return;

	/* Ensure the spte is completely set before we increase the count */
	smp_wmb();
	sp->clear_spte_count++;
}