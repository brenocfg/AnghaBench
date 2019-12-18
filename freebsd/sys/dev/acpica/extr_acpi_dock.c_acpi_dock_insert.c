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
struct acpi_dock_softc {scalar_t__ status; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  ACPI_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DOCK_CONNECT ; 
 int /*<<< orphan*/  ACPI_DOCK_LOCK ; 
 scalar_t__ ACPI_DOCK_STATUS_DOCKED ; 
 scalar_t__ ACPI_DOCK_STATUS_UNDOCKED ; 
 scalar_t__ ACPI_DOCK_STATUS_UNKNOWN ; 
 int /*<<< orphan*/  ACPI_SERIAL_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_UserNotify (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ acpi_dock_execute_dck (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_dock_execute_lck (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_dock_insert_children (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_get_handle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cold ; 
 struct acpi_dock_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dock ; 

__attribute__((used)) static void
acpi_dock_insert(device_t dev)
{
	struct acpi_dock_softc	*sc;
	ACPI_HANDLE		h;

	ACPI_SERIAL_ASSERT(dock);

	sc = device_get_softc(dev);
	h = acpi_get_handle(dev);

	if (sc->status == ACPI_DOCK_STATUS_UNDOCKED ||
	    sc->status == ACPI_DOCK_STATUS_UNKNOWN) {
		acpi_dock_execute_lck(dev, ACPI_DOCK_LOCK);
		if (acpi_dock_execute_dck(dev, ACPI_DOCK_CONNECT) != 0) {
			device_printf(dev, "_DCK failed\n");
			return;
		}

		if (!cold) {
			acpi_dock_insert_children(dev);

			acpi_UserNotify("Dock", h, 1);
		}

		sc->status = ACPI_DOCK_STATUS_DOCKED;
	}
}