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
struct kvm_memory_slot {scalar_t__ npages; scalar_t__ base_gfn; } ;
struct kvm {int /*<<< orphan*/  mmu_lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* flush_shadow_memslot ) (struct kvm*,struct kvm_memory_slot*) ;} ;

/* Variables and functions */
 TYPE_1__* kvm_mips_callbacks ; 
 int /*<<< orphan*/  kvm_mips_flush_gpa_pt (struct kvm*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct kvm*,struct kvm_memory_slot*) ; 

void kvm_arch_flush_shadow_memslot(struct kvm *kvm,
				   struct kvm_memory_slot *slot)
{
	/*
	 * The slot has been made invalid (ready for moving or deletion), so we
	 * need to ensure that it can no longer be accessed by any guest VCPUs.
	 */

	spin_lock(&kvm->mmu_lock);
	/* Flush slot from GPA */
	kvm_mips_flush_gpa_pt(kvm, slot->base_gfn,
			      slot->base_gfn + slot->npages - 1);
	/* Let implementation do the rest */
	kvm_mips_callbacks->flush_shadow_memslot(kvm, slot);
	spin_unlock(&kvm->mmu_lock);
}