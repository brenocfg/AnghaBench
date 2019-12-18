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
struct kvm_nested_guest {scalar_t__ l1_gr_to_hr; int /*<<< orphan*/  shadow_lpid; int /*<<< orphan*/  shadow_pgtable; struct kvm* l1_host; } ;
struct kvm {int /*<<< orphan*/  mmu_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvmhv_flush_lpid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvmhv_remove_nested (struct kvm_nested_guest*) ; 
 int /*<<< orphan*/  kvmhv_update_ptbl_cache (struct kvm_nested_guest*) ; 
 int /*<<< orphan*/  kvmppc_free_pgtable_radix (struct kvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void kvmhv_flush_nested(struct kvm_nested_guest *gp)
{
	struct kvm *kvm = gp->l1_host;

	spin_lock(&kvm->mmu_lock);
	kvmppc_free_pgtable_radix(kvm, gp->shadow_pgtable, gp->shadow_lpid);
	spin_unlock(&kvm->mmu_lock);
	kvmhv_flush_lpid(gp->shadow_lpid);
	kvmhv_update_ptbl_cache(gp);
	if (gp->l1_gr_to_hr == 0)
		kvmhv_remove_nested(gp);
}