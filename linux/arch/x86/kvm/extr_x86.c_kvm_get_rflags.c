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
struct kvm_vcpu {int guest_debug; } ;
struct TYPE_2__ {unsigned long (* get_rflags ) (struct kvm_vcpu*) ;} ;

/* Variables and functions */
 int KVM_GUESTDBG_SINGLESTEP ; 
 unsigned long X86_EFLAGS_TF ; 
 TYPE_1__* kvm_x86_ops ; 
 unsigned long stub1 (struct kvm_vcpu*) ; 

unsigned long kvm_get_rflags(struct kvm_vcpu *vcpu)
{
	unsigned long rflags;

	rflags = kvm_x86_ops->get_rflags(vcpu);
	if (vcpu->guest_debug & KVM_GUESTDBG_SINGLESTEP)
		rflags &= ~X86_EFLAGS_TF;
	return rflags;
}