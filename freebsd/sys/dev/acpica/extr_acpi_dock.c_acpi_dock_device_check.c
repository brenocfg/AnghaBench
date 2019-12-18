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
struct acpi_dock_softc {scalar_t__ _sta; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ ACPI_DEVICE_PRESENT (scalar_t__) ; 
 scalar_t__ ACPI_DOCK_STATUS_UNKNOWN ; 
 int /*<<< orphan*/  ACPI_SERIAL_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_dock_get_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_dock_insert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_dock_removal (int /*<<< orphan*/ ) ; 
 struct acpi_dock_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dock ; 

__attribute__((used)) static void
acpi_dock_device_check(device_t dev)
{
	struct acpi_dock_softc *sc;

	ACPI_SERIAL_ASSERT(dock);

	sc = device_get_softc(dev);
	acpi_dock_get_info(dev);

	/*
	 * If the _STA method indicates 'present' and 'functioning', the
	 * system is docked.  If _STA does not exist for this device, it
	 * is always present.
	 */
	if (sc->_sta == ACPI_DOCK_STATUS_UNKNOWN ||
	    ACPI_DEVICE_PRESENT(sc->_sta))
		acpi_dock_insert(dev);
	else if (sc->_sta == 0)
		acpi_dock_removal(dev);
}