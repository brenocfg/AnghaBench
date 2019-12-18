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
struct kvm_timer {scalar_t__ target_expiration; scalar_t__ tscdeadline; } ;
struct kvm_lapic {struct kvm_timer lapic_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  APIC_LVTT ; 
 scalar_t__ apic_lvtt_oneshot (struct kvm_lapic*) ; 
 scalar_t__ apic_lvtt_tscdeadline (struct kvm_lapic*) ; 
 int /*<<< orphan*/  kvm_apic_local_deliver (struct kvm_lapic*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kvm_apic_inject_pending_timer_irqs(struct kvm_lapic *apic)
{
	struct kvm_timer *ktimer = &apic->lapic_timer;

	kvm_apic_local_deliver(apic, APIC_LVTT);
	if (apic_lvtt_tscdeadline(apic))
		ktimer->tscdeadline = 0;
	if (apic_lvtt_oneshot(apic)) {
		ktimer->tscdeadline = 0;
		ktimer->target_expiration = 0;
	}
}