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
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_3__ {int /*<<< orphan*/  vmfunc_controls; int /*<<< orphan*/  secondary_ctls_high; int /*<<< orphan*/  exit_ctls_high; int /*<<< orphan*/  entry_ctls_high; int /*<<< orphan*/  pinbased_ctls_high; } ;
struct TYPE_4__ {int enlightened_vmcs_enabled; TYPE_1__ msrs; } ;
struct vcpu_vmx {TYPE_2__ nested; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVMCS1_UNSUPPORTED_2NDEXEC ; 
 int /*<<< orphan*/  EVMCS1_UNSUPPORTED_PINCTRL ; 
 int /*<<< orphan*/  EVMCS1_UNSUPPORTED_VMENTRY_CTRL ; 
 int /*<<< orphan*/  EVMCS1_UNSUPPORTED_VMEXIT_CTRL ; 
 int /*<<< orphan*/  EVMCS1_UNSUPPORTED_VMFUNC ; 
 int /*<<< orphan*/  nested_get_evmcs_version (struct kvm_vcpu*) ; 
 struct vcpu_vmx* to_vmx (struct kvm_vcpu*) ; 

int nested_enable_evmcs(struct kvm_vcpu *vcpu,
			uint16_t *vmcs_version)
{
	struct vcpu_vmx *vmx = to_vmx(vcpu);
	bool evmcs_already_enabled = vmx->nested.enlightened_vmcs_enabled;

	vmx->nested.enlightened_vmcs_enabled = true;

	if (vmcs_version)
		*vmcs_version = nested_get_evmcs_version(vcpu);

	/* We don't support disabling the feature for simplicity. */
	if (evmcs_already_enabled)
		return 0;

	vmx->nested.msrs.pinbased_ctls_high &= ~EVMCS1_UNSUPPORTED_PINCTRL;
	vmx->nested.msrs.entry_ctls_high &= ~EVMCS1_UNSUPPORTED_VMENTRY_CTRL;
	vmx->nested.msrs.exit_ctls_high &= ~EVMCS1_UNSUPPORTED_VMEXIT_CTRL;
	vmx->nested.msrs.secondary_ctls_high &= ~EVMCS1_UNSUPPORTED_2NDEXEC;
	vmx->nested.msrs.vmfunc_controls &= ~EVMCS1_UNSUPPORTED_VMFUNC;

	return 0;
}