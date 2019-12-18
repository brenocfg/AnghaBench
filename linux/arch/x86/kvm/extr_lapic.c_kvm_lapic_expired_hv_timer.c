#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct kvm_lapic* apic; } ;
struct kvm_vcpu {int /*<<< orphan*/  wq; TYPE_1__ arch; } ;
struct TYPE_4__ {scalar_t__ period; int /*<<< orphan*/  hv_timer_in_use; } ;
struct kvm_lapic {TYPE_2__ lapic_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  advance_periodic_target_expiration (struct kvm_lapic*) ; 
 scalar_t__ apic_lvtt_period (struct kvm_lapic*) ; 
 int /*<<< orphan*/  apic_timer_expired (struct kvm_lapic*) ; 
 int /*<<< orphan*/  cancel_hv_timer (struct kvm_lapic*) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  restart_apic_timer (struct kvm_lapic*) ; 
 int /*<<< orphan*/  swait_active (int /*<<< orphan*/ *) ; 

void kvm_lapic_expired_hv_timer(struct kvm_vcpu *vcpu)
{
	struct kvm_lapic *apic = vcpu->arch.apic;

	preempt_disable();
	/* If the preempt notifier has already run, it also called apic_timer_expired */
	if (!apic->lapic_timer.hv_timer_in_use)
		goto out;
	WARN_ON(swait_active(&vcpu->wq));
	cancel_hv_timer(apic);
	apic_timer_expired(apic);

	if (apic_lvtt_period(apic) && apic->lapic_timer.period) {
		advance_periodic_target_expiration(apic);
		restart_apic_timer(apic);
	}
out:
	preempt_enable();
}