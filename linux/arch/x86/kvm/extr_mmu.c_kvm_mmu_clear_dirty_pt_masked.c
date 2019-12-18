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
struct kvm_rmap_head {int dummy; } ;
struct kvm_memory_slot {scalar_t__ base_gfn; } ;
struct kvm {int dummy; } ;
typedef  scalar_t__ gfn_t ;

/* Variables and functions */
 int /*<<< orphan*/  PT_PAGE_TABLE_LEVEL ; 
 scalar_t__ __ffs (unsigned long) ; 
 struct kvm_rmap_head* __gfn_to_rmap (scalar_t__,int /*<<< orphan*/ ,struct kvm_memory_slot*) ; 
 int /*<<< orphan*/  __rmap_clear_dirty (struct kvm*,struct kvm_rmap_head*) ; 

void kvm_mmu_clear_dirty_pt_masked(struct kvm *kvm,
				     struct kvm_memory_slot *slot,
				     gfn_t gfn_offset, unsigned long mask)
{
	struct kvm_rmap_head *rmap_head;

	while (mask) {
		rmap_head = __gfn_to_rmap(slot->base_gfn + gfn_offset + __ffs(mask),
					  PT_PAGE_TABLE_LEVEL, slot);
		__rmap_clear_dirty(kvm, rmap_head);

		/* clear the first set bit */
		mask &= mask - 1;
	}
}