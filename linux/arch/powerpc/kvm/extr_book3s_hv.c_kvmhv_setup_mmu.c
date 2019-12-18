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
struct kvm_vcpu {struct kvm* kvm; } ;
struct TYPE_2__ {int mmu_ready; int /*<<< orphan*/  mmu_setup_lock; } ;
struct kvm {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_FTR_ARCH_300 ; 
 scalar_t__ cpu_has_feature (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_is_radix (struct kvm*) ; 
 int kvmppc_hv_setup_htab_rma (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_setup_partition_table (struct kvm*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int kvmhv_setup_mmu(struct kvm_vcpu *vcpu)
{
	int r = 0;
	struct kvm *kvm = vcpu->kvm;

	mutex_lock(&kvm->arch.mmu_setup_lock);
	if (!kvm->arch.mmu_ready) {
		if (!kvm_is_radix(kvm))
			r = kvmppc_hv_setup_htab_rma(vcpu);
		if (!r) {
			if (cpu_has_feature(CPU_FTR_ARCH_300))
				kvmppc_setup_partition_table(kvm);
			kvm->arch.mmu_ready = 1;
		}
	}
	mutex_unlock(&kvm->arch.mmu_setup_lock);
	return r;
}