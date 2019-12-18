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
struct acpi_softc {int /*<<< orphan*/  acpi_dev; scalar_t__ acpi_do_disable; scalar_t__ acpi_handle_reboot; } ;
typedef  int /*<<< orphan*/  register_t ;
typedef  scalar_t__ ACPI_STATUS ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (scalar_t__) ; 
 int /*<<< orphan*/  ACPI_STATE_S5 ; 
 scalar_t__ ACPI_SUCCESS (scalar_t__) ; 
 scalar_t__ AE_NOT_EXIST ; 
 scalar_t__ AcpiEnterSleepState (int /*<<< orphan*/ ) ; 
 scalar_t__ AcpiEnterSleepStatePrep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiFormatException (scalar_t__) ; 
 scalar_t__ AcpiReset () ; 
 int /*<<< orphan*/  AcpiTerminate () ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int RB_HALT ; 
 int RB_POWEROFF ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  intr_disable () ; 
 int /*<<< orphan*/  intr_restore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * panicstr ; 

__attribute__((used)) static void
acpi_shutdown_final(void *arg, int howto)
{
    struct acpi_softc *sc = (struct acpi_softc *)arg;
    register_t intr;
    ACPI_STATUS status;

    /*
     * XXX Shutdown code should only run on the BSP (cpuid 0).
     * Some chipsets do not power off the system correctly if called from
     * an AP.
     */
    if ((howto & RB_POWEROFF) != 0) {
	status = AcpiEnterSleepStatePrep(ACPI_STATE_S5);
	if (ACPI_FAILURE(status)) {
	    device_printf(sc->acpi_dev, "AcpiEnterSleepStatePrep failed - %s\n",
		AcpiFormatException(status));
	    return;
	}
	device_printf(sc->acpi_dev, "Powering system off\n");
	intr = intr_disable();
	status = AcpiEnterSleepState(ACPI_STATE_S5);
	if (ACPI_FAILURE(status)) {
	    intr_restore(intr);
	    device_printf(sc->acpi_dev, "power-off failed - %s\n",
		AcpiFormatException(status));
	} else {
	    DELAY(1000000);
	    intr_restore(intr);
	    device_printf(sc->acpi_dev, "power-off failed - timeout\n");
	}
    } else if ((howto & RB_HALT) == 0 && sc->acpi_handle_reboot) {
	/* Reboot using the reset register. */
	status = AcpiReset();
	if (ACPI_SUCCESS(status)) {
	    DELAY(1000000);
	    device_printf(sc->acpi_dev, "reset failed - timeout\n");
	} else if (status != AE_NOT_EXIST)
	    device_printf(sc->acpi_dev, "reset failed - %s\n",
		AcpiFormatException(status));
    } else if (sc->acpi_do_disable && panicstr == NULL) {
	/*
	 * Only disable ACPI if the user requested.  On some systems, writing
	 * the disable value to SMI_CMD hangs the system.
	 */
	device_printf(sc->acpi_dev, "Shutting down\n");
	AcpiTerminate();
    }
}