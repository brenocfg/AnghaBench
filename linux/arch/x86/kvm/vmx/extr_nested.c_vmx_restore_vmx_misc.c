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
struct TYPE_3__ {int misc_low; int misc_high; int pinbased_ctls_high; } ;
struct TYPE_4__ {TYPE_1__ msrs; } ;
struct vcpu_vmx {TYPE_2__ nested; } ;

/* Variables and functions */
 int BIT_ULL (int) ; 
 int EINVAL ; 
 int GENMASK_ULL (int,int) ; 
 int PIN_BASED_VMX_PREEMPTION_TIMER ; 
 int /*<<< orphan*/  is_bitwise_subset (int,int,int const) ; 
 int vmx_control_msr (int,int) ; 
 scalar_t__ vmx_misc_cr3_count (int) ; 
 scalar_t__ vmx_misc_max_msr (int) ; 
 scalar_t__ vmx_misc_mseg_revid (int) ; 
 scalar_t__ vmx_misc_preemption_timer_rate (int) ; 

__attribute__((used)) static int vmx_restore_vmx_misc(struct vcpu_vmx *vmx, u64 data)
{
	const u64 feature_and_reserved_bits =
		/* feature */
		BIT_ULL(5) | GENMASK_ULL(8, 6) | BIT_ULL(14) | BIT_ULL(15) |
		BIT_ULL(28) | BIT_ULL(29) | BIT_ULL(30) |
		/* reserved */
		GENMASK_ULL(13, 9) | BIT_ULL(31);
	u64 vmx_misc;

	vmx_misc = vmx_control_msr(vmx->nested.msrs.misc_low,
				   vmx->nested.msrs.misc_high);

	if (!is_bitwise_subset(vmx_misc, data, feature_and_reserved_bits))
		return -EINVAL;

	if ((vmx->nested.msrs.pinbased_ctls_high &
	     PIN_BASED_VMX_PREEMPTION_TIMER) &&
	    vmx_misc_preemption_timer_rate(data) !=
	    vmx_misc_preemption_timer_rate(vmx_misc))
		return -EINVAL;

	if (vmx_misc_cr3_count(data) > vmx_misc_cr3_count(vmx_misc))
		return -EINVAL;

	if (vmx_misc_max_msr(data) > vmx_misc_max_msr(vmx_misc))
		return -EINVAL;

	if (vmx_misc_mseg_revid(data) != vmx_misc_mseg_revid(vmx_misc))
		return -EINVAL;

	vmx->nested.msrs.misc_low = data;
	vmx->nested.msrs.misc_high = data >> 32;

	return 0;
}