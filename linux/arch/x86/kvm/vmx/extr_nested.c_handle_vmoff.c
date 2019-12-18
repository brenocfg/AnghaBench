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
 int /*<<< orphan*/  KVM_REQ_EVENT ; 
 int /*<<< orphan*/  free_nested (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_make_request (int /*<<< orphan*/ ,struct kvm_vcpu*) ; 
 int /*<<< orphan*/  nested_vmx_check_permission (struct kvm_vcpu*) ; 
 int nested_vmx_succeed (struct kvm_vcpu*) ; 

__attribute__((used)) static int handle_vmoff(struct kvm_vcpu *vcpu)
{
	if (!nested_vmx_check_permission(vcpu))
		return 1;

	free_nested(vcpu);

	/* Process a latched INIT during time CPU was in VMX operation */
	kvm_make_request(KVM_REQ_EVENT, vcpu);

	return nested_vmx_succeed(vcpu);
}