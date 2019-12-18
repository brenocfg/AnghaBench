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
struct kvm_page_track_notifier_node {int /*<<< orphan*/  track_flush_slot; int /*<<< orphan*/  track_write; } ;
struct TYPE_2__ {struct kvm_page_track_notifier_node mmu_sp_tracker; } ;
struct kvm {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvm_mmu_invalidate_zap_pages_in_memslot ; 
 int /*<<< orphan*/  kvm_mmu_pte_write ; 
 int /*<<< orphan*/  kvm_page_track_register_notifier (struct kvm*,struct kvm_page_track_notifier_node*) ; 

void kvm_mmu_init_vm(struct kvm *kvm)
{
	struct kvm_page_track_notifier_node *node = &kvm->arch.mmu_sp_tracker;

	node->track_write = kvm_mmu_pte_write;
	node->track_flush_slot = kvm_mmu_invalidate_zap_pages_in_memslot;
	kvm_page_track_register_notifier(kvm, node);
}