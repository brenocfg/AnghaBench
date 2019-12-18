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
struct acpi_cmbat_softc {int /*<<< orphan*/  bif; int /*<<< orphan*/  bst; int /*<<< orphan*/  bst_lastupdated; } ;
typedef  scalar_t__ device_t ;

/* Variables and functions */
 int ACPI_CMBAT_RETRY_MAX ; 
 int /*<<< orphan*/  ACPI_SERIAL_BEGIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_SERIAL_END (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_VPRINT (scalar_t__,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  AcpiOsSleep (int) ; 
 int /*<<< orphan*/  acpi_BatteryIsPresent (scalar_t__) ; 
 scalar_t__ acpi_battery_bif_valid (int /*<<< orphan*/ *) ; 
 scalar_t__ acpi_battery_bst_valid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_cmbat_get_bif (scalar_t__) ; 
 int /*<<< orphan*/  acpi_cmbat_get_bst (scalar_t__) ; 
 int /*<<< orphan*/  acpi_device_get_parent_softc (scalar_t__) ; 
 int /*<<< orphan*/  cmbat ; 
 struct acpi_cmbat_softc* device_get_softc (scalar_t__) ; 
 int /*<<< orphan*/  device_is_attached (scalar_t__) ; 
 int /*<<< orphan*/  timespecclear (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
acpi_cmbat_init_battery(void *arg)
{
    struct acpi_cmbat_softc *sc;
    int		retry, valid;
    device_t	dev;

    dev = (device_t)arg;
    ACPI_VPRINT(dev, acpi_device_get_parent_softc(dev),
		"battery initialization start\n");

    /*
     * Try repeatedly to get valid data from the battery.  Since the
     * embedded controller isn't always ready just after boot, we may have
     * to wait a while.
     */
    for (retry = 0; retry < ACPI_CMBAT_RETRY_MAX; retry++, AcpiOsSleep(10000)) {
	/*
	 * Batteries on DOCK can be ejected w/ DOCK during retrying.
	 *
	 * If there is a valid softc pointer the device may be in
	 * attaching, attached or detaching state. If the state is
	 * different from attached retry getting the device state
	 * until it becomes stable. This solves a race if the ACPI
	 * notification handler is called during attach, because
	 * device_is_attached() doesn't return non-zero until after
	 * the attach code has been executed.
	 */
	ACPI_SERIAL_BEGIN(cmbat);
	sc = device_get_softc(dev);
	if (sc == NULL) {
	    ACPI_SERIAL_END(cmbat);
	    return;
	}

	if (!acpi_BatteryIsPresent(dev) || !device_is_attached(dev)) {
	    ACPI_SERIAL_END(cmbat);
	    continue;
	}

	/*
	 * Only query the battery if this is the first try or the specific
	 * type of info is still invalid.
	 */
	if (retry == 0 || !acpi_battery_bst_valid(&sc->bst)) {
	    timespecclear(&sc->bst_lastupdated);
	    acpi_cmbat_get_bst(dev);
	}
	if (retry == 0 || !acpi_battery_bif_valid(&sc->bif))
	    acpi_cmbat_get_bif(dev);

	valid = acpi_battery_bst_valid(&sc->bst) &&
	    acpi_battery_bif_valid(&sc->bif);
	ACPI_SERIAL_END(cmbat);

	if (valid)
	    break;
    }

    if (retry == ACPI_CMBAT_RETRY_MAX) {
	ACPI_VPRINT(dev, acpi_device_get_parent_softc(dev),
		    "battery initialization failed, giving up\n");
    } else {
	ACPI_VPRINT(dev, acpi_device_get_parent_softc(dev),
		    "battery initialization done, tried %d times\n", retry + 1);
    }
}