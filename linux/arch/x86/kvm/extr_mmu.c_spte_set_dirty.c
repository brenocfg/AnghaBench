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
 int mmu_spte_update (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rmap_printk (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shadow_dirty_mask ; 

__attribute__((used)) static bool spte_set_dirty(u64 *sptep)
{
	u64 spte = *sptep;

	rmap_printk("rmap_set_dirty: spte %p %llx\n", sptep, *sptep);

	/*
	 * Similar to the !kvm_x86_ops->slot_disable_log_dirty case,
	 * do not bother adding back write access to pages marked
	 * SPTE_AD_WRPROT_ONLY_MASK.
	 */
	spte |= shadow_dirty_mask;

	return mmu_spte_update(sptep, spte);
}