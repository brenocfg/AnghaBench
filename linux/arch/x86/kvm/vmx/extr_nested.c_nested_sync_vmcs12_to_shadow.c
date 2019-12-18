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
struct TYPE_4__ {int need_vmcs12_to_shadow_sync; TYPE_1__* hv_evmcs; scalar_t__ enlightened_vmcs_enabled; } ;
struct vcpu_vmx {TYPE_2__ nested; } ;
struct kvm_vcpu {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  hv_clean_fields; } ;

/* Variables and functions */
 int /*<<< orphan*/  HV_VMX_ENLIGHTENED_CLEAN_FIELD_ALL ; 
 int /*<<< orphan*/  copy_vmcs12_to_enlightened (struct vcpu_vmx*) ; 
 int /*<<< orphan*/  copy_vmcs12_to_shadow (struct vcpu_vmx*) ; 
 int /*<<< orphan*/  nested_vmx_handle_enlightened_vmptrld (struct kvm_vcpu*,int) ; 
 struct vcpu_vmx* to_vmx (struct kvm_vcpu*) ; 

void nested_sync_vmcs12_to_shadow(struct kvm_vcpu *vcpu)
{
	struct vcpu_vmx *vmx = to_vmx(vcpu);

	/*
	 * hv_evmcs may end up being not mapped after migration (when
	 * L2 was running), map it here to make sure vmcs12 changes are
	 * properly reflected.
	 */
	if (vmx->nested.enlightened_vmcs_enabled && !vmx->nested.hv_evmcs)
		nested_vmx_handle_enlightened_vmptrld(vcpu, false);

	if (vmx->nested.hv_evmcs) {
		copy_vmcs12_to_enlightened(vmx);
		/* All fields are clean */
		vmx->nested.hv_evmcs->hv_clean_fields |=
			HV_VMX_ENLIGHTENED_CLEAN_FIELD_ALL;
	} else {
		copy_vmcs12_to_shadow(vmx);
	}

	vmx->nested.need_vmcs12_to_shadow_sync = false;
}