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
typedef  int u64 ;
typedef  int u32 ;
struct TYPE_3__ {int pinbased_ctls_low; int pinbased_ctls_high; int procbased_ctls_low; int procbased_ctls_high; int exit_ctls_low; int exit_ctls_high; int entry_ctls_low; int entry_ctls_high; int secondary_ctls_low; int secondary_ctls_high; } ;
struct TYPE_4__ {TYPE_1__ msrs; } ;
struct vcpu_vmx {TYPE_2__ nested; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int EINVAL ; 
 int /*<<< orphan*/  GENMASK_ULL (int,int) ; 
#define  MSR_IA32_VMX_PROCBASED_CTLS2 132 
#define  MSR_IA32_VMX_TRUE_ENTRY_CTLS 131 
#define  MSR_IA32_VMX_TRUE_EXIT_CTLS 130 
#define  MSR_IA32_VMX_TRUE_PINBASED_CTLS 129 
#define  MSR_IA32_VMX_TRUE_PROCBASED_CTLS 128 
 int /*<<< orphan*/  is_bitwise_subset (int,int,int /*<<< orphan*/ ) ; 
 int vmx_control_msr (int,int) ; 

__attribute__((used)) static int
vmx_restore_control_msr(struct vcpu_vmx *vmx, u32 msr_index, u64 data)
{
	u64 supported;
	u32 *lowp, *highp;

	switch (msr_index) {
	case MSR_IA32_VMX_TRUE_PINBASED_CTLS:
		lowp = &vmx->nested.msrs.pinbased_ctls_low;
		highp = &vmx->nested.msrs.pinbased_ctls_high;
		break;
	case MSR_IA32_VMX_TRUE_PROCBASED_CTLS:
		lowp = &vmx->nested.msrs.procbased_ctls_low;
		highp = &vmx->nested.msrs.procbased_ctls_high;
		break;
	case MSR_IA32_VMX_TRUE_EXIT_CTLS:
		lowp = &vmx->nested.msrs.exit_ctls_low;
		highp = &vmx->nested.msrs.exit_ctls_high;
		break;
	case MSR_IA32_VMX_TRUE_ENTRY_CTLS:
		lowp = &vmx->nested.msrs.entry_ctls_low;
		highp = &vmx->nested.msrs.entry_ctls_high;
		break;
	case MSR_IA32_VMX_PROCBASED_CTLS2:
		lowp = &vmx->nested.msrs.secondary_ctls_low;
		highp = &vmx->nested.msrs.secondary_ctls_high;
		break;
	default:
		BUG();
	}

	supported = vmx_control_msr(*lowp, *highp);

	/* Check must-be-1 bits are still 1. */
	if (!is_bitwise_subset(data, supported, GENMASK_ULL(31, 0)))
		return -EINVAL;

	/* Check must-be-0 bits are still 0. */
	if (!is_bitwise_subset(supported, data, GENMASK_ULL(63, 32)))
		return -EINVAL;

	*lowp = data;
	*highp = data >> 32;
	return 0;
}