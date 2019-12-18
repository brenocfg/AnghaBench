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

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FIXED_HARDWARE_EVENT ; 
 int /*<<< orphan*/  acpi_device_notify (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct acpi_device*) ; 

__attribute__((used)) static void acpi_device_notify_fixed(void *data)
{
	struct acpi_device *device = data;

	/* Fixed hardware devices have no handles */
	acpi_device_notify(NULL, ACPI_FIXED_HARDWARE_EVENT, device);
}