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
typedef  int u64 ;
typedef  int u32 ;
struct TYPE_2__ {int mcg_cap; int mcg_ctl; int mcg_status; int* mce_banks; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int MCG_CTL_P ; 
 int MSR_IA32_MC0_CTL ; 
#define  MSR_IA32_MCG_CAP 132 
#define  MSR_IA32_MCG_CTL 131 
#define  MSR_IA32_MCG_STATUS 130 
 int MSR_IA32_MCx_CTL (unsigned int) ; 
#define  MSR_IA32_P5_MC_ADDR 129 
#define  MSR_IA32_P5_MC_TYPE 128 

__attribute__((used)) static int get_msr_mce(struct kvm_vcpu *vcpu, u32 msr, u64 *pdata, bool host)
{
	u64 data;
	u64 mcg_cap = vcpu->arch.mcg_cap;
	unsigned bank_num = mcg_cap & 0xff;

	switch (msr) {
	case MSR_IA32_P5_MC_ADDR:
	case MSR_IA32_P5_MC_TYPE:
		data = 0;
		break;
	case MSR_IA32_MCG_CAP:
		data = vcpu->arch.mcg_cap;
		break;
	case MSR_IA32_MCG_CTL:
		if (!(mcg_cap & MCG_CTL_P) && !host)
			return 1;
		data = vcpu->arch.mcg_ctl;
		break;
	case MSR_IA32_MCG_STATUS:
		data = vcpu->arch.mcg_status;
		break;
	default:
		if (msr >= MSR_IA32_MC0_CTL &&
		    msr < MSR_IA32_MCx_CTL(bank_num)) {
			u32 offset = msr - MSR_IA32_MC0_CTL;
			data = vcpu->arch.mce_banks[offset];
			break;
		}
		return 1;
	}
	*pdata = data;
	return 0;
}