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
 int /*<<< orphan*/  cpu_timer_interrupts_enabled (struct kvm_vcpu*) ; 
 int kvm_s390_get_cpu_timer (struct kvm_vcpu*) ; 

__attribute__((used)) static int cpu_timer_irq_pending(struct kvm_vcpu *vcpu)
{
	if (!cpu_timer_interrupts_enabled(vcpu))
		return 0;
	return kvm_s390_get_cpu_timer(vcpu) >> 63;
}