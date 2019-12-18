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
typedef  int u32 ;
struct TYPE_2__ {int vmentry_ctrl; } ;

/* Variables and functions */
 scalar_t__ PT_MODE_SYSTEM ; 
 int VM_ENTRY_LOAD_IA32_EFER ; 
 int VM_ENTRY_LOAD_IA32_PERF_GLOBAL_CTRL ; 
 int VM_ENTRY_LOAD_IA32_RTIT_CTL ; 
 int VM_ENTRY_PT_CONCEAL_PIP ; 
 scalar_t__ pt_mode ; 
 TYPE_1__ vmcs_config ; 

__attribute__((used)) static inline u32 vmx_vmentry_ctrl(void)
{
	u32 vmentry_ctrl = vmcs_config.vmentry_ctrl;
	if (pt_mode == PT_MODE_SYSTEM)
		vmentry_ctrl &= ~(VM_ENTRY_PT_CONCEAL_PIP |
				  VM_ENTRY_LOAD_IA32_RTIT_CTL);
	/* Loading of EFER and PERF_GLOBAL_CTRL are toggled dynamically */
	return vmentry_ctrl &
		~(VM_ENTRY_LOAD_IA32_PERF_GLOBAL_CTRL | VM_ENTRY_LOAD_IA32_EFER);
}