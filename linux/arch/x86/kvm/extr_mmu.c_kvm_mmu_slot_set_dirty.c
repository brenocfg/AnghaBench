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
struct kvm_memory_slot {int /*<<< orphan*/  npages; int /*<<< orphan*/  base_gfn; } ;
struct kvm {int /*<<< orphan*/  slots_lock; int /*<<< orphan*/  mmu_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __rmap_set_dirty ; 
 int /*<<< orphan*/  kvm_flush_remote_tlbs_with_address (struct kvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int slot_handle_all_level (struct kvm*,struct kvm_memory_slot*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void kvm_mmu_slot_set_dirty(struct kvm *kvm,
			    struct kvm_memory_slot *memslot)
{
	bool flush;

	spin_lock(&kvm->mmu_lock);
	flush = slot_handle_all_level(kvm, memslot, __rmap_set_dirty, false);
	spin_unlock(&kvm->mmu_lock);

	lockdep_assert_held(&kvm->slots_lock);

	/* see kvm_mmu_slot_leaf_clear_dirty */
	if (flush)
		kvm_flush_remote_tlbs_with_address(kvm, memslot->base_gfn,
				memslot->npages);
}