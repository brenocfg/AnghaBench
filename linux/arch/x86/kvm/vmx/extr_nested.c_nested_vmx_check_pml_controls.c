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
struct vmcs12 {int /*<<< orphan*/  pml_address; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 scalar_t__ CC (int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  nested_cpu_has_ept (struct vmcs12*) ; 
 int /*<<< orphan*/  nested_cpu_has_pml (struct vmcs12*) ; 
 int /*<<< orphan*/  page_address_valid (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nested_vmx_check_pml_controls(struct kvm_vcpu *vcpu,
					 struct vmcs12 *vmcs12)
{
	if (!nested_cpu_has_pml(vmcs12))
		return 0;

	if (CC(!nested_cpu_has_ept(vmcs12)) ||
	    CC(!page_address_valid(vcpu, vmcs12->pml_address)))
		return -EINVAL;

	return 0;
}