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
typedef  int u32 ;
struct dock_station {int flags; int /*<<< orphan*/  handle; } ;
struct acpi_device {int /*<<< orphan*/  handle; } ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
#define  ACPI_NOTIFY_BUS_CHECK 130 
#define  ACPI_NOTIFY_DEVICE_CHECK 129 
#define  ACPI_NOTIFY_EJECT_REQUEST 128 
 int /*<<< orphan*/  DOCK_EVENT ; 
 int DOCK_IS_ATA ; 
 int DOCK_IS_DOCK ; 
 int ENODEV ; 
 int /*<<< orphan*/  UNDOCK_EVENT ; 
 int /*<<< orphan*/  acpi_device_enumerated (struct acpi_device*) ; 
 int /*<<< orphan*/  acpi_evaluate_lck (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  acpi_handle_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  acpi_update_all_gpes () ; 
 int /*<<< orphan*/  begin_dock (struct dock_station*) ; 
 int /*<<< orphan*/  begin_undock (struct dock_station*) ; 
 int /*<<< orphan*/  complete_dock (struct dock_station*) ; 
 int /*<<< orphan*/  dock (struct dock_station*) ; 
 int /*<<< orphan*/  dock_event (struct dock_station*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dock_in_progress (struct dock_station*) ; 
 int /*<<< orphan*/  dock_present (struct dock_station*) ; 
 struct dock_station* find_dock_station (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_eject_request (struct dock_station*,int) ; 
 int /*<<< orphan*/  hotplug_dock_devices (struct dock_station*,int) ; 
 int /*<<< orphan*/  immediate_undock ; 

int dock_notify(struct acpi_device *adev, u32 event)
{
	acpi_handle handle = adev->handle;
	struct dock_station *ds = find_dock_station(handle);
	int surprise_removal = 0;

	if (!ds)
		return -ENODEV;

	/*
	 * According to acpi spec 3.0a, if a DEVICE_CHECK notification
	 * is sent and _DCK is present, it is assumed to mean an undock
	 * request.
	 */
	if ((ds->flags & DOCK_IS_DOCK) && event == ACPI_NOTIFY_DEVICE_CHECK)
		event = ACPI_NOTIFY_EJECT_REQUEST;

	/*
	 * dock station: BUS_CHECK - docked or surprise removal
	 *		 DEVICE_CHECK - undocked
	 * other device: BUS_CHECK/DEVICE_CHECK - added or surprise removal
	 *
	 * To simplify event handling, dock dependent device handler always
	 * get ACPI_NOTIFY_BUS_CHECK/ACPI_NOTIFY_DEVICE_CHECK for add and
	 * ACPI_NOTIFY_EJECT_REQUEST for removal
	 */
	switch (event) {
	case ACPI_NOTIFY_BUS_CHECK:
	case ACPI_NOTIFY_DEVICE_CHECK:
		if (!dock_in_progress(ds) && !acpi_device_enumerated(adev)) {
			begin_dock(ds);
			dock(ds);
			if (!dock_present(ds)) {
				acpi_handle_err(handle, "Unable to dock!\n");
				complete_dock(ds);
				break;
			}
			hotplug_dock_devices(ds, event);
			complete_dock(ds);
			dock_event(ds, event, DOCK_EVENT);
			acpi_evaluate_lck(ds->handle, 1);
			acpi_update_all_gpes();
			break;
		}
		if (dock_present(ds) || dock_in_progress(ds))
			break;
		/* This is a surprise removal */
		surprise_removal = 1;
		event = ACPI_NOTIFY_EJECT_REQUEST;
		/* Fall back */
		/* fall through */
	case ACPI_NOTIFY_EJECT_REQUEST:
		begin_undock(ds);
		if ((immediate_undock && !(ds->flags & DOCK_IS_ATA))
		   || surprise_removal)
			handle_eject_request(ds, event);
		else
			dock_event(ds, event, UNDOCK_EVENT);
		break;
	}
	return 0;
}