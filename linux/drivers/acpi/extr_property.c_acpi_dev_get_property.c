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
typedef  union acpi_object {int dummy; } acpi_object ;
struct acpi_device {int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  acpi_object_type ;

/* Variables and functions */
 int EINVAL ; 
 int acpi_data_get_property (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,union acpi_object const**) ; 

int acpi_dev_get_property(const struct acpi_device *adev, const char *name,
			  acpi_object_type type, const union acpi_object **obj)
{
	return adev ? acpi_data_get_property(&adev->data, name, type, obj) : -EINVAL;
}