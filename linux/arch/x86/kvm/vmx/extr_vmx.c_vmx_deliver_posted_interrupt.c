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
struct vcpu_vmx {int /*<<< orphan*/  pi_desc; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvm_vcpu_kick (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_vcpu_trigger_posted_interrupt (struct kvm_vcpu*,int) ; 
 scalar_t__ pi_test_and_set_on (int /*<<< orphan*/ *) ; 
 scalar_t__ pi_test_and_set_pir (int,int /*<<< orphan*/ *) ; 
 struct vcpu_vmx* to_vmx (struct kvm_vcpu*) ; 
 int vmx_deliver_nested_posted_interrupt (struct kvm_vcpu*,int) ; 

__attribute__((used)) static void vmx_deliver_posted_interrupt(struct kvm_vcpu *vcpu, int vector)
{
	struct vcpu_vmx *vmx = to_vmx(vcpu);
	int r;

	r = vmx_deliver_nested_posted_interrupt(vcpu, vector);
	if (!r)
		return;

	if (pi_test_and_set_pir(vector, &vmx->pi_desc))
		return;

	/* If a previous notification has sent the IPI, nothing to do.  */
	if (pi_test_and_set_on(&vmx->pi_desc))
		return;

	if (!kvm_vcpu_trigger_posted_interrupt(vcpu, false))
		kvm_vcpu_kick(vcpu);
}