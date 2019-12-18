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
struct kvm_memory_slot {int flags; } ;
struct kvm {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* slot_disable_log_dirty ) (struct kvm*,struct kvm_memory_slot*) ;int /*<<< orphan*/  (* slot_enable_log_dirty ) (struct kvm*,struct kvm_memory_slot*) ;} ;

/* Variables and functions */
 int KVM_MEM_LOG_DIRTY_PAGES ; 
 int KVM_MEM_READONLY ; 
 int /*<<< orphan*/  kvm_mmu_slot_remove_write_access (struct kvm*,struct kvm_memory_slot*) ; 
 TYPE_1__* kvm_x86_ops ; 
 int /*<<< orphan*/  stub1 (struct kvm*,struct kvm_memory_slot*) ; 
 int /*<<< orphan*/  stub2 (struct kvm*,struct kvm_memory_slot*) ; 

__attribute__((used)) static void kvm_mmu_slot_apply_flags(struct kvm *kvm,
				     struct kvm_memory_slot *new)
{
	/* Still write protect RO slot */
	if (new->flags & KVM_MEM_READONLY) {
		kvm_mmu_slot_remove_write_access(kvm, new);
		return;
	}

	/*
	 * Call kvm_x86_ops dirty logging hooks when they are valid.
	 *
	 * kvm_x86_ops->slot_disable_log_dirty is called when:
	 *
	 *  - KVM_MR_CREATE with dirty logging is disabled
	 *  - KVM_MR_FLAGS_ONLY with dirty logging is disabled in new flag
	 *
	 * The reason is, in case of PML, we need to set D-bit for any slots
	 * with dirty logging disabled in order to eliminate unnecessary GPA
	 * logging in PML buffer (and potential PML buffer full VMEXT). This
	 * guarantees leaving PML enabled during guest's lifetime won't have
	 * any additional overhead from PML when guest is running with dirty
	 * logging disabled for memory slots.
	 *
	 * kvm_x86_ops->slot_enable_log_dirty is called when switching new slot
	 * to dirty logging mode.
	 *
	 * If kvm_x86_ops dirty logging hooks are invalid, use write protect.
	 *
	 * In case of write protect:
	 *
	 * Write protect all pages for dirty logging.
	 *
	 * All the sptes including the large sptes which point to this
	 * slot are set to readonly. We can not create any new large
	 * spte on this slot until the end of the logging.
	 *
	 * See the comments in fast_page_fault().
	 */
	if (new->flags & KVM_MEM_LOG_DIRTY_PAGES) {
		if (kvm_x86_ops->slot_enable_log_dirty)
			kvm_x86_ops->slot_enable_log_dirty(kvm, new);
		else
			kvm_mmu_slot_remove_write_access(kvm, new);
	} else {
		if (kvm_x86_ops->slot_disable_log_dirty)
			kvm_x86_ops->slot_disable_log_dirty(kvm, new);
	}
}