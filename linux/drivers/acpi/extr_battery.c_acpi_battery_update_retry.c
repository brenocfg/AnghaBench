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
struct acpi_battery {int dummy; } ;

/* Variables and functions */
 int acpi_battery_update (struct acpi_battery*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int acpi_battery_update_retry(struct acpi_battery *battery)
{
	int retry, ret;

	for (retry = 5; retry; retry--) {
		ret = acpi_battery_update(battery, false);
		if (!ret)
			break;

		msleep(20);
	}
	return ret;
}