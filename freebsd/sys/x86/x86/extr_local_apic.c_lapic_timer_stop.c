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
typedef  int /*<<< orphan*/  uint32_t ;
struct lapic {scalar_t__ la_timer_mode; int /*<<< orphan*/  lvt_timer_last; int /*<<< orphan*/  lvt_timer_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  APIC_LVTT_TM ; 
 int /*<<< orphan*/  APIC_LVT_M ; 
 int /*<<< orphan*/  LAPIC_LVT_TIMER ; 
 scalar_t__ LAT_MODE_DEADLINE ; 
 int /*<<< orphan*/  MSR_TSC_DEADLINE ; 
 int /*<<< orphan*/  lapic_write32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mfence () ; 
 int /*<<< orphan*/  wrmsr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
lapic_timer_stop(struct lapic *la)
{
	uint32_t value;

	if (la->la_timer_mode == LAT_MODE_DEADLINE) {
		wrmsr(MSR_TSC_DEADLINE, 0);
		mfence();
	} else {
		value = la->lvt_timer_base;
		value &= ~APIC_LVTT_TM;
		value |= APIC_LVT_M;
		la->lvt_timer_last = value;
		lapic_write32(LAPIC_LVT_TIMER, value);
	}
}