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
struct vmcs12 {unsigned long cr4_guest_host_mask; unsigned long guest_cr4; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CR4_READ_SHADOW ; 
 struct vmcs12* get_vmcs12 (struct kvm_vcpu*) ; 
 scalar_t__ is_guest_mode (struct kvm_vcpu*) ; 
 int kvm_set_cr4 (struct kvm_vcpu*,unsigned long) ; 
 int /*<<< orphan*/  vmcs_writel (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int handle_set_cr4(struct kvm_vcpu *vcpu, unsigned long val)
{
	if (is_guest_mode(vcpu)) {
		struct vmcs12 *vmcs12 = get_vmcs12(vcpu);
		unsigned long orig_val = val;

		/* analogously to handle_set_cr0 */
		val = (val & ~vmcs12->cr4_guest_host_mask) |
			(vmcs12->guest_cr4 & vmcs12->cr4_guest_host_mask);
		if (kvm_set_cr4(vcpu, val))
			return 1;
		vmcs_writel(CR4_READ_SHADOW, orig_val);
		return 0;
	} else
		return kvm_set_cr4(vcpu, val);
}