#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  pmu_event_filter; int /*<<< orphan*/  apic_map; } ;
struct kvm {scalar_t__ mm; int /*<<< orphan*/  srcu; TYPE_1__ arch; } ;
struct TYPE_6__ {scalar_t__ mm; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* vm_destroy ) (struct kvm*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  APIC_ACCESS_PAGE_PRIVATE_MEMSLOT ; 
 int /*<<< orphan*/  IDENTITY_PAGETABLE_PRIVATE_MEMSLOT ; 
 int /*<<< orphan*/  TSS_PRIVATE_MEMSLOT ; 
 TYPE_3__* current ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_free_vcpus (struct kvm*) ; 
 int /*<<< orphan*/  kvm_hv_destroy_vm (struct kvm*) ; 
 int /*<<< orphan*/  kvm_ioapic_destroy (struct kvm*) ; 
 int /*<<< orphan*/  kvm_mmu_uninit_vm (struct kvm*) ; 
 int /*<<< orphan*/  kvm_page_track_cleanup (struct kvm*) ; 
 int /*<<< orphan*/  kvm_pic_destroy (struct kvm*) ; 
 TYPE_2__* kvm_x86_ops ; 
 int /*<<< orphan*/  rcu_dereference_check (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  srcu_dereference_check (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (struct kvm*) ; 
 int /*<<< orphan*/  x86_set_memory_region (struct kvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void kvm_arch_destroy_vm(struct kvm *kvm)
{
	if (current->mm == kvm->mm) {
		/*
		 * Free memory regions allocated on behalf of userspace,
		 * unless the the memory map has changed due to process exit
		 * or fd copying.
		 */
		x86_set_memory_region(kvm, APIC_ACCESS_PAGE_PRIVATE_MEMSLOT, 0, 0);
		x86_set_memory_region(kvm, IDENTITY_PAGETABLE_PRIVATE_MEMSLOT, 0, 0);
		x86_set_memory_region(kvm, TSS_PRIVATE_MEMSLOT, 0, 0);
	}
	if (kvm_x86_ops->vm_destroy)
		kvm_x86_ops->vm_destroy(kvm);
	kvm_pic_destroy(kvm);
	kvm_ioapic_destroy(kvm);
	kvm_free_vcpus(kvm);
	kvfree(rcu_dereference_check(kvm->arch.apic_map, 1));
	kfree(srcu_dereference_check(kvm->arch.pmu_event_filter, &kvm->srcu, 1));
	kvm_mmu_uninit_vm(kvm);
	kvm_page_track_cleanup(kvm);
	kvm_hv_destroy_vm(kvm);
}