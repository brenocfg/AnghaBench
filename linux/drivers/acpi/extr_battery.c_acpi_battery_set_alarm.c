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
struct acpi_battery {int /*<<< orphan*/  alarm; int /*<<< orphan*/  lock; TYPE_1__* device; int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  acpi_status ;
struct TYPE_2__ {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_BATTERY_ALARM_PRESENT ; 
 int /*<<< orphan*/  ACPI_DB_INFO ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int /*<<< orphan*/  acpi_battery_present (struct acpi_battery*) ; 
 int /*<<< orphan*/  acpi_execute_simple_method (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int acpi_battery_set_alarm(struct acpi_battery *battery)
{
	acpi_status status = 0;

	if (!acpi_battery_present(battery) ||
	    !test_bit(ACPI_BATTERY_ALARM_PRESENT, &battery->flags))
		return -ENODEV;

	mutex_lock(&battery->lock);
	status = acpi_execute_simple_method(battery->device->handle, "_BTP",
					    battery->alarm);
	mutex_unlock(&battery->lock);

	if (ACPI_FAILURE(status))
		return -ENODEV;

	ACPI_DEBUG_PRINT((ACPI_DB_INFO, "Alarm set to %d\n", battery->alarm));
	return 0;
}