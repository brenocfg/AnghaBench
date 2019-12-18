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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct TYPE_3__ {int /*<<< orphan*/  cr4_fixed0; int /*<<< orphan*/  cr0_fixed0; } ;
struct TYPE_4__ {TYPE_1__ msrs; } ;
struct vcpu_vmx {TYPE_2__ nested; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int EINVAL ; 
#define  MSR_IA32_VMX_CR0_FIXED0 129 
#define  MSR_IA32_VMX_CR4_FIXED0 128 
 int /*<<< orphan*/  is_bitwise_subset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long long) ; 

__attribute__((used)) static int vmx_restore_fixed0_msr(struct vcpu_vmx *vmx, u32 msr_index, u64 data)
{
	u64 *msr;

	switch (msr_index) {
	case MSR_IA32_VMX_CR0_FIXED0:
		msr = &vmx->nested.msrs.cr0_fixed0;
		break;
	case MSR_IA32_VMX_CR4_FIXED0:
		msr = &vmx->nested.msrs.cr4_fixed0;
		break;
	default:
		BUG();
	}

	/*
	 * 1 bits (which indicates bits which "must-be-1" during VMX operation)
	 * must be 1 in the restored value.
	 */
	if (!is_bitwise_subset(data, *msr, -1ULL))
		return -EINVAL;

	*msr = data;
	return 0;
}