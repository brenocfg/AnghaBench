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
 scalar_t__ kvm_arch_interrupt_allowed (struct kvm_vcpu*) ; 
 scalar_t__ kvm_cpu_accept_dm_intr (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_cpu_has_interrupt (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_event_needs_reinjection (struct kvm_vcpu*) ; 

__attribute__((used)) static int kvm_vcpu_ready_for_interrupt_injection(struct kvm_vcpu *vcpu)
{
	return kvm_arch_interrupt_allowed(vcpu) &&
		!kvm_cpu_has_interrupt(vcpu) &&
		!kvm_event_needs_reinjection(vcpu) &&
		kvm_cpu_accept_dm_intr(vcpu);
}