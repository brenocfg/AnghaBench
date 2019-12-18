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
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_vmcs12 (struct kvm_vcpu*) ; 
 int nested_cpu_has_nmi_exiting (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool nested_exit_on_nmi(struct kvm_vcpu *vcpu)
{
	return nested_cpu_has_nmi_exiting(get_vmcs12(vcpu));
}