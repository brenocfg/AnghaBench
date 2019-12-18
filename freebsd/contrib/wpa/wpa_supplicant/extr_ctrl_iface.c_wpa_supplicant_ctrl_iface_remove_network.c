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
struct TYPE_3__ {scalar_t__ prev_bssid_set; } ;
struct wpa_supplicant {scalar_t__ wpa_state; int own_disconnect_req; TYPE_2__* conf; struct wpa_ssid* last_ssid; int /*<<< orphan*/  eapol; int /*<<< orphan*/  wpa; TYPE_1__ sme; scalar_t__ current_ssid; scalar_t__ sched_scanning; } ;
struct wpa_ssid {int id; struct wpa_ssid* next; } ;
struct TYPE_4__ {struct wpa_ssid* ssid; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  WLAN_REASON_DEAUTH_LEAVING ; 
 scalar_t__ WPA_AUTHENTICATING ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  eapol_sm_invalidate_cached_session (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eapol_sm_notify_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ os_strcmp (char*,char*) ; 
 int /*<<< orphan*/  wpa_config_remove_network (TYPE_2__*,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wpa_sm_set_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_supplicant_cancel_sched_scan (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wpa_supplicant_deauthenticate (struct wpa_supplicant*,int /*<<< orphan*/ ) ; 
 int wpa_supplicant_remove_network (struct wpa_supplicant*,int) ; 
 int /*<<< orphan*/  wpas_notify_network_removed (struct wpa_supplicant*,struct wpa_ssid*) ; 

__attribute__((used)) static int wpa_supplicant_ctrl_iface_remove_network(
	struct wpa_supplicant *wpa_s, char *cmd)
{
	int id;
	struct wpa_ssid *ssid;
	int result;

	/* cmd: "<network id>" or "all" */
	if (os_strcmp(cmd, "all") == 0) {
		wpa_printf(MSG_DEBUG, "CTRL_IFACE: REMOVE_NETWORK all");
		if (wpa_s->sched_scanning)
			wpa_supplicant_cancel_sched_scan(wpa_s);

		eapol_sm_invalidate_cached_session(wpa_s->eapol);
		if (wpa_s->current_ssid) {
#ifdef CONFIG_SME
			wpa_s->sme.prev_bssid_set = 0;
#endif /* CONFIG_SME */
			wpa_sm_set_config(wpa_s->wpa, NULL);
			eapol_sm_notify_config(wpa_s->eapol, NULL, NULL);
			if (wpa_s->wpa_state >= WPA_AUTHENTICATING)
				wpa_s->own_disconnect_req = 1;
			wpa_supplicant_deauthenticate(
				wpa_s, WLAN_REASON_DEAUTH_LEAVING);
		}
		ssid = wpa_s->conf->ssid;
		while (ssid) {
			struct wpa_ssid *remove_ssid = ssid;
			id = ssid->id;
			ssid = ssid->next;
			if (wpa_s->last_ssid == remove_ssid)
				wpa_s->last_ssid = NULL;
			wpas_notify_network_removed(wpa_s, remove_ssid);
			wpa_config_remove_network(wpa_s->conf, id);
		}
		return 0;
	}

	id = atoi(cmd);
	wpa_printf(MSG_DEBUG, "CTRL_IFACE: REMOVE_NETWORK id=%d", id);

	result = wpa_supplicant_remove_network(wpa_s, id);
	if (result == -1) {
		wpa_printf(MSG_DEBUG, "CTRL_IFACE: Could not find network "
			   "id=%d", id);
		return -1;
	}
	if (result == -2) {
		wpa_printf(MSG_DEBUG, "CTRL_IFACE: Not able to remove the "
			   "network id=%d", id);
		return -1;
	}
	return 0;
}