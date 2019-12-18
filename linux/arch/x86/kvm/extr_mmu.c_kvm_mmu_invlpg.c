#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  invlpg; } ;
struct TYPE_7__ {struct kvm_mmu* mmu; } ;
struct kvm_vcpu {TYPE_2__ stat; TYPE_3__ arch; } ;
struct kvm_mmu {TYPE_1__* prev_roots; int /*<<< orphan*/  (* invlpg ) (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  root_hpa; } ;
typedef  int /*<<< orphan*/  gva_t ;
struct TYPE_8__ {int /*<<< orphan*/  (* tlb_flush_gva ) (struct kvm_vcpu*,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  hpa; } ;

/* Variables and functions */
 int KVM_MMU_NUM_PREV_ROOTS ; 
 scalar_t__ VALID_PAGE (int /*<<< orphan*/ ) ; 
 scalar_t__ is_noncanonical_address (int /*<<< orphan*/ ,struct kvm_vcpu*) ; 
 TYPE_4__* kvm_x86_ops ; 
 int /*<<< orphan*/  stub1 (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 

void kvm_mmu_invlpg(struct kvm_vcpu *vcpu, gva_t gva)
{
	struct kvm_mmu *mmu = vcpu->arch.mmu;
	int i;

	/* INVLPG on a * non-canonical address is a NOP according to the SDM.  */
	if (is_noncanonical_address(gva, vcpu))
		return;

	mmu->invlpg(vcpu, gva, mmu->root_hpa);

	/*
	 * INVLPG is required to invalidate any global mappings for the VA,
	 * irrespective of PCID. Since it would take us roughly similar amount
	 * of work to determine whether any of the prev_root mappings of the VA
	 * is marked global, or to just sync it blindly, so we might as well
	 * just always sync it.
	 *
	 * Mappings not reachable via the current cr3 or the prev_roots will be
	 * synced when switching to that cr3, so nothing needs to be done here
	 * for them.
	 */
	for (i = 0; i < KVM_MMU_NUM_PREV_ROOTS; i++)
		if (VALID_PAGE(mmu->prev_roots[i].hpa))
			mmu->invlpg(vcpu, gva, mmu->prev_roots[i].hpa);

	kvm_x86_ops->tlb_flush_gva(vcpu, gva);
	++vcpu->stat.invlpg;
}