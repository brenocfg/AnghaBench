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
struct kvm_vcpu {struct kvm* kvm; } ;
struct kvm_nested_guest {int /*<<< orphan*/  tlb_lock; int /*<<< orphan*/  shadow_lpid; int /*<<< orphan*/  shadow_pgtable; } ;
struct kvm {int /*<<< orphan*/  mmu_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvmhv_flush_lpid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvmhv_flush_nested (struct kvm_nested_guest*) ; 
 int /*<<< orphan*/  kvmppc_free_pgtable_radix (struct kvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void kvmhv_emulate_tlbie_lpid(struct kvm_vcpu *vcpu,
				     struct kvm_nested_guest *gp, int ric)
{
	struct kvm *kvm = vcpu->kvm;

	mutex_lock(&gp->tlb_lock);
	switch (ric) {
	case 0:
		/* Invalidate TLB */
		spin_lock(&kvm->mmu_lock);
		kvmppc_free_pgtable_radix(kvm, gp->shadow_pgtable,
					  gp->shadow_lpid);
		kvmhv_flush_lpid(gp->shadow_lpid);
		spin_unlock(&kvm->mmu_lock);
		break;
	case 1:
		/*
		 * Invalidate PWC
		 * We don't cache this -> nothing to do
		 */
		break;
	case 2:
		/* Invalidate TLB, PWC and caching of partition table entries */
		kvmhv_flush_nested(gp);
		break;
	default:
		break;
	}
	mutex_unlock(&gp->tlb_lock);
}