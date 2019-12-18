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
struct vmcs12 {int vm_exit_controls; } ;

/* Variables and functions */
 int VM_EXIT_SAVE_VMX_PREEMPTION_TIMER ; 

__attribute__((used)) static inline bool nested_cpu_has_save_preemption_timer(struct vmcs12 *vmcs12)
{
	return vmcs12->vm_exit_controls &
	    VM_EXIT_SAVE_VMX_PREEMPTION_TIMER;
}