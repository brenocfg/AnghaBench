#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ level; } ;
struct kvm_mmu_page {TYPE_2__ role; int /*<<< orphan*/  gfn; } ;
struct kvm_memslots {int dummy; } ;
struct kvm_memory_slot {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  indirect_shadow_pages; } ;
struct kvm {TYPE_1__ arch; } ;
typedef  int /*<<< orphan*/  gfn_t ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_PAGE_TRACK_WRITE ; 
 scalar_t__ PT_PAGE_TABLE_LEVEL ; 
 struct kvm_memory_slot* __gfn_to_memslot (struct kvm_memslots*,int /*<<< orphan*/ ) ; 
 struct kvm_memslots* kvm_memslots_for_spte_role (struct kvm*,TYPE_2__) ; 
 int /*<<< orphan*/  kvm_mmu_gfn_disallow_lpage (struct kvm_memory_slot*,int /*<<< orphan*/ ) ; 
 void kvm_slot_page_track_add_page (struct kvm*,struct kvm_memory_slot*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void account_shadowed(struct kvm *kvm, struct kvm_mmu_page *sp)
{
	struct kvm_memslots *slots;
	struct kvm_memory_slot *slot;
	gfn_t gfn;

	kvm->arch.indirect_shadow_pages++;
	gfn = sp->gfn;
	slots = kvm_memslots_for_spte_role(kvm, sp->role);
	slot = __gfn_to_memslot(slots, gfn);

	/* the non-leaf shadow pages are keeping readonly. */
	if (sp->role.level > PT_PAGE_TABLE_LEVEL)
		return kvm_slot_page_track_add_page(kvm, slot, gfn,
						    KVM_PAGE_TRACK_WRITE);

	kvm_mmu_gfn_disallow_lpage(slot, gfn);
}