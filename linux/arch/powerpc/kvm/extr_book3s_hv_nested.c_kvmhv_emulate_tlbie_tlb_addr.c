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
struct kvm_nested_guest {int /*<<< orphan*/  tlb_lock; } ;
struct kvm {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int PAGE_SHIFT ; 
 int ap_to_shift (int) ; 
 struct kvm_nested_guest* kvmhv_get_nested (struct kvm*,int,int) ; 
 int /*<<< orphan*/  kvmhv_invalidate_shadow_pte (struct kvm_vcpu*,struct kvm_nested_guest*,unsigned long,int*) ; 
 int /*<<< orphan*/  kvmhv_put_nested (struct kvm_nested_guest*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int kvmhv_emulate_tlbie_tlb_addr(struct kvm_vcpu *vcpu, int lpid,
					int ap, long epn)
{
	struct kvm *kvm = vcpu->kvm;
	struct kvm_nested_guest *gp;
	long npages;
	int shift, shadow_shift;
	unsigned long addr;

	shift = ap_to_shift(ap);
	addr = epn << 12;
	if (shift < 0)
		/* Invalid ap encoding */
		return -EINVAL;

	addr &= ~((1UL << shift) - 1);
	npages = 1UL << (shift - PAGE_SHIFT);

	gp = kvmhv_get_nested(kvm, lpid, false);
	if (!gp) /* No such guest -> nothing to do */
		return 0;
	mutex_lock(&gp->tlb_lock);

	/* There may be more than one host page backing this single guest pte */
	do {
		kvmhv_invalidate_shadow_pte(vcpu, gp, addr, &shadow_shift);

		npages -= 1UL << (shadow_shift - PAGE_SHIFT);
		addr += 1UL << shadow_shift;
	} while (npages > 0);

	mutex_unlock(&gp->tlb_lock);
	kvmhv_put_nested(gp);
	return 0;
}