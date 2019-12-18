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
struct acpi_dock_softc {int /*<<< orphan*/  sysctl_tree; int /*<<< orphan*/  sysctl_ctx; int /*<<< orphan*/  _uid; int /*<<< orphan*/  _bdn; int /*<<< orphan*/  _sta; int /*<<< orphan*/  status; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/ * ACPI_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ALL_NOTIFY ; 
 int /*<<< orphan*/  ACPI_DOCK_STATUS_UNKNOWN ; 
 int /*<<< orphan*/  ACPI_SERIAL_BEGIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_SERIAL_END (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiEvaluateObject (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiInstallNotifyHandler (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CTLFLAG_RD ; 
 int CTLFLAG_RW ; 
 int CTLTYPE_INT ; 
 int ENXIO ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_INT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_dock_device_check (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_dock_notify_handler ; 
 int /*<<< orphan*/  acpi_dock_status_sysctl ; 
 int /*<<< orphan*/ * acpi_get_handle (int /*<<< orphan*/ ) ; 
 struct acpi_dock_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dock ; 

__attribute__((used)) static int
acpi_dock_attach(device_t dev)
{
	struct acpi_dock_softc *sc;
	ACPI_HANDLE	h;

	sc = device_get_softc(dev);
	h = acpi_get_handle(dev);
	if (sc == NULL || h == NULL)
		return (ENXIO);

	sc->status = ACPI_DOCK_STATUS_UNKNOWN;

	AcpiEvaluateObject(h, "_INI", NULL, NULL);

	ACPI_SERIAL_BEGIN(dock);

	acpi_dock_device_check(dev);

	/* Get the sysctl tree */
	sc->sysctl_ctx = device_get_sysctl_ctx(dev);
	sc->sysctl_tree = device_get_sysctl_tree(dev);

	SYSCTL_ADD_INT(sc->sysctl_ctx,
		SYSCTL_CHILDREN(sc->sysctl_tree),
		OID_AUTO, "_sta", CTLFLAG_RD,
		&sc->_sta, 0, "Dock _STA");
	SYSCTL_ADD_INT(sc->sysctl_ctx,
		SYSCTL_CHILDREN(sc->sysctl_tree),
		OID_AUTO, "_bdn", CTLFLAG_RD,
		&sc->_bdn, 0, "Dock _BDN");
	SYSCTL_ADD_INT(sc->sysctl_ctx,
		SYSCTL_CHILDREN(sc->sysctl_tree),
		OID_AUTO, "_uid", CTLFLAG_RD,
		&sc->_uid, 0, "Dock _UID");
	SYSCTL_ADD_PROC(sc->sysctl_ctx,
		SYSCTL_CHILDREN(sc->sysctl_tree),
		OID_AUTO, "status",
		CTLTYPE_INT|CTLFLAG_RW, dev, 0,
		acpi_dock_status_sysctl, "I",
		"Dock/Undock operation");

	ACPI_SERIAL_END(dock);

	AcpiInstallNotifyHandler(h, ACPI_ALL_NOTIFY,
				 acpi_dock_notify_handler, dev);

	return (0);
}