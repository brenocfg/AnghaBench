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
typedef  int uint32_t ;
struct acpi_smbat_softc {int sb_base_addr; int /*<<< orphan*/  bst_lastupdated; int /*<<< orphan*/  bif_lastupdated; int /*<<< orphan*/ * ec_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int ENXIO ; 
 int /*<<< orphan*/  acpi_GetInteger (int /*<<< orphan*/ ,char*,int*) ; 
 scalar_t__ acpi_battery_register (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_get_handle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devclass_find (char*) ; 
 int /*<<< orphan*/ * devclass_get_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct acpi_smbat_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  timespecclear (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
acpi_smbat_attach(device_t dev)
{
	struct acpi_smbat_softc *sc;
	uint32_t base;

	sc = device_get_softc(dev);
	if (ACPI_FAILURE(acpi_GetInteger(acpi_get_handle(dev), "_EC", &base))) {
		device_printf(dev, "cannot get EC base address\n");
		return (ENXIO);
	}
	sc->sb_base_addr = (base >> 8) & 0xff;

	/* XXX Only works with one EC, but nearly all systems only have one. */
	sc->ec_dev = devclass_get_device(devclass_find("acpi_ec"), 0);
	if (sc->ec_dev == NULL) {
		device_printf(dev, "cannot find EC device\n");
		return (ENXIO);
	}

	timespecclear(&sc->bif_lastupdated);
	timespecclear(&sc->bst_lastupdated);

	if (acpi_battery_register(dev) != 0) {
		device_printf(dev, "cannot register battery\n");
		return (ENXIO);
	}
	return (0);
}