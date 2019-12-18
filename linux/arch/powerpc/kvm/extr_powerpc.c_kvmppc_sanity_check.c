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
struct TYPE_2__ {scalar_t__ cpu_type; int sane; scalar_t__ papr_enabled; int /*<<< orphan*/  pvr; } ;
struct kvm_vcpu {TYPE_1__ arch; int /*<<< orphan*/  kvm; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_FTR_EMB_HV ; 
 int EINVAL ; 
 scalar_t__ KVM_CPU_3S_64 ; 
 int /*<<< orphan*/  cpu_has_feature (int /*<<< orphan*/ ) ; 
 scalar_t__ is_kvmppc_hv_enabled (int /*<<< orphan*/ ) ; 

int kvmppc_sanity_check(struct kvm_vcpu *vcpu)
{
	int r = false;

	/* We have to know what CPU to virtualize */
	if (!vcpu->arch.pvr)
		goto out;

	/* PAPR only works with book3s_64 */
	if ((vcpu->arch.cpu_type != KVM_CPU_3S_64) && vcpu->arch.papr_enabled)
		goto out;

	/* HV KVM can only do PAPR mode for now */
	if (!vcpu->arch.papr_enabled && is_kvmppc_hv_enabled(vcpu->kvm))
		goto out;

#ifdef CONFIG_KVM_BOOKE_HV
	if (!cpu_has_feature(CPU_FTR_EMB_HV))
		goto out;
#endif

	r = true;

out:
	vcpu->arch.sane = r;
	return r ? 0 : -EINVAL;
}