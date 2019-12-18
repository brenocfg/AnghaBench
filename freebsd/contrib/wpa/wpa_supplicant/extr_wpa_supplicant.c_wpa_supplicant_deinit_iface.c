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
struct wpa_supplicant {int disconnected; struct wpa_supplicant* ssids_from_scan_req; int /*<<< orphan*/ * conf; int /*<<< orphan*/ * ifmsh; int /*<<< orphan*/ * ctrl_iface; scalar_t__ drv_priv; int /*<<< orphan*/ * received_mb_ies; int /*<<< orphan*/ * fst; struct wpa_supplicant* next; int /*<<< orphan*/  ifname; struct wpa_supplicant* parent; struct wpa_supplicant* p2pdev; struct wpa_global* global; } ;
struct wpa_global {struct wpa_supplicant* ifaces; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  WLAN_REASON_DEAUTH_LEAVING ; 
 int /*<<< orphan*/  WPA_EVENT_TERMINATING ; 
 int /*<<< orphan*/  fst_detach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_free (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  radio_remove_interface (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wpa_clear_keys (struct wpa_supplicant*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_config_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_drv_deinit (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wpa_drv_set_countermeasures (struct wpa_supplicant*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_msg (struct wpa_supplicant*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_supplicant_cleanup (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wpa_supplicant_ctrl_iface_deinit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_supplicant_deauthenticate (struct wpa_supplicant*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_supplicant_mesh_iface_deinit (struct wpa_supplicant*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_supplicant_remove_iface (struct wpa_global*,struct wpa_supplicant*,int) ; 
 int /*<<< orphan*/  wpabuf_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpas_ctrl_radio_work_flush (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wpas_notify_iface_removed (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wpas_p2p_deinit_iface (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wpas_p2p_group_remove (struct wpa_supplicant*,char*) ; 

__attribute__((used)) static void wpa_supplicant_deinit_iface(struct wpa_supplicant *wpa_s,
					int notify, int terminate)
{
	struct wpa_global *global = wpa_s->global;
	struct wpa_supplicant *iface, *prev;

	if (wpa_s == wpa_s->parent)
		wpas_p2p_group_remove(wpa_s, "*");

	iface = global->ifaces;
	while (iface) {
		if (iface->p2pdev == wpa_s)
			iface->p2pdev = iface->parent;
		if (iface == wpa_s || iface->parent != wpa_s) {
			iface = iface->next;
			continue;
		}
		wpa_printf(MSG_DEBUG,
			   "Remove remaining child interface %s from parent %s",
			   iface->ifname, wpa_s->ifname);
		prev = iface;
		iface = iface->next;
		wpa_supplicant_remove_iface(global, prev, terminate);
	}

	wpa_s->disconnected = 1;
	if (wpa_s->drv_priv) {
		wpa_supplicant_deauthenticate(wpa_s,
					      WLAN_REASON_DEAUTH_LEAVING);

		wpa_drv_set_countermeasures(wpa_s, 0);
		wpa_clear_keys(wpa_s, NULL);
	}

	wpa_supplicant_cleanup(wpa_s);
	wpas_p2p_deinit_iface(wpa_s);

	wpas_ctrl_radio_work_flush(wpa_s);
	radio_remove_interface(wpa_s);

#ifdef CONFIG_FST
	if (wpa_s->fst) {
		fst_detach(wpa_s->fst);
		wpa_s->fst = NULL;
	}
	if (wpa_s->received_mb_ies) {
		wpabuf_free(wpa_s->received_mb_ies);
		wpa_s->received_mb_ies = NULL;
	}
#endif /* CONFIG_FST */

	if (wpa_s->drv_priv)
		wpa_drv_deinit(wpa_s);

	if (notify)
		wpas_notify_iface_removed(wpa_s);

	if (terminate)
		wpa_msg(wpa_s, MSG_INFO, WPA_EVENT_TERMINATING);

	if (wpa_s->ctrl_iface) {
		wpa_supplicant_ctrl_iface_deinit(wpa_s->ctrl_iface);
		wpa_s->ctrl_iface = NULL;
	}

#ifdef CONFIG_MESH
	if (wpa_s->ifmsh) {
		wpa_supplicant_mesh_iface_deinit(wpa_s, wpa_s->ifmsh);
		wpa_s->ifmsh = NULL;
	}
#endif /* CONFIG_MESH */

	if (wpa_s->conf != NULL) {
		wpa_config_free(wpa_s->conf);
		wpa_s->conf = NULL;
	}

	os_free(wpa_s->ssids_from_scan_req);

	os_free(wpa_s);
}