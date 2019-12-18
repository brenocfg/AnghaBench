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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  acpi_device_pwr_for_sleep (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  devclass_find (char*) ; 
 int /*<<< orphan*/  devclass_get_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
acpi_pcib_power_for_sleep(device_t pcib, device_t dev, int *pstate)
{
    device_t acpi_dev;

    acpi_dev = devclass_get_device(devclass_find("acpi"), 0);
    acpi_device_pwr_for_sleep(acpi_dev, dev, pstate);
    return (0);
}