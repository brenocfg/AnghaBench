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
typedef  int u32 ;
struct TYPE_2__ {int epcr; int /*<<< orphan*/  shadow_epcr; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPRN_EPCR_GICM ; 
 int SPRN_EPCR_ICM ; 

void kvmppc_set_epcr(struct kvm_vcpu *vcpu, u32 new_epcr)
{
#if defined(CONFIG_64BIT)
	vcpu->arch.epcr = new_epcr;
#ifdef CONFIG_KVM_BOOKE_HV
	vcpu->arch.shadow_epcr &= ~SPRN_EPCR_GICM;
	if (vcpu->arch.epcr  & SPRN_EPCR_ICM)
		vcpu->arch.shadow_epcr |= SPRN_EPCR_GICM;
#endif
#endif
}