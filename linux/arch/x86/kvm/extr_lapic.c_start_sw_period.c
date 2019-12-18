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
struct TYPE_2__ {int /*<<< orphan*/  target_expiration; int /*<<< orphan*/  timer; int /*<<< orphan*/  period; } ;
struct kvm_lapic {TYPE_1__ lapic_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  HRTIMER_MODE_ABS ; 
 int /*<<< orphan*/  advance_periodic_target_expiration (struct kvm_lapic*) ; 
 scalar_t__ apic_lvtt_oneshot (struct kvm_lapic*) ; 
 int /*<<< orphan*/  apic_timer_expired (struct kvm_lapic*) ; 
 int /*<<< orphan*/  hrtimer_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ktime_after (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get () ; 

__attribute__((used)) static void start_sw_period(struct kvm_lapic *apic)
{
	if (!apic->lapic_timer.period)
		return;

	if (ktime_after(ktime_get(),
			apic->lapic_timer.target_expiration)) {
		apic_timer_expired(apic);

		if (apic_lvtt_oneshot(apic))
			return;

		advance_periodic_target_expiration(apic);
	}

	hrtimer_start(&apic->lapic_timer.timer,
		apic->lapic_timer.target_expiration,
		HRTIMER_MODE_ABS);
}