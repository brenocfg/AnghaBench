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
 int /*<<< orphan*/  MIPS_EXC_INT_TIMER ; 
 int /*<<< orphan*/  kvm_vz_dequeue_irq (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kvm_vz_dequeue_timer_int_cb(struct kvm_vcpu *vcpu)
{
	/*
	 * timer expiry is asynchronous to vcpu execution therefore defer guest
	 * cp0 accesses
	 */
	kvm_vz_dequeue_irq(vcpu, MIPS_EXC_INT_TIMER);
}