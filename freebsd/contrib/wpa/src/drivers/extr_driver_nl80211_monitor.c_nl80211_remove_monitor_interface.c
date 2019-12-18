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
struct wpa_driver_nl80211_data {scalar_t__ monitor_refcount; int monitor_ifidx; int monitor_sock; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  eloop_unregister_read_sock (int) ; 
 int /*<<< orphan*/  nl80211_remove_iface (struct wpa_driver_nl80211_data*,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,scalar_t__) ; 

void nl80211_remove_monitor_interface(struct wpa_driver_nl80211_data *drv)
{
	if (drv->monitor_refcount > 0)
		drv->monitor_refcount--;
	wpa_printf(MSG_DEBUG, "nl80211: Remove monitor interface: refcount=%d",
		   drv->monitor_refcount);
	if (drv->monitor_refcount > 0)
		return;

	if (drv->monitor_ifidx >= 0) {
		nl80211_remove_iface(drv, drv->monitor_ifidx);
		drv->monitor_ifidx = -1;
	}
	if (drv->monitor_sock >= 0) {
		eloop_unregister_read_sock(drv->monitor_sock);
		close(drv->monitor_sock);
		drv->monitor_sock = -1;
	}
}