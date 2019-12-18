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
struct TYPE_2__ {int vmentry_ctrl; int vmexit_ctrl; } ;

/* Variables and functions */
 int VM_ENTRY_LOAD_IA32_PERF_GLOBAL_CTRL ; 
 int VM_EXIT_LOAD_IA32_PERF_GLOBAL_CTRL ; 
 TYPE_1__ vmcs_config ; 

__attribute__((used)) static inline bool cpu_has_load_perf_global_ctrl(void)
{
	return (vmcs_config.vmentry_ctrl & VM_ENTRY_LOAD_IA32_PERF_GLOBAL_CTRL) &&
	       (vmcs_config.vmexit_ctrl & VM_EXIT_LOAD_IA32_PERF_GLOBAL_CTRL);
}