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
struct vmcs12 {int /*<<< orphan*/  virtual_apic_page_addr; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 scalar_t__ CC (int) ; 
 int /*<<< orphan*/  CPU_BASED_TPR_SHADOW ; 
 int EINVAL ; 
 int /*<<< orphan*/  nested_cpu_has (struct vmcs12*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_address_valid (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nested_vmx_check_tpr_shadow_controls(struct kvm_vcpu *vcpu,
						struct vmcs12 *vmcs12)
{
	if (!nested_cpu_has(vmcs12, CPU_BASED_TPR_SHADOW))
		return 0;

	if (CC(!page_address_valid(vcpu, vmcs12->virtual_apic_page_addr)))
		return -EINVAL;

	return 0;
}