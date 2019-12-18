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
struct wpa_supplicant {TYPE_1__* conf; } ;
struct wpa_ssid {scalar_t__ mode; int key_mgmt; int /*<<< orphan*/  ssid_len; int /*<<< orphan*/  ssid; struct wpa_ssid* pnext; } ;
struct TYPE_2__ {int num_prio; struct wpa_ssid** pssid; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_INFO ; 
 scalar_t__ WPAS_MODE_AP ; 
 scalar_t__ WPAS_MODE_IBSS ; 
 scalar_t__ WPAS_MODE_MESH ; 
 int WPA_KEY_MGMT_NONE ; 
 int WPA_KEY_MGMT_WPA_NONE ; 
 int /*<<< orphan*/  wpa_msg (struct wpa_supplicant*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_ssid_txt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ wpas_network_disabled (struct wpa_supplicant*,struct wpa_ssid*) ; 

__attribute__((used)) static struct wpa_ssid *
wpa_supplicant_pick_new_network(struct wpa_supplicant *wpa_s)
{
	int prio;
	struct wpa_ssid *ssid;

	for (prio = 0; prio < wpa_s->conf->num_prio; prio++) {
		for (ssid = wpa_s->conf->pssid[prio]; ssid; ssid = ssid->pnext)
		{
			if (wpas_network_disabled(wpa_s, ssid))
				continue;
#ifndef CONFIG_IBSS_RSN
			if (ssid->mode == WPAS_MODE_IBSS &&
			    !(ssid->key_mgmt & (WPA_KEY_MGMT_NONE |
						WPA_KEY_MGMT_WPA_NONE))) {
				wpa_msg(wpa_s, MSG_INFO,
					"IBSS RSN not supported in the build - cannot use the profile for SSID '%s'",
					wpa_ssid_txt(ssid->ssid,
						     ssid->ssid_len));
				continue;
			}
#endif /* !CONFIG_IBSS_RSN */
			if (ssid->mode == WPAS_MODE_IBSS ||
			    ssid->mode == WPAS_MODE_AP ||
			    ssid->mode == WPAS_MODE_MESH)
				return ssid;
		}
	}
	return NULL;
}