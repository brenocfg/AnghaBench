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
struct kvm_timer {int /*<<< orphan*/  pending; scalar_t__ timer_advance_ns; int /*<<< orphan*/  tscdeadline; int /*<<< orphan*/  expired_tscdeadline; scalar_t__ hv_timer_in_use; } ;
struct kvm_lapic {struct kvm_timer lapic_timer; struct kvm_vcpu* vcpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  __kvm_wait_lapic_expire (struct kvm_vcpu*) ; 
 scalar_t__ apic_lvtt_tscdeadline (struct kvm_lapic*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvm_apic_inject_pending_timer_irqs (struct kvm_lapic*) ; 
 int /*<<< orphan*/  kvm_set_pending_timer (struct kvm_vcpu*) ; 
 scalar_t__ kvm_use_posted_timer_interrupt (struct kvm_vcpu*) ; 

__attribute__((used)) static void apic_timer_expired(struct kvm_lapic *apic)
{
	struct kvm_vcpu *vcpu = apic->vcpu;
	struct kvm_timer *ktimer = &apic->lapic_timer;

	if (atomic_read(&apic->lapic_timer.pending))
		return;

	if (apic_lvtt_tscdeadline(apic) || ktimer->hv_timer_in_use)
		ktimer->expired_tscdeadline = ktimer->tscdeadline;

	if (kvm_use_posted_timer_interrupt(apic->vcpu)) {
		if (apic->lapic_timer.timer_advance_ns)
			__kvm_wait_lapic_expire(vcpu);
		kvm_apic_inject_pending_timer_irqs(apic);
		return;
	}

	atomic_inc(&apic->lapic_timer.pending);
	kvm_set_pending_timer(vcpu);
}