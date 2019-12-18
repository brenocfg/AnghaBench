#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_5__ {int ctl; } ;
struct TYPE_6__ {int addr_range; TYPE_2__ guest; } ;
struct TYPE_4__ {unsigned long* msr_bitmap; } ;
struct vcpu_vmx {TYPE_3__ pt_desc; TYPE_1__ vmcs01; } ;

/* Variables and functions */
 scalar_t__ MSR_IA32_RTIT_ADDR0_A ; 
 scalar_t__ MSR_IA32_RTIT_ADDR0_B ; 
 scalar_t__ MSR_IA32_RTIT_CR3_MATCH ; 
 scalar_t__ MSR_IA32_RTIT_OUTPUT_BASE ; 
 scalar_t__ MSR_IA32_RTIT_OUTPUT_MASK ; 
 scalar_t__ MSR_IA32_RTIT_STATUS ; 
 int /*<<< orphan*/  MSR_TYPE_RW ; 
 int RTIT_CTL_TRACEEN ; 
 int /*<<< orphan*/  vmx_set_intercept_for_msr (unsigned long*,scalar_t__,int /*<<< orphan*/ ,int) ; 

void pt_update_intercept_for_msr(struct vcpu_vmx *vmx)
{
	unsigned long *msr_bitmap = vmx->vmcs01.msr_bitmap;
	bool flag = !(vmx->pt_desc.guest.ctl & RTIT_CTL_TRACEEN);
	u32 i;

	vmx_set_intercept_for_msr(msr_bitmap, MSR_IA32_RTIT_STATUS,
							MSR_TYPE_RW, flag);
	vmx_set_intercept_for_msr(msr_bitmap, MSR_IA32_RTIT_OUTPUT_BASE,
							MSR_TYPE_RW, flag);
	vmx_set_intercept_for_msr(msr_bitmap, MSR_IA32_RTIT_OUTPUT_MASK,
							MSR_TYPE_RW, flag);
	vmx_set_intercept_for_msr(msr_bitmap, MSR_IA32_RTIT_CR3_MATCH,
							MSR_TYPE_RW, flag);
	for (i = 0; i < vmx->pt_desc.addr_range; i++) {
		vmx_set_intercept_for_msr(msr_bitmap,
			MSR_IA32_RTIT_ADDR0_A + i * 2, MSR_TYPE_RW, flag);
		vmx_set_intercept_for_msr(msr_bitmap,
			MSR_IA32_RTIT_ADDR0_B + i * 2, MSR_TYPE_RW, flag);
	}
}