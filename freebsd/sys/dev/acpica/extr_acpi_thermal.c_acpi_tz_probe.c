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
 scalar_t__ ACPI_TYPE_THERMAL ; 
 int ENXIO ; 
 int /*<<< orphan*/  acpi_disabled (char*) ; 
 scalar_t__ acpi_get_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
acpi_tz_probe(device_t dev)
{
    int		result;

    if (acpi_get_type(dev) == ACPI_TYPE_THERMAL && !acpi_disabled("thermal")) {
	device_set_desc(dev, "Thermal Zone");
	result = -10;
    } else
	result = ENXIO;
    return (result);
}