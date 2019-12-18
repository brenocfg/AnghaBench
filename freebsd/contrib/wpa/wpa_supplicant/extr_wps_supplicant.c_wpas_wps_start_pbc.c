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
typedef  int /*<<< orphan*/  u8 ;
struct wpa_supplicant {scalar_t__ wps_fragment_size; TYPE_1__* go_params; scalar_t__ ap_iface; } ;
struct TYPE_4__ {scalar_t__ fragment_size; } ;
struct wpa_ssid {int temporary; int p2p_group; int pbss; int multi_ap_backhaul_sta; TYPE_2__ eap; scalar_t__ ssid_len; scalar_t__ ssid; } ;
typedef  int /*<<< orphan*/  phase1 ;
struct TYPE_3__ {int freq; int /*<<< orphan*/  ssid; scalar_t__ ssid_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  WPS_EV_PBC_ACTIVE ; 
 int /*<<< orphan*/  WPS_PBC_WALK_TIME ; 
 int /*<<< orphan*/  eloop_register_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wpa_supplicant*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_memcpy (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  os_snprintf (char*,int,char*,char*) ; 
 scalar_t__ os_zalloc (scalar_t__) ; 
 scalar_t__ wpa_config_set_quoted (struct wpa_ssid*,char*,char*) ; 
 int /*<<< orphan*/  wpa_hexdump_ascii (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpa_supplicant_wps_event (struct wpa_supplicant*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpas_clear_wps (struct wpa_supplicant*) ; 
 struct wpa_ssid* wpas_wps_add_network (struct wpa_supplicant*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  wpas_wps_reassoc (struct wpa_supplicant*,struct wpa_ssid*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpas_wps_timeout ; 

int wpas_wps_start_pbc(struct wpa_supplicant *wpa_s, const u8 *bssid,
		       int p2p_group, int multi_ap_backhaul_sta)
{
	struct wpa_ssid *ssid;
	char phase1[32];

#ifdef CONFIG_AP
	if (wpa_s->ap_iface) {
		wpa_printf(MSG_DEBUG,
			   "WPS: Reject request to start Registrar(as station) operation while AP mode is enabled");
		return -1;
	}
#endif /* CONFIG_AP */
	wpas_clear_wps(wpa_s);
	ssid = wpas_wps_add_network(wpa_s, 0, NULL, bssid);
	if (ssid == NULL)
		return -1;
	ssid->temporary = 1;
	ssid->p2p_group = p2p_group;
	/*
	 * When starting a regular WPS process (not P2P group formation)
	 * the registrar/final station can be either AP or PCP
	 * so use a "don't care" value for the pbss flag.
	 */
	if (!p2p_group)
		ssid->pbss = 2;
#ifdef CONFIG_P2P
	if (p2p_group && wpa_s->go_params && wpa_s->go_params->ssid_len) {
		ssid->ssid = os_zalloc(wpa_s->go_params->ssid_len + 1);
		if (ssid->ssid) {
			ssid->ssid_len = wpa_s->go_params->ssid_len;
			os_memcpy(ssid->ssid, wpa_s->go_params->ssid,
				  ssid->ssid_len);
			if (wpa_s->go_params->freq > 56160) {
				/* P2P in 60 GHz uses PBSS */
				ssid->pbss = 1;
			}
			wpa_hexdump_ascii(MSG_DEBUG, "WPS: Use specific AP "
					  "SSID", ssid->ssid, ssid->ssid_len);
		}
	}
#endif /* CONFIG_P2P */
	os_snprintf(phase1, sizeof(phase1), "pbc=1%s",
		    multi_ap_backhaul_sta ? " multi_ap=1" : "");
	if (wpa_config_set_quoted(ssid, "phase1", phase1) < 0)
		return -1;
	if (wpa_s->wps_fragment_size)
		ssid->eap.fragment_size = wpa_s->wps_fragment_size;
	if (multi_ap_backhaul_sta)
		ssid->multi_ap_backhaul_sta = 1;
	wpa_supplicant_wps_event(wpa_s, WPS_EV_PBC_ACTIVE, NULL);
	eloop_register_timeout(WPS_PBC_WALK_TIME, 0, wpas_wps_timeout,
			       wpa_s, NULL);
	wpas_wps_reassoc(wpa_s, ssid, bssid, 0);
	return 0;
}