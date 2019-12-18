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
struct vmcs12 {int /*<<< orphan*/  vmwrite_bitmap; int /*<<< orphan*/  vmread_bitmap; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 scalar_t__ CC (int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  nested_cpu_has_shadow_vmcs (struct vmcs12*) ; 
 int /*<<< orphan*/  page_address_valid (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nested_vmx_check_shadow_vmcs_controls(struct kvm_vcpu *vcpu,
						 struct vmcs12 *vmcs12)
{
	if (!nested_cpu_has_shadow_vmcs(vmcs12))
		return 0;

	if (CC(!page_address_valid(vcpu, vmcs12->vmread_bitmap)) ||
	    CC(!page_address_valid(vcpu, vmcs12->vmwrite_bitmap)))
		return -EINVAL;

	return 0;
}