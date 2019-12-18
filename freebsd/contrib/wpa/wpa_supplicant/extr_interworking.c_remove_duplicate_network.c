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
struct wpa_supplicant {int own_disconnect_req; TYPE_1__* conf; int /*<<< orphan*/  eapol; int /*<<< orphan*/  wpa; struct wpa_ssid* current_ssid; } ;
struct wpa_ssid {int /*<<< orphan*/  id; int /*<<< orphan*/  ssid; int /*<<< orphan*/  ssid_len; struct wpa_cred* parent_cred; struct wpa_ssid* next; } ;
struct wpa_cred {int dummy; } ;
struct wpa_bss {int /*<<< orphan*/  ssid_len; int /*<<< orphan*/  ssid; } ;
struct TYPE_2__ {struct wpa_ssid* ssid; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  WLAN_REASON_DEAUTH_LEAVING ; 
 int /*<<< orphan*/  eapol_sm_notify_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ os_memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_config_remove_network (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpa_sm_set_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_supplicant_deauthenticate (struct wpa_supplicant*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpas_notify_network_removed (struct wpa_supplicant*,struct wpa_ssid*) ; 

__attribute__((used)) static void remove_duplicate_network(struct wpa_supplicant *wpa_s,
				     struct wpa_cred *cred,
				     struct wpa_bss *bss)
{
	struct wpa_ssid *ssid;

	for (ssid = wpa_s->conf->ssid; ssid; ssid = ssid->next) {
		if (ssid->parent_cred != cred)
			continue;
		if (ssid->ssid_len != bss->ssid_len ||
		    os_memcmp(ssid->ssid, bss->ssid, bss->ssid_len) != 0)
			continue;

		break;
	}

	if (ssid == NULL)
		return;

	wpa_printf(MSG_DEBUG, "Interworking: Remove duplicate network entry for the same credential");

	if (ssid == wpa_s->current_ssid) {
		wpa_sm_set_config(wpa_s->wpa, NULL);
		eapol_sm_notify_config(wpa_s->eapol, NULL, NULL);
		wpa_s->own_disconnect_req = 1;
		wpa_supplicant_deauthenticate(wpa_s,
					      WLAN_REASON_DEAUTH_LEAVING);
	}

	wpas_notify_network_removed(wpa_s, ssid);
	wpa_config_remove_network(wpa_s->conf, ssid->id);
}