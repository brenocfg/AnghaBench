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
struct TYPE_2__ {int cpu_based_2nd_exec_ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_IA32_VMX_MISC ; 
 int MSR_IA32_VMX_MISC_VMWRITE_SHADOW_RO_FIELDS ; 
 int SECONDARY_EXEC_SHADOW_VMCS ; 
 int /*<<< orphan*/  rdmsrl (int /*<<< orphan*/ ,int) ; 
 TYPE_1__ vmcs_config ; 

__attribute__((used)) static inline bool cpu_has_vmx_shadow_vmcs(void)
{
	u64 vmx_msr;

	/* check if the cpu supports writing r/o exit information fields */
	rdmsrl(MSR_IA32_VMX_MISC, vmx_msr);
	if (!(vmx_msr & MSR_IA32_VMX_MISC_VMWRITE_SHADOW_RO_FIELDS))
		return false;

	return vmcs_config.cpu_based_2nd_exec_ctrl &
		SECONDARY_EXEC_SHADOW_VMCS;
}