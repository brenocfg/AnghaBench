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
struct vmcs12 {int /*<<< orphan*/  vm_exit_controls; } ;
struct TYPE_3__ {int /*<<< orphan*/  exit_ctls_high; int /*<<< orphan*/  exit_ctls_low; } ;
struct TYPE_4__ {TYPE_1__ msrs; } ;
struct vcpu_vmx {TYPE_2__ nested; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 scalar_t__ CC (int) ; 
 int EINVAL ; 
 int nested_vmx_check_exit_msr_switch_controls (struct kvm_vcpu*,struct vmcs12*) ; 
 struct vcpu_vmx* to_vmx (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vmx_control_verify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nested_check_vm_exit_controls(struct kvm_vcpu *vcpu,
                                         struct vmcs12 *vmcs12)
{
	struct vcpu_vmx *vmx = to_vmx(vcpu);

	if (CC(!vmx_control_verify(vmcs12->vm_exit_controls,
				    vmx->nested.msrs.exit_ctls_low,
				    vmx->nested.msrs.exit_ctls_high)) ||
	    CC(nested_vmx_check_exit_msr_switch_controls(vcpu, vmcs12)))
		return -EINVAL;

	return 0;
}