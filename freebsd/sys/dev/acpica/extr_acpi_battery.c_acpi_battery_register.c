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
 int /*<<< orphan*/  ACPI_SERIAL_BEGIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_SERIAL_END (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_batteries_initted ; 
 int acpi_battery_init () ; 
 int /*<<< orphan*/  battery ; 

int
acpi_battery_register(device_t dev)
{
    int error;

    error = 0;
    ACPI_SERIAL_BEGIN(battery);
    if (!acpi_batteries_initted)
	error = acpi_battery_init();
    ACPI_SERIAL_END(battery);
    return (error);
}