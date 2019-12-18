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
typedef  int UINT32 ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  int /*<<< orphan*/  ACPI_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FAILURE (int /*<<< orphan*/ ) ; 
#define  ACPI_NOTIFY_DEVICE_CHECK 129 
#define  ACPI_NOTIFY_EJECT_REQUEST 128 
 int AcpiFormatException (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUS_RESCAN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Giant ; 
 int /*<<< orphan*/  acpi_SetInteger (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/ * acpi_get_device (int /*<<< orphan*/ ) ; 
 int acpi_name (int /*<<< orphan*/ ) ; 
 int device_detach (int /*<<< orphan*/ *) ; 
 int device_get_nameunit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ *,char*,int,...) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
acpi_pci_device_notify_handler(ACPI_HANDLE h, UINT32 notify, void *context)
{
	device_t child, dev;
	ACPI_STATUS status;
	int error;

	dev = context;

	switch (notify) {
	case ACPI_NOTIFY_DEVICE_CHECK:
		mtx_lock(&Giant);
		BUS_RESCAN(dev);
		mtx_unlock(&Giant);
		break;
	case ACPI_NOTIFY_EJECT_REQUEST:
		child = acpi_get_device(h);
		if (child == NULL) {
			device_printf(dev, "no device to eject for %s\n",
			    acpi_name(h));
			return;
		}
		mtx_lock(&Giant);
		error = device_detach(child);
		if (error) {
			mtx_unlock(&Giant);
			device_printf(dev, "failed to detach %s: %d\n",
			    device_get_nameunit(child), error);
			return;
		}
		status = acpi_SetInteger(h, "_EJ0", 1);
		if (ACPI_FAILURE(status)) {
			mtx_unlock(&Giant);
			device_printf(dev, "failed to eject %s: %s\n",
			    acpi_name(h), AcpiFormatException(status));
			return;
		}
		BUS_RESCAN(dev);
		mtx_unlock(&Giant);
		break;
	default:
		device_printf(dev, "unknown notify %#x for %s\n", notify,
		    acpi_name(h));
		break;
	}
}