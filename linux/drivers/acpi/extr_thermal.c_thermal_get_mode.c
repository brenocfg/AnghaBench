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
struct thermal_zone_device {struct acpi_thermal* devdata; } ;
struct acpi_thermal {scalar_t__ tz_enabled; } ;
typedef  enum thermal_device_mode { ____Placeholder_thermal_device_mode } thermal_device_mode ;

/* Variables and functions */
 int EINVAL ; 
 int THERMAL_DEVICE_DISABLED ; 
 int THERMAL_DEVICE_ENABLED ; 

__attribute__((used)) static int thermal_get_mode(struct thermal_zone_device *thermal,
				enum thermal_device_mode *mode)
{
	struct acpi_thermal *tz = thermal->devdata;

	if (!tz)
		return -EINVAL;

	*mode = tz->tz_enabled ? THERMAL_DEVICE_ENABLED :
		THERMAL_DEVICE_DISABLED;

	return 0;
}