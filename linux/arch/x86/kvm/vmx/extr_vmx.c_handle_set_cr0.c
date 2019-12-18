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
struct vmcs12 {unsigned long cr0_guest_host_mask; unsigned long guest_cr0; } ;
struct kvm_vcpu {int dummy; } ;
struct TYPE_3__ {scalar_t__ vmxon; } ;
struct TYPE_4__ {TYPE_1__ nested; } ;

/* Variables and functions */
 int /*<<< orphan*/  CR0_READ_SHADOW ; 
 struct vmcs12* get_vmcs12 (struct kvm_vcpu*) ; 
 scalar_t__ is_guest_mode (struct kvm_vcpu*) ; 
 int kvm_set_cr0 (struct kvm_vcpu*,unsigned long) ; 
 int /*<<< orphan*/  nested_guest_cr0_valid (struct kvm_vcpu*,unsigned long) ; 
 int /*<<< orphan*/  nested_host_cr0_valid (struct kvm_vcpu*,unsigned long) ; 
 TYPE_2__* to_vmx (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vmcs_writel (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int handle_set_cr0(struct kvm_vcpu *vcpu, unsigned long val)
{
	if (is_guest_mode(vcpu)) {
		struct vmcs12 *vmcs12 = get_vmcs12(vcpu);
		unsigned long orig_val = val;

		/*
		 * We get here when L2 changed cr0 in a way that did not change
		 * any of L1's shadowed bits (see nested_vmx_exit_handled_cr),
		 * but did change L0 shadowed bits. So we first calculate the
		 * effective cr0 value that L1 would like to write into the
		 * hardware. It consists of the L2-owned bits from the new
		 * value combined with the L1-owned bits from L1's guest_cr0.
		 */
		val = (val & ~vmcs12->cr0_guest_host_mask) |
			(vmcs12->guest_cr0 & vmcs12->cr0_guest_host_mask);

		if (!nested_guest_cr0_valid(vcpu, val))
			return 1;

		if (kvm_set_cr0(vcpu, val))
			return 1;
		vmcs_writel(CR0_READ_SHADOW, orig_val);
		return 0;
	} else {
		if (to_vmx(vcpu)->nested.vmxon &&
		    !nested_host_cr0_valid(vcpu, val))
			return 1;

		return kvm_set_cr0(vcpu, val);
	}
}