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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ timer_mode_mask; scalar_t__ timer_mode; scalar_t__ tscdeadline; scalar_t__ period; int /*<<< orphan*/  timer; } ;
struct kvm_lapic {TYPE_1__ lapic_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  APIC_LVTT ; 
 scalar_t__ APIC_LVT_TIMER_TSCDEADLINE ; 
 int /*<<< orphan*/  APIC_TMICT ; 
 int apic_lvtt_tscdeadline (struct kvm_lapic*) ; 
 int /*<<< orphan*/  hrtimer_cancel (int /*<<< orphan*/ *) ; 
 scalar_t__ kvm_lapic_get_reg (struct kvm_lapic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_lapic_set_reg (struct kvm_lapic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  limit_periodic_timer_frequency (struct kvm_lapic*) ; 

__attribute__((used)) static void apic_update_lvtt(struct kvm_lapic *apic)
{
	u32 timer_mode = kvm_lapic_get_reg(apic, APIC_LVTT) &
			apic->lapic_timer.timer_mode_mask;

	if (apic->lapic_timer.timer_mode != timer_mode) {
		if (apic_lvtt_tscdeadline(apic) != (timer_mode ==
				APIC_LVT_TIMER_TSCDEADLINE)) {
			hrtimer_cancel(&apic->lapic_timer.timer);
			kvm_lapic_set_reg(apic, APIC_TMICT, 0);
			apic->lapic_timer.period = 0;
			apic->lapic_timer.tscdeadline = 0;
		}
		apic->lapic_timer.timer_mode = timer_mode;
		limit_periodic_timer_frequency(apic);
	}
}