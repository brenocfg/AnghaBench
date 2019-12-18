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

/* Variables and functions */
 int /*<<< orphan*/  APIC_LVTT ; 
 unsigned int APIC_LVT_MASKED ; 
 unsigned int LOCAL_TIMER_VECTOR ; 
 int /*<<< orphan*/  apic_pm_activate () ; 
 unsigned int apic_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apic_write (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  lapic_setup_esr () ; 

__attribute__((used)) static void end_local_APIC_setup(void)
{
	lapic_setup_esr();

#ifdef CONFIG_X86_32
	{
		unsigned int value;
		/* Disable the local apic timer */
		value = apic_read(APIC_LVTT);
		value |= (APIC_LVT_MASKED | LOCAL_TIMER_VECTOR);
		apic_write(APIC_LVTT, value);
	}
#endif

	apic_pm_activate();
}