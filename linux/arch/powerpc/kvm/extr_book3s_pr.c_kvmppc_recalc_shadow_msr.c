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
typedef  int ulong ;
struct TYPE_2__ {int guest_owned_ext; int shadow_msr; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int MSR_BE ; 
 int MSR_DR ; 
 int MSR_EE ; 
 int MSR_FE0 ; 
 int MSR_FE1 ; 
 int MSR_HV ; 
 int MSR_IR ; 
 int MSR_ISF ; 
 int MSR_LE ; 
 int MSR_ME ; 
 int MSR_PR ; 
 int MSR_RI ; 
 int MSR_SE ; 
 int MSR_SF ; 
 int MSR_TM ; 
 int MSR_TS_MASK ; 
 int kvmppc_get_msr (struct kvm_vcpu*) ; 

__attribute__((used)) static void kvmppc_recalc_shadow_msr(struct kvm_vcpu *vcpu)
{
	ulong guest_msr = kvmppc_get_msr(vcpu);
	ulong smsr = guest_msr;

	/* Guest MSR values */
#ifdef CONFIG_PPC_TRANSACTIONAL_MEM
	smsr &= MSR_FE0 | MSR_FE1 | MSR_SF | MSR_SE | MSR_BE | MSR_LE |
		MSR_TM | MSR_TS_MASK;
#else
	smsr &= MSR_FE0 | MSR_FE1 | MSR_SF | MSR_SE | MSR_BE | MSR_LE;
#endif
	/* Process MSR values */
	smsr |= MSR_ME | MSR_RI | MSR_IR | MSR_DR | MSR_PR | MSR_EE;
	/* External providers the guest reserved */
	smsr |= (guest_msr & vcpu->arch.guest_owned_ext);
	/* 64-bit Process MSR values */
#ifdef CONFIG_PPC_BOOK3S_64
	smsr |= MSR_ISF | MSR_HV;
#endif
#ifdef CONFIG_PPC_TRANSACTIONAL_MEM
	/*
	 * in guest privileged state, we want to fail all TM transactions.
	 * So disable MSR TM bit so that all tbegin. will be able to be
	 * trapped into host.
	 */
	if (!(guest_msr & MSR_PR))
		smsr &= ~MSR_TM;
#endif
	vcpu->arch.shadow_msr = smsr;
}