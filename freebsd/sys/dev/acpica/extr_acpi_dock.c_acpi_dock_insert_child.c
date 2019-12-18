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
typedef  int /*<<< orphan*/ * device_t ;
typedef  int /*<<< orphan*/  UINT32 ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  int /*<<< orphan*/  ACPI_INIT_WALK_INFO ;
typedef  int /*<<< orphan*/  ACPI_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_TYPE_ANY ; 
 int /*<<< orphan*/  ACPI_VPRINT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AcpiNsInitOneDevice ; 
 int /*<<< orphan*/  AcpiNsWalkNamespace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiOsExecute (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSL_NOTIFY_HANDLER ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  acpi_device_get_parent_softc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_dock_attach_later ; 
 int /*<<< orphan*/  acpi_dock_is_ejd_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * acpi_get_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_get_handle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ACPI_STATUS
acpi_dock_insert_child(ACPI_HANDLE handle, UINT32 level, void *context,
    void **status)
{
	device_t	dock_dev, dev;
	ACPI_HANDLE	dock_handle;

	dock_dev = (device_t)context;
	dock_handle = acpi_get_handle(dock_dev);

	if (!acpi_dock_is_ejd_device(dock_handle, handle))
		goto out;

	ACPI_VPRINT(dock_dev, acpi_device_get_parent_softc(dock_dev),
		    "inserting device for %s\n", acpi_name(handle));

#if 0
	/*
	 * If the system boot up w/o Docking, the devices under the dock
	 * still un-initialized, also control methods such as _INI, _STA
	 * are not executed.
	 * Normal devices are initialized at booting by calling
	 * AcpiInitializeObjects(), however the devices under the dock
	 * need to be initialized here on the scheme of ACPICA.
	 */
	ACPI_INIT_WALK_INFO	Info;

	AcpiNsWalkNamespace(ACPI_TYPE_ANY, handle,
	    100, TRUE, AcpiNsInitOneDevice, NULL, &Info, NULL);
#endif

	dev = acpi_get_device(handle);
	if (dev == NULL) {
		device_printf(dock_dev, "error: %s has no associated device\n",
		    acpi_name(handle));
		goto out;
	}

	AcpiOsExecute(OSL_NOTIFY_HANDLER, acpi_dock_attach_later, dev);

out:
	return (AE_OK);
}