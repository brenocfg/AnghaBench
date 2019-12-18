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
struct acpi_cmbat_softc {int /*<<< orphan*/  bst_lastupdated; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  ACPI_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ALL_NOTIFY ; 
 int /*<<< orphan*/  AcpiInstallNotifyHandler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiOsExecute (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSL_NOTIFY_HANDLER ; 
 int acpi_battery_register (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_cmbat_init_battery ; 
 int /*<<< orphan*/  acpi_cmbat_notify_handler ; 
 int /*<<< orphan*/  acpi_get_handle (int /*<<< orphan*/ ) ; 
 struct acpi_cmbat_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  timespecclear (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
acpi_cmbat_attach(device_t dev)
{
    int		error;
    ACPI_HANDLE	handle;
    struct acpi_cmbat_softc *sc;

    sc = device_get_softc(dev);
    handle = acpi_get_handle(dev);
    sc->dev = dev;

    timespecclear(&sc->bst_lastupdated);

    error = acpi_battery_register(dev);
    if (error != 0) {
    	device_printf(dev, "registering battery failed\n");
	return (error);
    }

    /*
     * Install a system notify handler in addition to the device notify.
     * Toshiba notebook uses this alternate notify for its battery.
     */
    AcpiInstallNotifyHandler(handle, ACPI_ALL_NOTIFY,
	acpi_cmbat_notify_handler, dev);

    AcpiOsExecute(OSL_NOTIFY_HANDLER, acpi_cmbat_init_battery, dev);

    return (0);
}