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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  state; } ;
struct acpi_device {TYPE_1__ power; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 char* acpi_power_state_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 struct acpi_device* to_acpi_device (struct device*) ; 

__attribute__((used)) static ssize_t power_state_show(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct acpi_device *adev = to_acpi_device(dev);

	return sprintf(buf, "%s\n", acpi_power_state_string(adev->power.state));
}