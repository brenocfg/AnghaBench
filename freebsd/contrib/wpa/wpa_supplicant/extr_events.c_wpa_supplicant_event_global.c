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
struct TYPE_4__ {unsigned int ifindex; scalar_t__ ievent; int /*<<< orphan*/  ifname; } ;
union wpa_event_data {TYPE_2__ interface_status; } ;
struct wpa_supplicant {int matched; int /*<<< orphan*/  drv_priv; TYPE_1__* driver; } ;
struct wpa_interface {int dummy; } ;
typedef  enum wpa_event_type { ____Placeholder_wpa_event_type } wpa_event_type ;
struct TYPE_3__ {unsigned int (* get_ifindex ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ EVENT_INTERFACE_ADDED ; 
 int EVENT_INTERFACE_STATUS ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  os_free (struct wpa_interface*) ; 
 unsigned int stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_dbg (struct wpa_supplicant*,int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 
 struct wpa_supplicant* wpa_supplicant_add_iface (void*,struct wpa_interface*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_supplicant_event (struct wpa_supplicant*,int,union wpa_event_data*) ; 
 struct wpa_supplicant* wpa_supplicant_get_iface (void*,int /*<<< orphan*/ ) ; 
 struct wpa_interface* wpa_supplicant_match_iface (void*,int /*<<< orphan*/ ) ; 

void wpa_supplicant_event_global(void *ctx, enum wpa_event_type event,
				 union wpa_event_data *data)
{
	struct wpa_supplicant *wpa_s;

	if (event != EVENT_INTERFACE_STATUS)
		return;

	wpa_s = wpa_supplicant_get_iface(ctx, data->interface_status.ifname);
	if (wpa_s && wpa_s->driver->get_ifindex) {
		unsigned int ifindex;

		ifindex = wpa_s->driver->get_ifindex(wpa_s->drv_priv);
		if (ifindex != data->interface_status.ifindex) {
			wpa_dbg(wpa_s, MSG_DEBUG,
				"interface status ifindex %d mismatch (%d)",
				ifindex, data->interface_status.ifindex);
			return;
		}
	}
#ifdef CONFIG_MATCH_IFACE
	else if (data->interface_status.ievent == EVENT_INTERFACE_ADDED) {
		struct wpa_interface *wpa_i;

		wpa_i = wpa_supplicant_match_iface(
			ctx, data->interface_status.ifname);
		if (!wpa_i)
			return;
		wpa_s = wpa_supplicant_add_iface(ctx, wpa_i, NULL);
		os_free(wpa_i);
		if (wpa_s)
			wpa_s->matched = 1;
	}
#endif /* CONFIG_MATCH_IFACE */

	if (wpa_s)
		wpa_supplicant_event(wpa_s, event, data);
}