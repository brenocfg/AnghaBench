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
 int /*<<< orphan*/  ACPI_STATE_S5 ; 
 int /*<<< orphan*/  GIANT_REQUIRED ; 
 int /*<<< orphan*/  acpi_wake_prep_walk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_generic_shutdown (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
acpi_shutdown(device_t dev)
{

    GIANT_REQUIRED;

    /* Allow children to shutdown first. */
    bus_generic_shutdown(dev);

    /*
     * Enable any GPEs that are able to power-on the system (i.e., RTC).
     * Also, disable any that are not valid for this state (most).
     */
    acpi_wake_prep_walk(ACPI_STATE_S5);

    return (0);
}