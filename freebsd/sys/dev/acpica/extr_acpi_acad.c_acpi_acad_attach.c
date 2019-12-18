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
struct acpi_softc {int /*<<< orphan*/  acpi_sysctl_tree; int /*<<< orphan*/  acpi_sysctl_ctx; } ;
struct acpi_acad_softc {int status; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  ACPI_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPIIO_ACAD_GET_STATUS ; 
 int /*<<< orphan*/  ACPI_ALL_NOTIFY ; 
 int /*<<< orphan*/  AcpiInstallNotifyHandler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiOsExecute (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int CTLFLAG_RD ; 
 int CTLTYPE_INT ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  OSL_NOTIFY_HANDLER ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_acad_init_acline ; 
 int /*<<< orphan*/  acpi_acad_ioctl ; 
 int /*<<< orphan*/  acpi_acad_notify_handler ; 
 int /*<<< orphan*/  acpi_acad_sysctl ; 
 struct acpi_softc* acpi_device_get_parent_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_get_handle (int /*<<< orphan*/ ) ; 
 int acpi_register_ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct acpi_acad_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ device_get_unit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
acpi_acad_attach(device_t dev)
{
    struct acpi_acad_softc *sc;
    struct acpi_softc	   *acpi_sc;
    ACPI_HANDLE	handle;
    int		error;

    sc = device_get_softc(dev);
    handle = acpi_get_handle(dev);

    error = acpi_register_ioctl(ACPIIO_ACAD_GET_STATUS, acpi_acad_ioctl, dev);
    if (error != 0)
	return (error);

    if (device_get_unit(dev) == 0) {
	acpi_sc = acpi_device_get_parent_softc(dev);
	SYSCTL_ADD_PROC(&acpi_sc->acpi_sysctl_ctx,
			SYSCTL_CHILDREN(acpi_sc->acpi_sysctl_tree),
			OID_AUTO, "acline", CTLTYPE_INT | CTLFLAG_RD,
			&sc->status, 0, acpi_acad_sysctl, "I", "");
    }

    /* Get initial status after whole system is up. */
    sc->status = -1;

    /*
     * Install both system and device notify handlers since the Casio
     * FIVA needs them.
     */
    AcpiInstallNotifyHandler(handle, ACPI_ALL_NOTIFY,
			     acpi_acad_notify_handler, dev);
    AcpiOsExecute(OSL_NOTIFY_HANDLER, acpi_acad_init_acline, dev);

    return (0);
}