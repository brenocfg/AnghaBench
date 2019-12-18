#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  ievent; int /*<<< orphan*/  ifname; } ;
union wpa_event_data {TYPE_1__ interface_status; } ;
struct wpa_driver_ndis_data {int /*<<< orphan*/  ctx; int /*<<< orphan*/  ifname; } ;
typedef  int /*<<< orphan*/  event ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_INTERFACE_REMOVED ; 
 int /*<<< orphan*/  EVENT_INTERFACE_STATUS ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  os_memset (union wpa_event_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  os_strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpa_supplicant_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,union wpa_event_data*) ; 

void wpa_driver_ndis_event_adapter_removal(struct wpa_driver_ndis_data *drv)
{
	union wpa_event_data event;

	wpa_printf(MSG_DEBUG, "NDIS: Notify Adapter Removal");
	os_memset(&event, 0, sizeof(event));
	os_strlcpy(event.interface_status.ifname, drv->ifname,
		   sizeof(event.interface_status.ifname));
	event.interface_status.ievent = EVENT_INTERFACE_REMOVED;
	wpa_supplicant_event(drv->ctx, EVENT_INTERFACE_STATUS, &event);
}