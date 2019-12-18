#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct kvm_userspace_memory_region {int dummy; } ;
struct kvm_memory_slot {int flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  n_requested_mmu_pages; } ;
struct kvm {TYPE_1__ arch; } ;
typedef  enum kvm_mr_change { ____Placeholder_kvm_mr_change } kvm_mr_change ;

/* Variables and functions */
 int KVM_MEM_LOG_DIRTY_PAGES ; 
 int KVM_MR_DELETE ; 
 int KVM_MR_FLAGS_ONLY ; 
 int /*<<< orphan*/  kvm_mmu_calculate_default_mmu_pages (struct kvm*) ; 
 int /*<<< orphan*/  kvm_mmu_change_mmu_pages (struct kvm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_mmu_slot_apply_flags (struct kvm*,struct kvm_memory_slot*) ; 
 int /*<<< orphan*/  kvm_mmu_zap_collapsible_sptes (struct kvm*,struct kvm_memory_slot const*) ; 

void kvm_arch_commit_memory_region(struct kvm *kvm,
				const struct kvm_userspace_memory_region *mem,
				const struct kvm_memory_slot *old,
				const struct kvm_memory_slot *new,
				enum kvm_mr_change change)
{
	if (!kvm->arch.n_requested_mmu_pages)
		kvm_mmu_change_mmu_pages(kvm,
				kvm_mmu_calculate_default_mmu_pages(kvm));

	/*
	 * Dirty logging tracks sptes in 4k granularity, meaning that large
	 * sptes have to be split.  If live migration is successful, the guest
	 * in the source machine will be destroyed and large sptes will be
	 * created in the destination. However, if the guest continues to run
	 * in the source machine (for example if live migration fails), small
	 * sptes will remain around and cause bad performance.
	 *
	 * Scan sptes if dirty logging has been stopped, dropping those
	 * which can be collapsed into a single large-page spte.  Later
	 * page faults will create the large-page sptes.
	 *
	 * There is no need to do this in any of the following cases:
	 * CREATE:	No dirty mappings will already exist.
	 * MOVE/DELETE:	The old mappings will already have been cleaned up by
	 *		kvm_arch_flush_shadow_memslot()
	 */
	if (change == KVM_MR_FLAGS_ONLY &&
		(old->flags & KVM_MEM_LOG_DIRTY_PAGES) &&
		!(new->flags & KVM_MEM_LOG_DIRTY_PAGES))
		kvm_mmu_zap_collapsible_sptes(kvm, new);

	/*
	 * Set up write protection and/or dirty logging for the new slot.
	 *
	 * For KVM_MR_DELETE and KVM_MR_MOVE, the shadow pages of old slot have
	 * been zapped so no dirty logging staff is needed for old slot. For
	 * KVM_MR_FLAGS_ONLY, the old slot is essentially the same one as the
	 * new and it's also covered when dealing with the new slot.
	 *
	 * FIXME: const-ify all uses of struct kvm_memory_slot.
	 */
	if (change != KVM_MR_DELETE)
		kvm_mmu_slot_apply_flags(kvm, (struct kvm_memory_slot *) new);
}