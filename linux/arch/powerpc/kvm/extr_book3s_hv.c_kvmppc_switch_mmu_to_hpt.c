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
struct TYPE_2__ {scalar_t__ radix; scalar_t__ process_table; } ;
struct kvm {int /*<<< orphan*/  mmu_lock; TYPE_1__ arch; } ;

/* Variables and functions */
 int LPCR_GTSE ; 
 int LPCR_HR ; 
 int LPCR_UPRT ; 
 int LPCR_VPM1 ; 
 int /*<<< orphan*/  kvmhv_release_all_nested (struct kvm*) ; 
 int /*<<< orphan*/  kvmppc_free_radix (struct kvm*) ; 
 int /*<<< orphan*/  kvmppc_rmap_reset (struct kvm*) ; 
 int /*<<< orphan*/  kvmppc_update_lpcr (struct kvm*,int,int) ; 
 scalar_t__ nesting_enabled (struct kvm*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int kvmppc_switch_mmu_to_hpt(struct kvm *kvm)
{
	if (nesting_enabled(kvm))
		kvmhv_release_all_nested(kvm);
	kvmppc_rmap_reset(kvm);
	kvm->arch.process_table = 0;
	/* Mutual exclusion with kvm_unmap_hva_range etc. */
	spin_lock(&kvm->mmu_lock);
	kvm->arch.radix = 0;
	spin_unlock(&kvm->mmu_lock);
	kvmppc_free_radix(kvm);
	kvmppc_update_lpcr(kvm, LPCR_VPM1,
			   LPCR_VPM1 | LPCR_UPRT | LPCR_GTSE | LPCR_HR);
	return 0;
}