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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 int /*<<< orphan*/  touch_nmi_watchdog () ; 
 int /*<<< orphan*/  udelay (scalar_t__) ; 

void acpi_os_stall(u32 us)
{
	while (us) {
		u32 delay = 1000;

		if (delay > us)
			delay = us;
		udelay(delay);
		touch_nmi_watchdog();
		us -= delay;
	}
}