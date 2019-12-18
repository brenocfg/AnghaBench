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
struct acpi_dock_softc {scalar_t__ status; scalar_t__ _sta; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  ACPI_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DOCK_ISOLATE ; 
 scalar_t__ ACPI_DOCK_STATUS_DOCKED ; 
 scalar_t__ ACPI_DOCK_STATUS_UNDOCKED ; 
 scalar_t__ ACPI_DOCK_STATUS_UNKNOWN ; 
 int /*<<< orphan*/  ACPI_DOCK_UNLOCK ; 
 int /*<<< orphan*/  ACPI_SERIAL_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_UserNotify (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_dock_eject_children (int /*<<< orphan*/ ) ; 
 scalar_t__ acpi_dock_execute_dck (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ acpi_dock_execute_ejx (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_dock_execute_lck (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_dock_get_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_get_handle (int /*<<< orphan*/ ) ; 
 struct acpi_dock_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dock ; 

__attribute__((used)) static void
acpi_dock_removal(device_t dev)
{
	struct acpi_dock_softc *sc;
	ACPI_HANDLE		h;

	ACPI_SERIAL_ASSERT(dock);

	sc = device_get_softc(dev);
	h = acpi_get_handle(dev);

	if (sc->status == ACPI_DOCK_STATUS_DOCKED ||
	    sc->status == ACPI_DOCK_STATUS_UNKNOWN) {
		acpi_dock_eject_children(dev);
		if (acpi_dock_execute_dck(dev, ACPI_DOCK_ISOLATE) != 0)
			return;

		acpi_dock_execute_lck(dev, ACPI_DOCK_UNLOCK);

		if (acpi_dock_execute_ejx(dev, 1, 0) != 0) {
			device_printf(dev, "_EJ0 failed\n");
			return;
		}

		acpi_UserNotify("Dock", h, 0);

		sc->status = ACPI_DOCK_STATUS_UNDOCKED;
	}

	acpi_dock_get_info(dev);
	if (sc->_sta != 0)
		device_printf(dev, "mechanical failure (%#x).\n", sc->_sta);
}