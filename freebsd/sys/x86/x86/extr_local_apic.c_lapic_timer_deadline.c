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
typedef  int uint32_t ;
struct lapic {int lvt_timer_base; int lvt_timer_last; scalar_t__ la_timer_period; } ;

/* Variables and functions */
 int APIC_LVTT_TM ; 
 int APIC_LVTT_TM_TSCDLT ; 
 int APIC_LVT_M ; 
 int /*<<< orphan*/  LAPIC_LVT_TIMER ; 
 int /*<<< orphan*/  MSR_TSC_DEADLINE ; 
 int /*<<< orphan*/  lapic_write32_nofence (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mfence () ; 
 scalar_t__ rdtsc () ; 
 int /*<<< orphan*/  wrmsr (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  x2apic_mode ; 

__attribute__((used)) static void
lapic_timer_deadline(struct lapic *la)
{
	uint32_t value;

	value = la->lvt_timer_base;
	value &= ~(APIC_LVTT_TM | APIC_LVT_M);
	value |= APIC_LVTT_TM_TSCDLT;
	if (value != la->lvt_timer_last) {
		la->lvt_timer_last = value;
		lapic_write32_nofence(LAPIC_LVT_TIMER, value);
		if (!x2apic_mode)
			mfence();
	}
	wrmsr(MSR_TSC_DEADLINE, la->la_timer_period + rdtsc());
}