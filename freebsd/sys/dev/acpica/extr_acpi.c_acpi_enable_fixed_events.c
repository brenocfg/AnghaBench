#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct acpi_softc {int /*<<< orphan*/  acpi_dev; } ;
struct TYPE_2__ {int Flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_EVENT_POWER_BUTTON ; 
 int /*<<< orphan*/  ACPI_EVENT_SLEEP_BUTTON ; 
 int ACPI_FADT_POWER_BUTTON ; 
 int ACPI_FADT_SLEEP_BUTTON ; 
 int /*<<< orphan*/  AcpiClearEvent (int /*<<< orphan*/ ) ; 
 TYPE_1__ AcpiGbl_FADT ; 
 int /*<<< orphan*/  AcpiInstallFixedEventHandler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct acpi_softc*) ; 
 int /*<<< orphan*/  acpi_event_power_button_sleep ; 
 int /*<<< orphan*/  acpi_event_sleep_button_sleep ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
acpi_enable_fixed_events(struct acpi_softc *sc)
{
    static int	first_time = 1;

    /* Enable and clear fixed events and install handlers. */
    if ((AcpiGbl_FADT.Flags & ACPI_FADT_POWER_BUTTON) == 0) {
	AcpiClearEvent(ACPI_EVENT_POWER_BUTTON);
	AcpiInstallFixedEventHandler(ACPI_EVENT_POWER_BUTTON,
				     acpi_event_power_button_sleep, sc);
	if (first_time)
	    device_printf(sc->acpi_dev, "Power Button (fixed)\n");
    }
    if ((AcpiGbl_FADT.Flags & ACPI_FADT_SLEEP_BUTTON) == 0) {
	AcpiClearEvent(ACPI_EVENT_SLEEP_BUTTON);
	AcpiInstallFixedEventHandler(ACPI_EVENT_SLEEP_BUTTON,
				     acpi_event_sleep_button_sleep, sc);
	if (first_time)
	    device_printf(sc->acpi_dev, "Sleep Button (fixed)\n");
    }

    first_time = 0;
}