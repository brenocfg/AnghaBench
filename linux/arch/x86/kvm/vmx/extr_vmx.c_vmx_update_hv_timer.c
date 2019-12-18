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
typedef  int u32 ;
struct vcpu_vmx {int hv_deadline_tsc; TYPE_1__* loaded_vmcs; scalar_t__ req_immediate_exit; } ;
struct kvm_vcpu {int dummy; } ;
struct TYPE_2__ {int hv_timer_soft_disabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  VMX_PREEMPTION_TIMER_VALUE ; 
 int cpu_preemption_timer_multi ; 
 int rdtsc () ; 
 struct vcpu_vmx* to_vmx (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vmcs_write32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void vmx_update_hv_timer(struct kvm_vcpu *vcpu)
{
	struct vcpu_vmx *vmx = to_vmx(vcpu);
	u64 tscl;
	u32 delta_tsc;

	if (vmx->req_immediate_exit) {
		vmcs_write32(VMX_PREEMPTION_TIMER_VALUE, 0);
		vmx->loaded_vmcs->hv_timer_soft_disabled = false;
	} else if (vmx->hv_deadline_tsc != -1) {
		tscl = rdtsc();
		if (vmx->hv_deadline_tsc > tscl)
			/* set_hv_timer ensures the delta fits in 32-bits */
			delta_tsc = (u32)((vmx->hv_deadline_tsc - tscl) >>
				cpu_preemption_timer_multi);
		else
			delta_tsc = 0;

		vmcs_write32(VMX_PREEMPTION_TIMER_VALUE, delta_tsc);
		vmx->loaded_vmcs->hv_timer_soft_disabled = false;
	} else if (!vmx->loaded_vmcs->hv_timer_soft_disabled) {
		vmcs_write32(VMX_PREEMPTION_TIMER_VALUE, -1);
		vmx->loaded_vmcs->hv_timer_soft_disabled = true;
	}
}