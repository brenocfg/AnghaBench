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
struct acpi_softc {int /*<<< orphan*/  acpi_sleep_disabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_LOCK_ASSERT (int /*<<< orphan*/ ) ; 
 int ACPI_MINIMUM_AWAKETIME ; 
 int /*<<< orphan*/  AcpiGbl_SystemAwakeAndRunning ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  acpi ; 
 int /*<<< orphan*/  acpi_sleep_timer ; 
 int /*<<< orphan*/  callout_schedule (int /*<<< orphan*/ *,int) ; 
 int hz ; 

__attribute__((used)) static void
acpi_sleep_enable(void *arg)
{
    struct acpi_softc	*sc = (struct acpi_softc *)arg;

    ACPI_LOCK_ASSERT(acpi);

    /* Reschedule if the system is not fully up and running. */
    if (!AcpiGbl_SystemAwakeAndRunning) {
	callout_schedule(&acpi_sleep_timer, hz * ACPI_MINIMUM_AWAKETIME);
	return;
    }

    sc->acpi_sleep_disabled = FALSE;
}