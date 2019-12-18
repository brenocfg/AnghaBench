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
typedef  int u64 ;
typedef  int u32 ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int KVM_NR_VAR_MTRR ; 
 int MSR_IA32_CR_PAT ; 
 int MSR_MTRRdefType ; 
 int MSR_MTRRfix4K_F8000 ; 
 int MSR_MTRRfix64K_00000 ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 unsigned long long cpuid_maxphyaddr (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_inject_gp (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int kvm_pat_valid (int) ; 
 int /*<<< orphan*/  msr_mtrr_valid (int) ; 
 int valid_mtrr_type (int) ; 

bool kvm_mtrr_valid(struct kvm_vcpu *vcpu, u32 msr, u64 data)
{
	int i;
	u64 mask;

	if (!msr_mtrr_valid(msr))
		return false;

	if (msr == MSR_IA32_CR_PAT) {
		return kvm_pat_valid(data);
	} else if (msr == MSR_MTRRdefType) {
		if (data & ~0xcff)
			return false;
		return valid_mtrr_type(data & 0xff);
	} else if (msr >= MSR_MTRRfix64K_00000 && msr <= MSR_MTRRfix4K_F8000) {
		for (i = 0; i < 8 ; i++)
			if (!valid_mtrr_type((data >> (i * 8)) & 0xff))
				return false;
		return true;
	}

	/* variable MTRRs */
	WARN_ON(!(msr >= 0x200 && msr < 0x200 + 2 * KVM_NR_VAR_MTRR));

	mask = (~0ULL) << cpuid_maxphyaddr(vcpu);
	if ((msr & 1) == 0) {
		/* MTRR base */
		if (!valid_mtrr_type(data & 0xff))
			return false;
		mask |= 0xf00;
	} else
		/* MTRR mask */
		mask |= 0x7ff;
	if (data & mask) {
		kvm_inject_gp(vcpu, 0);
		return false;
	}

	return true;
}