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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct acpi_battery {unsigned long alarm_capacity; scalar_t__ present; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int acpi_battery_scale (struct acpi_battery*) ; 
 int /*<<< orphan*/  acpi_battery_set_alarm (struct acpi_battery*) ; 
 int /*<<< orphan*/  dev_get_drvdata (struct device*) ; 
 int sscanf (char const*,char*,unsigned long*) ; 
 struct acpi_battery* to_acpi_battery (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t acpi_battery_alarm_store(struct device *dev,
					struct device_attribute *attr,
					const char *buf, size_t count)
{
	unsigned long x;
	struct acpi_battery *battery = to_acpi_battery(dev_get_drvdata(dev));
	if (sscanf(buf, "%lu\n", &x) == 1)
		battery->alarm_capacity = x /
			(1000 * acpi_battery_scale(battery));
	if (battery->present)
		acpi_battery_set_alarm(battery);
	return count;
}