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
struct kvm_nested_guest {int /*<<< orphan*/  shadow_lpid; int /*<<< orphan*/  shadow_pgtable; } ;
struct kvm {int /*<<< orphan*/  mmu_lock; } ;
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int /*<<< orphan*/ * __find_linux_pte (int /*<<< orphan*/ ,long,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  kvmppc_unmap_pte (struct kvm*,int /*<<< orphan*/ *,long,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ pte_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool kvmhv_invalidate_shadow_pte(struct kvm_vcpu *vcpu,
					struct kvm_nested_guest *gp,
					long gpa, int *shift_ret)
{
	struct kvm *kvm = vcpu->kvm;
	bool ret = false;
	pte_t *ptep;
	int shift;

	spin_lock(&kvm->mmu_lock);
	ptep = __find_linux_pte(gp->shadow_pgtable, gpa, NULL, &shift);
	if (!shift)
		shift = PAGE_SHIFT;
	if (ptep && pte_present(*ptep)) {
		kvmppc_unmap_pte(kvm, ptep, gpa, shift, NULL, gp->shadow_lpid);
		ret = true;
	}
	spin_unlock(&kvm->mmu_lock);

	if (shift_ret)
		*shift_ret = shift;
	return ret;
}