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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {TYPE_1__* shared; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;
struct TYPE_3__ {int /*<<< orphan*/  msr; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_GS ; 
 int /*<<< orphan*/  kvmppc_mmu_msr_notify (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvmppc_vcpu_sync_debug (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_vcpu_sync_fpu (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_vcpu_sync_spe (struct kvm_vcpu*) ; 

void kvmppc_set_msr(struct kvm_vcpu *vcpu, u32 new_msr)
{
	u32 old_msr = vcpu->arch.shared->msr;

#ifdef CONFIG_KVM_BOOKE_HV
	new_msr |= MSR_GS;
#endif

	vcpu->arch.shared->msr = new_msr;

	kvmppc_mmu_msr_notify(vcpu, old_msr);
	kvmppc_vcpu_sync_spe(vcpu);
	kvmppc_vcpu_sync_fpu(vcpu);
	kvmppc_vcpu_sync_debug(vcpu);
}