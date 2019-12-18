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
 int /*<<< orphan*/  ACPI_STATE_D0 ; 
 int /*<<< orphan*/  ACPI_STATE_D3_COLD ; 
 int EINVAL ; 
 int acpi_device_set_power (struct acpi_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fan_set_state(struct acpi_device *device, unsigned long state)
{
	if (state != 0 && state != 1)
		return -EINVAL;

	return acpi_device_set_power(device,
				     state ? ACPI_STATE_D0 : ACPI_STATE_D3_COLD);
}