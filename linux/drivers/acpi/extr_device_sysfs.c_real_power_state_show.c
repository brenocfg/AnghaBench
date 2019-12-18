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
struct acpi_device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int acpi_device_get_power (struct acpi_device*,int*) ; 
 char* acpi_power_state_string (int) ; 
 int sprintf (char*,char*,char*) ; 
 struct acpi_device* to_acpi_device (struct device*) ; 

__attribute__((used)) static ssize_t real_power_state_show(struct device *dev,
				     struct device_attribute *attr, char *buf)
{
	struct acpi_device *adev = to_acpi_device(dev);
	int state;
	int ret;

	ret = acpi_device_get_power(adev, &state);
	if (ret)
		return ret;

	return sprintf(buf, "%s\n", acpi_power_state_string(state));
}