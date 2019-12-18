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
struct acpi_softc {int /*<<< orphan*/  acpi_next_sstate; int /*<<< orphan*/  acpi_dev; } ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_EnterSleepState (struct acpi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
acpi_sleep_force_task(void *context)
{
    struct acpi_softc *sc = (struct acpi_softc *)context;

    if (ACPI_FAILURE(acpi_EnterSleepState(sc, sc->acpi_next_sstate)))
	device_printf(sc->acpi_dev, "force sleep state S%d failed\n",
	    sc->acpi_next_sstate);
}