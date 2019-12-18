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
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  ACPI_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ALL_NOTIFY ; 
 int /*<<< orphan*/  ACPI_SERIAL_BEGIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_SERIAL_END (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiRemoveNotifyHandler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_battery_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_cmbat_notify_handler ; 
 int /*<<< orphan*/  acpi_get_handle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmbat ; 
 int /*<<< orphan*/  device_set_softc (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
acpi_cmbat_detach(device_t dev)
{
    ACPI_HANDLE	handle;

    handle = acpi_get_handle(dev);
    AcpiRemoveNotifyHandler(handle, ACPI_ALL_NOTIFY, acpi_cmbat_notify_handler);
    acpi_battery_remove(dev);

    /*
     * Force any pending notification handler calls to complete by
     * requesting cmbat serialisation while freeing and clearing the
     * softc pointer:
     */
    ACPI_SERIAL_BEGIN(cmbat);
    device_set_softc(dev, NULL);
    ACPI_SERIAL_END(cmbat);

    return (0);
}