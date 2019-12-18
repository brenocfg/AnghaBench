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
struct kvm_vcpu {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  vmcs01; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_nested (struct kvm_vcpu*) ; 
 TYPE_1__* to_vmx (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vcpu_load (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vcpu_put (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vmx_leave_nested (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vmx_switch_vmcs (struct kvm_vcpu*,int /*<<< orphan*/ *) ; 

void nested_vmx_free_vcpu(struct kvm_vcpu *vcpu)
{
	vcpu_load(vcpu);
	vmx_leave_nested(vcpu);
	vmx_switch_vmcs(vcpu, &to_vmx(vcpu)->vmcs01);
	free_nested(vcpu);
	vcpu_put(vcpu);
}