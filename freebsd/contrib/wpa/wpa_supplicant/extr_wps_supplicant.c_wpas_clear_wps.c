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
struct wpa_supplicant {int own_disconnect_req; TYPE_1__* conf; int /*<<< orphan*/  eapol; int /*<<< orphan*/  wpa; struct wpa_ssid* current_ssid; scalar_t__ known_wps_freq; scalar_t__ after_wps; } ;
struct wpa_ssid {int key_mgmt; int id; struct wpa_ssid* next; } ;
struct TYPE_2__ {struct wpa_ssid* ssid; } ;

/* Variables and functions */
 int /*<<< orphan*/  WLAN_REASON_DEAUTH_LEAVING ; 
 int WPA_KEY_MGMT_WPS ; 
 int /*<<< orphan*/  eapol_sm_notify_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,struct wpa_supplicant*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_config_remove_network (TYPE_1__*,int) ; 
 int /*<<< orphan*/  wpa_sm_set_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_supplicant_deauthenticate (struct wpa_supplicant*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpas_notify_network_removed (struct wpa_supplicant*,struct wpa_ssid*) ; 
 int /*<<< orphan*/  wpas_wps_clear_ap_info (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wpas_wps_clear_timeout ; 
 int /*<<< orphan*/  wpas_wps_reenable_networks (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wpas_wps_timeout ; 

__attribute__((used)) static void wpas_clear_wps(struct wpa_supplicant *wpa_s)
{
	int id;
	struct wpa_ssid *ssid, *remove_ssid = NULL, *prev_current;

	wpa_s->after_wps = 0;
	wpa_s->known_wps_freq = 0;

	prev_current = wpa_s->current_ssid;

	/* Enable the networks disabled during wpas_wps_reassoc */
	wpas_wps_reenable_networks(wpa_s);

	eloop_cancel_timeout(wpas_wps_timeout, wpa_s, NULL);
	eloop_cancel_timeout(wpas_wps_clear_timeout, wpa_s, NULL);

	/* Remove any existing WPS network from configuration */
	ssid = wpa_s->conf->ssid;
	while (ssid) {
		if (ssid->key_mgmt & WPA_KEY_MGMT_WPS) {
			if (ssid == wpa_s->current_ssid) {
				wpa_s->own_disconnect_req = 1;
				wpa_supplicant_deauthenticate(
					wpa_s, WLAN_REASON_DEAUTH_LEAVING);
			}
			id = ssid->id;
			remove_ssid = ssid;
		} else
			id = -1;
		ssid = ssid->next;
		if (id >= 0) {
			if (prev_current == remove_ssid) {
				wpa_sm_set_config(wpa_s->wpa, NULL);
				eapol_sm_notify_config(wpa_s->eapol, NULL,
						       NULL);
			}
			wpas_notify_network_removed(wpa_s, remove_ssid);
			wpa_config_remove_network(wpa_s->conf, id);
		}
	}

	wpas_wps_clear_ap_info(wpa_s);
}