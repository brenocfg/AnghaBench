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
typedef  int u64 ;
struct kvmppc_pte {int rc; unsigned long raddr; } ;
struct kvm_vcpu {struct kvm* kvm; } ;
struct kvm_nested_guest {int /*<<< orphan*/  shadow_lpid; int /*<<< orphan*/  shadow_pgtable; } ;
struct TYPE_2__ {int /*<<< orphan*/  lpid; int /*<<< orphan*/  pgtable; } ;
struct kvm {int /*<<< orphan*/  mmu_lock; TYPE_1__ arch; } ;

/* Variables and functions */
 unsigned long DSISR_ISSTORE ; 
 long EINVAL ; 
 long RESUME_HOST ; 
 int _PAGE_ACCESSED ; 
 int _PAGE_DIRTY ; 
 long kvmppc_hv_handle_set_rc (struct kvm*,int /*<<< orphan*/ ,int,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static long kvmhv_handle_nested_set_rc(struct kvm_vcpu *vcpu,
				       struct kvm_nested_guest *gp,
				       unsigned long n_gpa,
				       struct kvmppc_pte gpte,
				       unsigned long dsisr)
{
	struct kvm *kvm = vcpu->kvm;
	bool writing = !!(dsisr & DSISR_ISSTORE);
	u64 pgflags;
	long ret;

	/* Are the rc bits set in the L1 partition scoped pte? */
	pgflags = _PAGE_ACCESSED;
	if (writing)
		pgflags |= _PAGE_DIRTY;
	if (pgflags & ~gpte.rc)
		return RESUME_HOST;

	spin_lock(&kvm->mmu_lock);
	/* Set the rc bit in the pte of our (L0) pgtable for the L1 guest */
	ret = kvmppc_hv_handle_set_rc(kvm, kvm->arch.pgtable, writing,
				     gpte.raddr, kvm->arch.lpid);
	if (!ret) {
		ret = -EINVAL;
		goto out_unlock;
	}

	/* Set the rc bit in the pte of the shadow_pgtable for the nest guest */
	ret = kvmppc_hv_handle_set_rc(kvm, gp->shadow_pgtable, writing, n_gpa,
				      gp->shadow_lpid);
	if (!ret)
		ret = -EINVAL;
	else
		ret = 0;

out_unlock:
	spin_unlock(&kvm->mmu_lock);
	return ret;
}