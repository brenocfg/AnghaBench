#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int ifindex; int /*<<< orphan*/  ifname; } ;
union wpa_event_data {TYPE_2__ interface_status; } ;
struct wpa_priv_interface {int /*<<< orphan*/  ifname; int /*<<< orphan*/  drv_priv; TYPE_1__* driver; struct wpa_priv_interface* next; } ;
struct wpa_priv_global {struct wpa_priv_interface* interfaces; } ;
typedef  enum wpa_event_type { ____Placeholder_wpa_event_type } wpa_event_type ;
struct TYPE_3__ {unsigned int (* get_ifindex ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EVENT_INTERFACE_STATUS ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ os_strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  wpa_supplicant_event (struct wpa_priv_interface*,int,union wpa_event_data*) ; 

void wpa_supplicant_event_global(void *ctx, enum wpa_event_type event,
				 union wpa_event_data *data)
{
	struct wpa_priv_global *global = ctx;
	struct wpa_priv_interface *iface;

	if (event != EVENT_INTERFACE_STATUS)
		return;

	for (iface = global->interfaces; iface; iface = iface->next) {
		if (os_strcmp(iface->ifname, data->interface_status.ifname) ==
		    0)
			break;
	}
	if (iface && iface->driver->get_ifindex) {
		unsigned int ifindex;

		ifindex = iface->driver->get_ifindex(iface->drv_priv);
		if (ifindex != data->interface_status.ifindex) {
			wpa_printf(MSG_DEBUG,
				   "%s: interface status ifindex %d mismatch (%d)",
				   iface->ifname, ifindex,
				   data->interface_status.ifindex);
			return;
		}
	}
	if (iface)
		wpa_supplicant_event(iface, event, data);
}