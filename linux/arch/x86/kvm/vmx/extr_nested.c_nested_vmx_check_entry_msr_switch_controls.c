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
struct vmcs12 {int /*<<< orphan*/  vm_entry_msr_load_addr; int /*<<< orphan*/  vm_entry_msr_load_count; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 scalar_t__ CC (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  nested_vmx_check_msr_switch (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nested_vmx_check_entry_msr_switch_controls(struct kvm_vcpu *vcpu,
                                                      struct vmcs12 *vmcs12)
{
	if (CC(nested_vmx_check_msr_switch(vcpu,
					   vmcs12->vm_entry_msr_load_count,
					   vmcs12->vm_entry_msr_load_addr)))
                return -EINVAL;

	return 0;
}