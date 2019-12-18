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
struct list_head {int dummy; } ;
struct attribute_group {int dummy; } ;
struct acpi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  acpi_power_expose_list (struct acpi_device*,struct list_head*,struct attribute_group const*) ; 
 int /*<<< orphan*/  acpi_power_hide_list (struct acpi_device*,struct list_head*,struct attribute_group const*) ; 

__attribute__((used)) static void acpi_power_expose_hide(struct acpi_device *adev,
				   struct list_head *resources,
				   const struct attribute_group *attr_group,
				   bool expose)
{
	if (expose)
		acpi_power_expose_list(adev, resources, attr_group);
	else
		acpi_power_hide_list(adev, resources, attr_group);
}