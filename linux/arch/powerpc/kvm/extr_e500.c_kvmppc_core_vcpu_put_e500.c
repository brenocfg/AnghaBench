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
struct TYPE_2__ {int shadow_msr; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int MSR_SPE ; 
 int /*<<< orphan*/  kvmppc_booke_vcpu_put (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_vcpu_disable_spe (struct kvm_vcpu*) ; 

__attribute__((used)) static void kvmppc_core_vcpu_put_e500(struct kvm_vcpu *vcpu)
{
#ifdef CONFIG_SPE
	if (vcpu->arch.shadow_msr & MSR_SPE)
		kvmppc_vcpu_disable_spe(vcpu);
#endif

	kvmppc_booke_vcpu_put(vcpu);
}