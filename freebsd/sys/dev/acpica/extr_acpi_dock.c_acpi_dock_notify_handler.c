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
typedef  scalar_t__ device_t ;
typedef  int /*<<< orphan*/  UINT32 ;
typedef  int /*<<< orphan*/  ACPI_HANDLE ;

/* Variables and functions */
#define  ACPI_NOTIFY_BUS_CHECK 130 
#define  ACPI_NOTIFY_DEVICE_CHECK 129 
#define  ACPI_NOTIFY_EJECT_REQUEST 128 
 int /*<<< orphan*/  ACPI_SERIAL_BEGIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_SERIAL_END (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_VPRINT (scalar_t__,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_device_get_parent_softc (scalar_t__) ; 
 int /*<<< orphan*/  acpi_dock_device_check (scalar_t__) ; 
 int /*<<< orphan*/  acpi_dock_removal (scalar_t__) ; 
 int /*<<< orphan*/  device_printf (scalar_t__,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dock ; 

__attribute__((used)) static void
acpi_dock_notify_handler(ACPI_HANDLE h, UINT32 notify, void *context)
{
	device_t	dev;

	dev = (device_t) context;
	ACPI_VPRINT(dev, acpi_device_get_parent_softc(dev),
		    "got notification %#x\n", notify);

	ACPI_SERIAL_BEGIN(dock);
	switch (notify) {
	case ACPI_NOTIFY_BUS_CHECK:
	case ACPI_NOTIFY_DEVICE_CHECK:
		acpi_dock_device_check(dev);
		break;
	case ACPI_NOTIFY_EJECT_REQUEST:
		acpi_dock_removal(dev);
		break;
	default:
		device_printf(dev, "unknown notify %#x\n", notify);
		break;
	}
	ACPI_SERIAL_END(dock);
}