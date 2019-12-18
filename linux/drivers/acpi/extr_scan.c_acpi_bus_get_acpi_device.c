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
struct acpi_device {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  acpi_get_device_data (int /*<<< orphan*/ ,struct acpi_device**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_acpi_device ; 

struct acpi_device *acpi_bus_get_acpi_device(acpi_handle handle)
{
	struct acpi_device *adev = NULL;

	acpi_get_device_data(handle, &adev, get_acpi_device);
	return adev;
}