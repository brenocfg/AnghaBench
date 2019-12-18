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
struct acpi_dock_softc {void* _uid; void* _bdn; void* _sta; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  ACPI_HANDLE ;

/* Variables and functions */
 void* ACPI_DOCK_STATUS_UNKNOWN ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_VPRINT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,void*,void*,void*) ; 
 int /*<<< orphan*/  acpi_GetInteger (int /*<<< orphan*/ ,char*,void**) ; 
 int /*<<< orphan*/  acpi_device_get_parent_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_get_handle (int /*<<< orphan*/ ) ; 
 struct acpi_dock_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
acpi_dock_get_info(device_t dev)
{
	struct acpi_dock_softc *sc;
	ACPI_HANDLE	h;

	sc = device_get_softc(dev);
	h = acpi_get_handle(dev);

	if (ACPI_FAILURE(acpi_GetInteger(h, "_STA", &sc->_sta)))
		sc->_sta = ACPI_DOCK_STATUS_UNKNOWN;
	if (ACPI_FAILURE(acpi_GetInteger(h, "_BDN", &sc->_bdn)))
		sc->_bdn = ACPI_DOCK_STATUS_UNKNOWN;
	if (ACPI_FAILURE(acpi_GetInteger(h, "_UID", &sc->_uid)))
		sc->_uid = ACPI_DOCK_STATUS_UNKNOWN;
	ACPI_VPRINT(dev, acpi_device_get_parent_softc(dev),
		    "_STA: %04x, _BDN: %04x, _UID: %04x\n", sc->_sta,
		    sc->_bdn, sc->_uid);
}