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
typedef  int u32 ;
struct kvm_vcpu {int dummy; } ;
struct TYPE_2__ {int (* get_interrupt_shadow ) (struct kvm_vcpu*) ;int /*<<< orphan*/  (* set_interrupt_shadow ) (struct kvm_vcpu*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_REQ_EVENT ; 
 int /*<<< orphan*/  kvm_make_request (int /*<<< orphan*/ ,struct kvm_vcpu*) ; 
 TYPE_1__* kvm_x86_ops ; 
 int stub1 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  stub2 (struct kvm_vcpu*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void toggle_interruptibility(struct kvm_vcpu *vcpu, u32 mask)
{
	u32 int_shadow = kvm_x86_ops->get_interrupt_shadow(vcpu);
	/*
	 * an sti; sti; sequence only disable interrupts for the first
	 * instruction. So, if the last instruction, be it emulated or
	 * not, left the system with the INT_STI flag enabled, it
	 * means that the last instruction is an sti. We should not
	 * leave the flag on in this case. The same goes for mov ss
	 */
	if (int_shadow & mask)
		mask = 0;
	if (unlikely(int_shadow || mask)) {
		kvm_x86_ops->set_interrupt_shadow(vcpu, mask);
		if (!mask)
			kvm_make_request(KVM_REQ_EVENT, vcpu);
	}
}