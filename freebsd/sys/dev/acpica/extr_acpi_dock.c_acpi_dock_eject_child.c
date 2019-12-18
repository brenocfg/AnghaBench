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
typedef  int /*<<< orphan*/  ACPI_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_VPRINT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  Giant ; 
 int /*<<< orphan*/  acpi_SetInteger (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_device_get_parent_softc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_dock_is_ejd_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * acpi_get_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_get_handle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_detach (int /*<<< orphan*/ *) ; 
 scalar_t__ device_is_attached (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ACPI_STATUS
acpi_dock_eject_child(ACPI_HANDLE handle, UINT32 level, void *context,
    void **status)
{
	device_t	dock_dev, dev;
	ACPI_HANDLE	dock_handle;

	dock_dev = *(device_t *)context;
	dock_handle = acpi_get_handle(dock_dev);

	if (!acpi_dock_is_ejd_device(dock_handle, handle))
		goto out;

	ACPI_VPRINT(dock_dev, acpi_device_get_parent_softc(dock_dev),
	    "ejecting device for %s\n", acpi_name(handle));

	dev = acpi_get_device(handle);
	if (dev != NULL && device_is_attached(dev)) {
		mtx_lock(&Giant);
		device_detach(dev);
		mtx_unlock(&Giant);
	}

	acpi_SetInteger(handle, "_EJ0", 0);
out:
	return (AE_OK);
}