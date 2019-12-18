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
struct lapic {int lvt_timer_base; int lvt_timer_last; int la_timer_period; } ;

/* Variables and functions */
 int APIC_LVTT_TM ; 
 int APIC_LVTT_TM_PERIODIC ; 
 int APIC_LVT_M ; 
 int /*<<< orphan*/  LAPIC_ICR_TIMER ; 
 int /*<<< orphan*/  LAPIC_LVT_TIMER ; 
 int /*<<< orphan*/  lapic_write32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
lapic_timer_periodic(struct lapic *la)
{
	uint32_t value;

	value = la->lvt_timer_base;
	value &= ~(APIC_LVTT_TM | APIC_LVT_M);
	value |= APIC_LVTT_TM_PERIODIC;
	la->lvt_timer_last = value;
	lapic_write32(LAPIC_LVT_TIMER, value);
	lapic_write32(LAPIC_ICR_TIMER, la->la_timer_period);
}