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
struct TYPE_2__ {int /*<<< orphan*/  cop0; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int C_IRQ5 ; 
 int C_TI ; 
 int /*<<< orphan*/  MIPS_EXC_INT_TIMER ; 
 int /*<<< orphan*/  kvm_clear_c0_guest_cause (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kvm_mips_dequeue_irq (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 

void kvm_mips_dequeue_timer_int_cb(struct kvm_vcpu *vcpu)
{
	kvm_clear_c0_guest_cause(vcpu->arch.cop0, (C_IRQ5 | C_TI));
	kvm_mips_dequeue_irq(vcpu, MIPS_EXC_INT_TIMER);
}