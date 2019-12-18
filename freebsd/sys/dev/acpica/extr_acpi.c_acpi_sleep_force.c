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
struct acpi_softc {int /*<<< orphan*/  acpi_dev; } ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiOsExecute (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct acpi_softc*) ; 
 int /*<<< orphan*/  OSL_NOTIFY_HANDLER ; 
 int /*<<< orphan*/  acpi_sleep_force_task ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
acpi_sleep_force(void *arg)
{
    struct acpi_softc *sc = (struct acpi_softc *)arg;

    device_printf(sc->acpi_dev,
	"suspend request timed out, forcing sleep now\n");
    /*
     * XXX Suspending from callout causes freezes in DEVICE_SUSPEND().
     * Suspend from acpi_task thread instead.
     */
    if (ACPI_FAILURE(AcpiOsExecute(OSL_NOTIFY_HANDLER,
	acpi_sleep_force_task, sc)))
	device_printf(sc->acpi_dev, "AcpiOsExecute() for sleeping failed\n");
}