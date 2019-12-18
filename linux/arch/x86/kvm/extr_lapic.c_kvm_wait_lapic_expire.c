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
 int /*<<< orphan*/  __kvm_wait_lapic_expire (struct kvm_vcpu*) ; 
 scalar_t__ lapic_timer_int_injected (struct kvm_vcpu*) ; 

void kvm_wait_lapic_expire(struct kvm_vcpu *vcpu)
{
	if (lapic_timer_int_injected(vcpu))
		__kvm_wait_lapic_expire(vcpu);
}