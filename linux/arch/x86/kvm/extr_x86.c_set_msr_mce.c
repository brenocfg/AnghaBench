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
struct msr_data {int index; int data; int /*<<< orphan*/  host_initiated; } ;
struct TYPE_2__ {int mcg_cap; int mcg_status; int mcg_ctl; int* mce_banks; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int MCG_CTL_P ; 
 int MSR_IA32_MC0_CTL ; 
#define  MSR_IA32_MCG_CTL 129 
#define  MSR_IA32_MCG_STATUS 128 
 int MSR_IA32_MCx_CTL (unsigned int) ; 
 int /*<<< orphan*/  can_set_mci_status (struct kvm_vcpu*) ; 

__attribute__((used)) static int set_msr_mce(struct kvm_vcpu *vcpu, struct msr_data *msr_info)
{
	u64 mcg_cap = vcpu->arch.mcg_cap;
	unsigned bank_num = mcg_cap & 0xff;
	u32 msr = msr_info->index;
	u64 data = msr_info->data;

	switch (msr) {
	case MSR_IA32_MCG_STATUS:
		vcpu->arch.mcg_status = data;
		break;
	case MSR_IA32_MCG_CTL:
		if (!(mcg_cap & MCG_CTL_P) &&
		    (data || !msr_info->host_initiated))
			return 1;
		if (data != 0 && data != ~(u64)0)
			return 1;
		vcpu->arch.mcg_ctl = data;
		break;
	default:
		if (msr >= MSR_IA32_MC0_CTL &&
		    msr < MSR_IA32_MCx_CTL(bank_num)) {
			u32 offset = msr - MSR_IA32_MC0_CTL;
			/* only 0 or all 1s can be written to IA32_MCi_CTL
			 * some Linux kernels though clear bit 10 in bank 4 to
			 * workaround a BIOS/GART TBL issue on AMD K8s, ignore
			 * this to avoid an uncatched #GP in the guest
			 */
			if ((offset & 0x3) == 0 &&
			    data != 0 && (data | (1 << 10)) != ~(u64)0)
				return -1;

			/* MCi_STATUS */
			if (!msr_info->host_initiated &&
			    (offset & 0x3) == 1 && data != 0) {
				if (!can_set_mci_status(vcpu))
					return -1;
			}

			vcpu->arch.mce_banks[offset] = data;
			break;
		}
		return 1;
	}
	return 0;
}