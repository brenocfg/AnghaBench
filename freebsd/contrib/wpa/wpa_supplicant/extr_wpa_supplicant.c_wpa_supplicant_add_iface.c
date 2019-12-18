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
struct wpa_supplicant {int drv_flags; struct wpa_global* global; TYPE_1__* conf; int /*<<< orphan*/  ifname; struct wpa_supplicant* next; } ;
struct wpa_ssid {struct wpa_ssid* next; } ;
struct wpa_interface {scalar_t__ p2p_mgmt; int /*<<< orphan*/  ifname; scalar_t__ ctrl_interface; scalar_t__ driver; } ;
struct TYPE_4__ {int /*<<< orphan*/  conf_p2p_dev; scalar_t__ override_ctrl_interface; scalar_t__ override_driver; } ;
struct wpa_global {TYPE_2__ params; int /*<<< orphan*/  p2p_disabled; int /*<<< orphan*/ * p2p; struct wpa_supplicant* ifaces; } ;
struct TYPE_3__ {int /*<<< orphan*/  p2p_disabled; struct wpa_ssid* ssid; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  WPA_DISCONNECTED ; 
 int WPA_DRIVER_FLAGS_DEDICATED_P2P_DEVICE ; 
 int /*<<< orphan*/  wpa_dbg (struct wpa_supplicant*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 struct wpa_supplicant* wpa_supplicant_alloc (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wpa_supplicant_deinit_iface (struct wpa_supplicant*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ wpa_supplicant_init_iface (struct wpa_supplicant*,struct wpa_interface*) ; 
 int /*<<< orphan*/  wpa_supplicant_set_state (struct wpa_supplicant*,int /*<<< orphan*/ ) ; 
 scalar_t__ wpas_notify_iface_added (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wpas_notify_network_added (struct wpa_supplicant*,struct wpa_ssid*) ; 
 scalar_t__ wpas_p2p_add_p2pdev_interface (struct wpa_supplicant*,int /*<<< orphan*/ ) ; 

struct wpa_supplicant * wpa_supplicant_add_iface(struct wpa_global *global,
						 struct wpa_interface *iface,
						 struct wpa_supplicant *parent)
{
	struct wpa_supplicant *wpa_s;
	struct wpa_interface t_iface;
	struct wpa_ssid *ssid;

	if (global == NULL || iface == NULL)
		return NULL;

	wpa_s = wpa_supplicant_alloc(parent);
	if (wpa_s == NULL)
		return NULL;

	wpa_s->global = global;

	t_iface = *iface;
	if (global->params.override_driver) {
		wpa_printf(MSG_DEBUG, "Override interface parameter: driver "
			   "('%s' -> '%s')",
			   iface->driver, global->params.override_driver);
		t_iface.driver = global->params.override_driver;
	}
	if (global->params.override_ctrl_interface) {
		wpa_printf(MSG_DEBUG, "Override interface parameter: "
			   "ctrl_interface ('%s' -> '%s')",
			   iface->ctrl_interface,
			   global->params.override_ctrl_interface);
		t_iface.ctrl_interface =
			global->params.override_ctrl_interface;
	}
	if (wpa_supplicant_init_iface(wpa_s, &t_iface)) {
		wpa_printf(MSG_DEBUG, "Failed to add interface %s",
			   iface->ifname);
		wpa_supplicant_deinit_iface(wpa_s, 0, 0);
		return NULL;
	}

	if (iface->p2p_mgmt == 0) {
		/* Notify the control interfaces about new iface */
		if (wpas_notify_iface_added(wpa_s)) {
			wpa_supplicant_deinit_iface(wpa_s, 1, 0);
			return NULL;
		}

		for (ssid = wpa_s->conf->ssid; ssid; ssid = ssid->next)
			wpas_notify_network_added(wpa_s, ssid);
	}

	wpa_s->next = global->ifaces;
	global->ifaces = wpa_s;

	wpa_dbg(wpa_s, MSG_DEBUG, "Added interface %s", wpa_s->ifname);
	wpa_supplicant_set_state(wpa_s, WPA_DISCONNECTED);

#ifdef CONFIG_P2P
	if (wpa_s->global->p2p == NULL &&
	    !wpa_s->global->p2p_disabled && !wpa_s->conf->p2p_disabled &&
	    (wpa_s->drv_flags & WPA_DRIVER_FLAGS_DEDICATED_P2P_DEVICE) &&
	    wpas_p2p_add_p2pdev_interface(
		    wpa_s, wpa_s->global->params.conf_p2p_dev) < 0) {
		wpa_printf(MSG_INFO,
			   "P2P: Failed to enable P2P Device interface");
		/* Try to continue without. P2P will be disabled. */
	}
#endif /* CONFIG_P2P */

	return wpa_s;
}