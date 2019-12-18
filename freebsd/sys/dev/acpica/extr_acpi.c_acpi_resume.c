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
 int /*<<< orphan*/  ACPI_STATE_D0 ; 
 int /*<<< orphan*/  GIANT_REQUIRED ; 
 int /*<<< orphan*/  acpi_set_power_children (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bus_generic_resume (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
acpi_resume(device_t dev)
{

    GIANT_REQUIRED;

    acpi_set_power_children(dev, ACPI_STATE_D0);

    return (bus_generic_resume(dev));
}