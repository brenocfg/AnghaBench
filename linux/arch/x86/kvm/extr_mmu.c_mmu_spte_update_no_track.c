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

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __update_clear_spte_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __update_clear_spte_slow (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_shadow_present_pte (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmu_spte_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spte_has_volatile_bits (int /*<<< orphan*/ ) ; 
 scalar_t__ spte_to_pfn (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64 mmu_spte_update_no_track(u64 *sptep, u64 new_spte)
{
	u64 old_spte = *sptep;

	WARN_ON(!is_shadow_present_pte(new_spte));

	if (!is_shadow_present_pte(old_spte)) {
		mmu_spte_set(sptep, new_spte);
		return old_spte;
	}

	if (!spte_has_volatile_bits(old_spte))
		__update_clear_spte_fast(sptep, new_spte);
	else
		old_spte = __update_clear_spte_slow(sptep, new_spte);

	WARN_ON(spte_to_pfn(old_spte) != spte_to_pfn(new_spte));

	return old_spte;
}