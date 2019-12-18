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
struct kvm_page_track_notifier_node {int dummy; } ;
struct kvm_memory_slot {int dummy; } ;
struct kvm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvm_mmu_zap_all_fast (struct kvm*) ; 

__attribute__((used)) static void kvm_mmu_invalidate_zap_pages_in_memslot(struct kvm *kvm,
			struct kvm_memory_slot *slot,
			struct kvm_page_track_notifier_node *node)
{
	kvm_mmu_zap_all_fast(kvm);
}