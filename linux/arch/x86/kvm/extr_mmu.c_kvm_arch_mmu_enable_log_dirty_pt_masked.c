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
struct kvm_memory_slot {int dummy; } ;
struct kvm {int dummy; } ;
typedef  int /*<<< orphan*/  gfn_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* enable_log_dirty_pt_masked ) (struct kvm*,struct kvm_memory_slot*,int /*<<< orphan*/ ,unsigned long) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  kvm_mmu_write_protect_pt_masked (struct kvm*,struct kvm_memory_slot*,int /*<<< orphan*/ ,unsigned long) ; 
 TYPE_1__* kvm_x86_ops ; 
 int /*<<< orphan*/  stub1 (struct kvm*,struct kvm_memory_slot*,int /*<<< orphan*/ ,unsigned long) ; 

void kvm_arch_mmu_enable_log_dirty_pt_masked(struct kvm *kvm,
				struct kvm_memory_slot *slot,
				gfn_t gfn_offset, unsigned long mask)
{
	if (kvm_x86_ops->enable_log_dirty_pt_masked)
		kvm_x86_ops->enable_log_dirty_pt_masked(kvm, slot, gfn_offset,
				mask);
	else
		kvm_mmu_write_protect_pt_masked(kvm, slot, gfn_offset, mask);
}