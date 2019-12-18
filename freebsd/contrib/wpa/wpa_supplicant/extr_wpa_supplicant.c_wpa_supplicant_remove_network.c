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
struct TYPE_2__ {scalar_t__ prev_bssid_set; } ;
struct wpa_supplicant {scalar_t__ wpa_state; int own_disconnect_req; scalar_t__ sched_scanning; int /*<<< orphan*/  conf; int /*<<< orphan*/  eapol; int /*<<< orphan*/  wpa; struct wpa_ssid* current_ssid; TYPE_1__ sme; struct wpa_ssid* last_ssid; } ;
struct wpa_ssid {int disabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  WLAN_REASON_DEAUTH_LEAVING ; 
 scalar_t__ WPA_AUTHENTICATING ; 
 int /*<<< orphan*/  eapol_sm_invalidate_cached_session (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eapol_sm_notify_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct wpa_ssid* wpa_config_get_network (int /*<<< orphan*/ ,int) ; 
 scalar_t__ wpa_config_remove_network (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpa_sm_set_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_supplicant_cancel_sched_scan (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wpa_supplicant_deauthenticate (struct wpa_supplicant*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_supplicant_req_scan (struct wpa_supplicant*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpas_notify_network_removed (struct wpa_supplicant*,struct wpa_ssid*) ; 

int wpa_supplicant_remove_network(struct wpa_supplicant *wpa_s, int id)
{
	struct wpa_ssid *ssid;
	int was_disabled;

	ssid = wpa_config_get_network(wpa_s->conf, id);
	if (!ssid)
		return -1;
	wpas_notify_network_removed(wpa_s, ssid);

	if (wpa_s->last_ssid == ssid)
		wpa_s->last_ssid = NULL;

	if (ssid == wpa_s->current_ssid || !wpa_s->current_ssid) {
#ifdef CONFIG_SME
		wpa_s->sme.prev_bssid_set = 0;
#endif /* CONFIG_SME */
		/*
		 * Invalidate the EAP session cache if the current or
		 * previously used network is removed.
		 */
		eapol_sm_invalidate_cached_session(wpa_s->eapol);
	}

	if (ssid == wpa_s->current_ssid) {
		wpa_sm_set_config(wpa_s->wpa, NULL);
		eapol_sm_notify_config(wpa_s->eapol, NULL, NULL);

		if (wpa_s->wpa_state >= WPA_AUTHENTICATING)
			wpa_s->own_disconnect_req = 1;
		wpa_supplicant_deauthenticate(wpa_s,
					      WLAN_REASON_DEAUTH_LEAVING);
	}

	was_disabled = ssid->disabled;

	if (wpa_config_remove_network(wpa_s->conf, id) < 0)
		return -2;

	if (!was_disabled && wpa_s->sched_scanning) {
		wpa_printf(MSG_DEBUG,
			   "Stop ongoing sched_scan to remove network from filters");
		wpa_supplicant_cancel_sched_scan(wpa_s);
		wpa_supplicant_req_scan(wpa_s, 0, 0);
	}

	return 0;
}