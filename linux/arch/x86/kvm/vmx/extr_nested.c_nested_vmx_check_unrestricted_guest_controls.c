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
struct vmcs12 {int dummy; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 scalar_t__ CC (int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  SECONDARY_EXEC_UNRESTRICTED_GUEST ; 
 scalar_t__ nested_cpu_has2 (struct vmcs12*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nested_cpu_has_ept (struct vmcs12*) ; 

__attribute__((used)) static int nested_vmx_check_unrestricted_guest_controls(struct kvm_vcpu *vcpu,
							struct vmcs12 *vmcs12)
{
	if (CC(nested_cpu_has2(vmcs12, SECONDARY_EXEC_UNRESTRICTED_GUEST) &&
	       !nested_cpu_has_ept(vmcs12)))
		return -EINVAL;
	return 0;
}