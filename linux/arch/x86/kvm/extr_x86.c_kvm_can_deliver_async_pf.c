#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int msr_val; scalar_t__ send_user_only; int /*<<< orphan*/  delivery_as_pf_vmexit; } ;
struct TYPE_5__ {TYPE_1__ apf; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;
struct TYPE_6__ {scalar_t__ (* get_cpl ) (struct kvm_vcpu*) ;} ;

/* Variables and functions */
 int KVM_ASYNC_PF_ENABLED ; 
 scalar_t__ is_guest_mode (struct kvm_vcpu*) ; 
 TYPE_3__* kvm_x86_ops ; 
 scalar_t__ stub1 (struct kvm_vcpu*) ; 

__attribute__((used)) static bool kvm_can_deliver_async_pf(struct kvm_vcpu *vcpu)
{
	if (!vcpu->arch.apf.delivery_as_pf_vmexit && is_guest_mode(vcpu))
		return false;

	if (!(vcpu->arch.apf.msr_val & KVM_ASYNC_PF_ENABLED) ||
	    (vcpu->arch.apf.send_user_only &&
	     kvm_x86_ops->get_cpl(vcpu) == 0))
		return false;

	return true;
}