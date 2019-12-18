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
struct TYPE_2__ {unsigned long long current_vmptr; scalar_t__ hv_evmcs; } ;
struct vcpu_vmx {TYPE_1__ nested; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 scalar_t__ is_guest_mode (struct kvm_vcpu*) ; 
 struct vcpu_vmx* to_vmx (struct kvm_vcpu*) ; 

__attribute__((used)) static inline int vmx_has_valid_vmcs12(struct kvm_vcpu *vcpu)
{
	struct vcpu_vmx *vmx = to_vmx(vcpu);

	/*
	 * In case we do two consecutive get/set_nested_state()s while L2 was
	 * running hv_evmcs may end up not being mapped (we map it from
	 * nested_vmx_run()/vmx_vcpu_run()). Check is_guest_mode() as we always
	 * have vmcs12 if it is true.
	 */
	return is_guest_mode(vcpu) || vmx->nested.current_vmptr != -1ull ||
		vmx->nested.hv_evmcs;
}