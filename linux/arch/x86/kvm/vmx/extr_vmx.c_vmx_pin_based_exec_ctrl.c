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
typedef  int /*<<< orphan*/  u32 ;
struct vcpu_vmx {int /*<<< orphan*/  vcpu; } ;
struct TYPE_2__ {int /*<<< orphan*/  pin_based_exec_ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  PIN_BASED_POSTED_INTR ; 
 int /*<<< orphan*/  PIN_BASED_VIRTUAL_NMIS ; 
 int /*<<< orphan*/  PIN_BASED_VMX_PREEMPTION_TIMER ; 
 int /*<<< orphan*/  enable_preemption_timer ; 
 int /*<<< orphan*/  enable_vnmi ; 
 int /*<<< orphan*/  kvm_vcpu_apicv_active (int /*<<< orphan*/ *) ; 
 TYPE_1__ vmcs_config ; 

u32 vmx_pin_based_exec_ctrl(struct vcpu_vmx *vmx)
{
	u32 pin_based_exec_ctrl = vmcs_config.pin_based_exec_ctrl;

	if (!kvm_vcpu_apicv_active(&vmx->vcpu))
		pin_based_exec_ctrl &= ~PIN_BASED_POSTED_INTR;

	if (!enable_vnmi)
		pin_based_exec_ctrl &= ~PIN_BASED_VIRTUAL_NMIS;

	if (!enable_preemption_timer)
		pin_based_exec_ctrl &= ~PIN_BASED_VMX_PREEMPTION_TIMER;

	return pin_based_exec_ctrl;
}