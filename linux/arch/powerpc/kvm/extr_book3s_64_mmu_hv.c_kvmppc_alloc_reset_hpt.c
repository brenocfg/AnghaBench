#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct kvm_hpt_info {int dummy; } ;
struct TYPE_4__ {int order; scalar_t__ virt; } ;
struct TYPE_3__ {int mmu_ready; int /*<<< orphan*/  mmu_setup_lock; int /*<<< orphan*/  need_tlb_flush; TYPE_2__ hpt; int /*<<< orphan*/  vcpus_running; } ;
struct kvm {TYPE_1__ arch; } ;

/* Variables and functions */
 long EBUSY ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpumask_setall (int /*<<< orphan*/ *) ; 
 scalar_t__ kvm_is_radix (struct kvm*) ; 
 long kvmppc_allocate_hpt (struct kvm_hpt_info*,int) ; 
 int /*<<< orphan*/  kvmppc_free_hpt (TYPE_2__*) ; 
 int /*<<< orphan*/  kvmppc_rmap_reset (struct kvm*) ; 
 int /*<<< orphan*/  kvmppc_set_hpt (struct kvm*,struct kvm_hpt_info*) ; 
 long kvmppc_switch_mmu_to_hpt (struct kvm*) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb () ; 

long kvmppc_alloc_reset_hpt(struct kvm *kvm, int order)
{
	long err = -EBUSY;
	struct kvm_hpt_info info;

	mutex_lock(&kvm->arch.mmu_setup_lock);
	if (kvm->arch.mmu_ready) {
		kvm->arch.mmu_ready = 0;
		/* order mmu_ready vs. vcpus_running */
		smp_mb();
		if (atomic_read(&kvm->arch.vcpus_running)) {
			kvm->arch.mmu_ready = 1;
			goto out;
		}
	}
	if (kvm_is_radix(kvm)) {
		err = kvmppc_switch_mmu_to_hpt(kvm);
		if (err)
			goto out;
	}

	if (kvm->arch.hpt.order == order) {
		/* We already have a suitable HPT */

		/* Set the entire HPT to 0, i.e. invalid HPTEs */
		memset((void *)kvm->arch.hpt.virt, 0, 1ul << order);
		/*
		 * Reset all the reverse-mapping chains for all memslots
		 */
		kvmppc_rmap_reset(kvm);
		err = 0;
		goto out;
	}

	if (kvm->arch.hpt.virt) {
		kvmppc_free_hpt(&kvm->arch.hpt);
		kvmppc_rmap_reset(kvm);
	}

	err = kvmppc_allocate_hpt(&info, order);
	if (err < 0)
		goto out;
	kvmppc_set_hpt(kvm, &info);

out:
	if (err == 0)
		/* Ensure that each vcpu will flush its TLB on next entry. */
		cpumask_setall(&kvm->arch.need_tlb_flush);

	mutex_unlock(&kvm->arch.mmu_setup_lock);
	return err;
}