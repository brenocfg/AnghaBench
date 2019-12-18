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
struct kvm_nested_guest {int /*<<< orphan*/  shadow_lpid; scalar_t__ shadow_pgtable; struct kvm* l1_host; } ;
struct kvm {int /*<<< orphan*/  mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct kvm_nested_guest*) ; 
 int /*<<< orphan*/  kvmhv_set_ptbl_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvmppc_free_lpid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvmppc_free_pgtable_radix (struct kvm*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgd_free (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void kvmhv_release_nested(struct kvm_nested_guest *gp)
{
	struct kvm *kvm = gp->l1_host;

	if (gp->shadow_pgtable) {
		/*
		 * No vcpu is using this struct and no call to
		 * kvmhv_get_nested can find this struct,
		 * so we don't need to hold kvm->mmu_lock.
		 */
		kvmppc_free_pgtable_radix(kvm, gp->shadow_pgtable,
					  gp->shadow_lpid);
		pgd_free(kvm->mm, gp->shadow_pgtable);
	}
	kvmhv_set_ptbl_entry(gp->shadow_lpid, 0, 0);
	kvmppc_free_lpid(gp->shadow_lpid);
	kfree(gp);
}