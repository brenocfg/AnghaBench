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
struct clock_event_device {int features; } ;

/* Variables and functions */
 int /*<<< orphan*/  APIC_LVTT ; 
 unsigned int APIC_LVT_MASKED ; 
 int /*<<< orphan*/  APIC_TMICT ; 
 int CLOCK_EVT_FEAT_DUMMY ; 
 unsigned int LOCAL_TIMER_VECTOR ; 
 unsigned int apic_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apic_write (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int lapic_timer_shutdown(struct clock_event_device *evt)
{
	unsigned int v;

	/* Lapic used as dummy for broadcast ? */
	if (evt->features & CLOCK_EVT_FEAT_DUMMY)
		return 0;

	v = apic_read(APIC_LVTT);
	v |= (APIC_LVT_MASKED | LOCAL_TIMER_VECTOR);
	apic_write(APIC_LVTT, v);
	apic_write(APIC_TMICT, 0);
	return 0;
}