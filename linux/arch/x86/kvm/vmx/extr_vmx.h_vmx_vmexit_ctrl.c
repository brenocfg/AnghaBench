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
struct TYPE_2__ {int vmexit_ctrl; } ;

/* Variables and functions */
 scalar_t__ PT_MODE_SYSTEM ; 
 int VM_EXIT_CLEAR_IA32_RTIT_CTL ; 
 int VM_EXIT_LOAD_IA32_EFER ; 
 int VM_EXIT_LOAD_IA32_PERF_GLOBAL_CTRL ; 
 int VM_EXIT_PT_CONCEAL_PIP ; 
 scalar_t__ pt_mode ; 
 TYPE_1__ vmcs_config ; 

__attribute__((used)) static inline u32 vmx_vmexit_ctrl(void)
{
	u32 vmexit_ctrl = vmcs_config.vmexit_ctrl;
	if (pt_mode == PT_MODE_SYSTEM)
		vmexit_ctrl &= ~(VM_EXIT_PT_CONCEAL_PIP |
				 VM_EXIT_CLEAR_IA32_RTIT_CTL);
	/* Loading of EFER and PERF_GLOBAL_CTRL are toggled dynamically */
	return vmexit_ctrl &
		~(VM_EXIT_LOAD_IA32_PERF_GLOBAL_CTRL | VM_EXIT_LOAD_IA32_EFER);
}