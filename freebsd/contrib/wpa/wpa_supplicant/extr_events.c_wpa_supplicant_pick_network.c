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
struct wpa_supplicant {scalar_t__ last_scan_res_used; int /*<<< orphan*/  blacklist_cleared; int /*<<< orphan*/  countermeasures; scalar_t__ blacklist; TYPE_1__* conf; struct wpa_ssid* next_ssid; int /*<<< orphan*/ * last_scan_res; } ;
struct wpa_ssid {scalar_t__ priority; int /*<<< orphan*/  ext_psk; int /*<<< orphan*/  passphrase; int /*<<< orphan*/  psk_set; scalar_t__ mem_only_psk; struct wpa_ssid* next; } ;
struct wpa_bss {int dummy; } ;
struct TYPE_2__ {int num_prio; struct wpa_ssid** pssid; struct wpa_ssid* ssid; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  WPA_CTRL_REQ_PSK_PASSPHRASE ; 
 int /*<<< orphan*/  wpa_blacklist_clear (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wpa_dbg (struct wpa_supplicant*,int /*<<< orphan*/ ,char*) ; 
 char* wpa_supplicant_ctrl_req_to_string (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const**) ; 
 struct wpa_bss* wpa_supplicant_select_bss (struct wpa_supplicant*,struct wpa_ssid*,struct wpa_ssid**,int) ; 
 int /*<<< orphan*/  wpas_notify_network_request (struct wpa_supplicant*,struct wpa_ssid*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpas_send_ctrl_req (struct wpa_supplicant*,struct wpa_ssid*,char const*,char const*) ; 

struct wpa_bss * wpa_supplicant_pick_network(struct wpa_supplicant *wpa_s,
					     struct wpa_ssid **selected_ssid)
{
	struct wpa_bss *selected = NULL;
	int prio;
	struct wpa_ssid *next_ssid = NULL;
	struct wpa_ssid *ssid;

	if (wpa_s->last_scan_res == NULL ||
	    wpa_s->last_scan_res_used == 0)
		return NULL; /* no scan results from last update */

	if (wpa_s->next_ssid) {
		/* check that next_ssid is still valid */
		for (ssid = wpa_s->conf->ssid; ssid; ssid = ssid->next) {
			if (ssid == wpa_s->next_ssid)
				break;
		}
		next_ssid = ssid;
		wpa_s->next_ssid = NULL;
	}

	while (selected == NULL) {
		for (prio = 0; prio < wpa_s->conf->num_prio; prio++) {
			if (next_ssid && next_ssid->priority ==
			    wpa_s->conf->pssid[prio]->priority) {
				selected = wpa_supplicant_select_bss(
					wpa_s, next_ssid, selected_ssid, 1);
				if (selected)
					break;
			}
			selected = wpa_supplicant_select_bss(
				wpa_s, wpa_s->conf->pssid[prio],
				selected_ssid, 0);
			if (selected)
				break;
		}

		if (selected == NULL && wpa_s->blacklist &&
		    !wpa_s->countermeasures) {
			wpa_dbg(wpa_s, MSG_DEBUG, "No APs found - clear "
				"blacklist and try again");
			wpa_blacklist_clear(wpa_s);
			wpa_s->blacklist_cleared++;
		} else if (selected == NULL)
			break;
	}

	ssid = *selected_ssid;
	if (selected && ssid && ssid->mem_only_psk && !ssid->psk_set &&
	    !ssid->passphrase && !ssid->ext_psk) {
		const char *field_name, *txt = NULL;

		wpa_dbg(wpa_s, MSG_DEBUG,
			"PSK/passphrase not yet available for the selected network");

		wpas_notify_network_request(wpa_s, ssid,
					    WPA_CTRL_REQ_PSK_PASSPHRASE, NULL);

		field_name = wpa_supplicant_ctrl_req_to_string(
			WPA_CTRL_REQ_PSK_PASSPHRASE, NULL, &txt);
		if (field_name == NULL)
			return NULL;

		wpas_send_ctrl_req(wpa_s, ssid, field_name, txt);

		selected = NULL;
	}

	return selected;
}