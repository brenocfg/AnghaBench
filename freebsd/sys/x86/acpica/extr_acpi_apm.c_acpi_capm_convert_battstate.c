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
struct acpi_battinfo {int state; int cap; } ;

/* Variables and functions */
 int ACPI_BATT_STAT_CHARGING ; 
 int ACPI_BATT_STAT_CRITICAL ; 
 int ACPI_BATT_STAT_DISCHARG ; 
 int APM_UNKNOWN ; 

__attribute__((used)) static int
acpi_capm_convert_battstate(struct  acpi_battinfo *battp)
{
	int	state;

	state = APM_UNKNOWN;

	if (battp->state & ACPI_BATT_STAT_DISCHARG) {
		if (battp->cap >= 50)
			state = 0;	/* high */
		else
			state = 1;	/* low */
	}
	if (battp->state & ACPI_BATT_STAT_CRITICAL)
		state = 2;		/* critical */
	if (battp->state & ACPI_BATT_STAT_CHARGING)
		state = 3;		/* charging */

	/* If still unknown, determine it based on the battery capacity. */
	if (state == APM_UNKNOWN) {
		if (battp->cap >= 50)
			state = 0;	/* high */
		else
			state = 1;	/* low */
	}

	return (state);
}