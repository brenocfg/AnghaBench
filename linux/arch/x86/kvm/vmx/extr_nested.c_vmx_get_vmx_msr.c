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
struct nested_vmx_msrs {int basic; int cr0_fixed0; int cr0_fixed1; int cr4_fixed0; int cr4_fixed1; int vmcs_enum; int ept_caps; int vmfunc_controls; int /*<<< orphan*/  vpid_caps; int /*<<< orphan*/  secondary_ctls_high; int /*<<< orphan*/  secondary_ctls_low; int /*<<< orphan*/  misc_high; int /*<<< orphan*/  misc_low; int /*<<< orphan*/  entry_ctls_high; int /*<<< orphan*/  entry_ctls_low; int /*<<< orphan*/  exit_ctls_high; int /*<<< orphan*/  exit_ctls_low; int /*<<< orphan*/  procbased_ctls_high; int /*<<< orphan*/  procbased_ctls_low; int /*<<< orphan*/  pinbased_ctls_high; int /*<<< orphan*/  pinbased_ctls_low; } ;

/* Variables and functions */
 int CPU_BASED_ALWAYSON_WITHOUT_TRUE_MSR ; 
#define  MSR_IA32_VMX_BASIC 145 
#define  MSR_IA32_VMX_CR0_FIXED0 144 
#define  MSR_IA32_VMX_CR0_FIXED1 143 
#define  MSR_IA32_VMX_CR4_FIXED0 142 
#define  MSR_IA32_VMX_CR4_FIXED1 141 
#define  MSR_IA32_VMX_ENTRY_CTLS 140 
#define  MSR_IA32_VMX_EPT_VPID_CAP 139 
#define  MSR_IA32_VMX_EXIT_CTLS 138 
#define  MSR_IA32_VMX_MISC 137 
#define  MSR_IA32_VMX_PINBASED_CTLS 136 
#define  MSR_IA32_VMX_PROCBASED_CTLS 135 
#define  MSR_IA32_VMX_PROCBASED_CTLS2 134 
#define  MSR_IA32_VMX_TRUE_ENTRY_CTLS 133 
#define  MSR_IA32_VMX_TRUE_EXIT_CTLS 132 
#define  MSR_IA32_VMX_TRUE_PINBASED_CTLS 131 
#define  MSR_IA32_VMX_TRUE_PROCBASED_CTLS 130 
#define  MSR_IA32_VMX_VMCS_ENUM 129 
#define  MSR_IA32_VMX_VMFUNC 128 
 int PIN_BASED_ALWAYSON_WITHOUT_TRUE_MSR ; 
 int VM_ENTRY_ALWAYSON_WITHOUT_TRUE_MSR ; 
 int VM_EXIT_ALWAYSON_WITHOUT_TRUE_MSR ; 
 int vmx_control_msr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int vmx_get_vmx_msr(struct nested_vmx_msrs *msrs, u32 msr_index, u64 *pdata)
{
	switch (msr_index) {
	case MSR_IA32_VMX_BASIC:
		*pdata = msrs->basic;
		break;
	case MSR_IA32_VMX_TRUE_PINBASED_CTLS:
	case MSR_IA32_VMX_PINBASED_CTLS:
		*pdata = vmx_control_msr(
			msrs->pinbased_ctls_low,
			msrs->pinbased_ctls_high);
		if (msr_index == MSR_IA32_VMX_PINBASED_CTLS)
			*pdata |= PIN_BASED_ALWAYSON_WITHOUT_TRUE_MSR;
		break;
	case MSR_IA32_VMX_TRUE_PROCBASED_CTLS:
	case MSR_IA32_VMX_PROCBASED_CTLS:
		*pdata = vmx_control_msr(
			msrs->procbased_ctls_low,
			msrs->procbased_ctls_high);
		if (msr_index == MSR_IA32_VMX_PROCBASED_CTLS)
			*pdata |= CPU_BASED_ALWAYSON_WITHOUT_TRUE_MSR;
		break;
	case MSR_IA32_VMX_TRUE_EXIT_CTLS:
	case MSR_IA32_VMX_EXIT_CTLS:
		*pdata = vmx_control_msr(
			msrs->exit_ctls_low,
			msrs->exit_ctls_high);
		if (msr_index == MSR_IA32_VMX_EXIT_CTLS)
			*pdata |= VM_EXIT_ALWAYSON_WITHOUT_TRUE_MSR;
		break;
	case MSR_IA32_VMX_TRUE_ENTRY_CTLS:
	case MSR_IA32_VMX_ENTRY_CTLS:
		*pdata = vmx_control_msr(
			msrs->entry_ctls_low,
			msrs->entry_ctls_high);
		if (msr_index == MSR_IA32_VMX_ENTRY_CTLS)
			*pdata |= VM_ENTRY_ALWAYSON_WITHOUT_TRUE_MSR;
		break;
	case MSR_IA32_VMX_MISC:
		*pdata = vmx_control_msr(
			msrs->misc_low,
			msrs->misc_high);
		break;
	case MSR_IA32_VMX_CR0_FIXED0:
		*pdata = msrs->cr0_fixed0;
		break;
	case MSR_IA32_VMX_CR0_FIXED1:
		*pdata = msrs->cr0_fixed1;
		break;
	case MSR_IA32_VMX_CR4_FIXED0:
		*pdata = msrs->cr4_fixed0;
		break;
	case MSR_IA32_VMX_CR4_FIXED1:
		*pdata = msrs->cr4_fixed1;
		break;
	case MSR_IA32_VMX_VMCS_ENUM:
		*pdata = msrs->vmcs_enum;
		break;
	case MSR_IA32_VMX_PROCBASED_CTLS2:
		*pdata = vmx_control_msr(
			msrs->secondary_ctls_low,
			msrs->secondary_ctls_high);
		break;
	case MSR_IA32_VMX_EPT_VPID_CAP:
		*pdata = msrs->ept_caps |
			((u64)msrs->vpid_caps << 32);
		break;
	case MSR_IA32_VMX_VMFUNC:
		*pdata = msrs->vmfunc_controls;
		break;
	default:
		return 1;
	}

	return 0;
}