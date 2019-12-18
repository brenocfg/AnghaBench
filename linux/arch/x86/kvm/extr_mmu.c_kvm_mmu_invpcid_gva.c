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
typedef  size_t uint ;
struct TYPE_7__ {int /*<<< orphan*/  invlpg; } ;
struct TYPE_5__ {struct kvm_mmu* mmu; } ;
struct kvm_vcpu {TYPE_3__ stat; TYPE_1__ arch; } ;
struct kvm_mmu {TYPE_2__* prev_roots; int /*<<< orphan*/  (* invlpg ) (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  root_hpa; } ;
typedef  int /*<<< orphan*/  gva_t ;
struct TYPE_8__ {int /*<<< orphan*/  (* tlb_flush_gva ) (struct kvm_vcpu*,int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  hpa; int /*<<< orphan*/  cr3; } ;

/* Variables and functions */
 size_t KVM_MMU_NUM_PREV_ROOTS ; 
 scalar_t__ VALID_PAGE (int /*<<< orphan*/ ) ; 
 unsigned long kvm_get_active_pcid (struct kvm_vcpu*) ; 
 unsigned long kvm_get_pcid (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 TYPE_4__* kvm_x86_ops ; 
 int /*<<< orphan*/  stub1 (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 

void kvm_mmu_invpcid_gva(struct kvm_vcpu *vcpu, gva_t gva, unsigned long pcid)
{
	struct kvm_mmu *mmu = vcpu->arch.mmu;
	bool tlb_flush = false;
	uint i;

	if (pcid == kvm_get_active_pcid(vcpu)) {
		mmu->invlpg(vcpu, gva, mmu->root_hpa);
		tlb_flush = true;
	}

	for (i = 0; i < KVM_MMU_NUM_PREV_ROOTS; i++) {
		if (VALID_PAGE(mmu->prev_roots[i].hpa) &&
		    pcid == kvm_get_pcid(vcpu, mmu->prev_roots[i].cr3)) {
			mmu->invlpg(vcpu, gva, mmu->prev_roots[i].hpa);
			tlb_flush = true;
		}
	}

	if (tlb_flush)
		kvm_x86_ops->tlb_flush_gva(vcpu, gva);

	++vcpu->stat.invlpg;

	/*
	 * Mappings not reachable via the current cr3 or the prev_roots will be
	 * synced when switching to that cr3, so nothing needs to be done here
	 * for them.
	 */
}