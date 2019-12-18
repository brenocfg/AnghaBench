#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ usec; scalar_t__ sec; } ;
struct wpa_supplicant {scalar_t__ wpa_state; scalar_t__ key_mgmt; scalar_t__ enabled_4addr_mode; scalar_t__ ieee80211ac; int /*<<< orphan*/  last_tk; int /*<<< orphan*/  last_tk_alg; scalar_t__ wnmsleep_used; int /*<<< orphan*/  eapol; int /*<<< orphan*/ * current_ssid; scalar_t__ ap_ies_from_associnfo; scalar_t__ assoc_freq; int /*<<< orphan*/ * current_bss; int /*<<< orphan*/  pending_bssid; int /*<<< orphan*/  bssid; TYPE_1__ session_start; int /*<<< orphan*/  session_length; int /*<<< orphan*/ * ibss_rsn; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  WPA_ALG_NONE ; 
 int /*<<< orphan*/  WPA_DISCONNECTED ; 
 scalar_t__ WPA_INTERFACE_DISABLED ; 
 scalar_t__ WPA_KEY_MGMT_DPP ; 
 scalar_t__ WPA_KEY_MGMT_OWE ; 
 int /*<<< orphan*/  eapol_sm_notify_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eapol_sm_notify_eap_success (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eapol_sm_notify_portEnabled (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eapol_sm_notify_portValid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibss_rsn_deinit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_zero_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  os_reltime_age (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ os_reltime_initialized (TYPE_1__*) ; 
 int /*<<< orphan*/  sme_clear_on_disassoc (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wnm_bss_keep_alive_deinit (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wnm_clear_coloc_intf_reporting (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wpa_drv_configure_frame_filters (struct wpa_supplicant*,int /*<<< orphan*/ ) ; 
 scalar_t__ wpa_drv_set_4addr_mode (struct wpa_supplicant*,int /*<<< orphan*/ ) ; 
 scalar_t__ wpa_key_mgmt_wpa_psk (scalar_t__) ; 
 int /*<<< orphan*/  wpa_supplicant_ap_deinit (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wpa_supplicant_set_state (struct wpa_supplicant*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpas_notify_bssid_changed (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wpas_notify_session_length (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wpas_rrm_reset (struct wpa_supplicant*) ; 

void wpa_supplicant_mark_disassoc(struct wpa_supplicant *wpa_s)
{
	int bssid_changed;

	wnm_bss_keep_alive_deinit(wpa_s);

#ifdef CONFIG_IBSS_RSN
	ibss_rsn_deinit(wpa_s->ibss_rsn);
	wpa_s->ibss_rsn = NULL;
#endif /* CONFIG_IBSS_RSN */

#ifdef CONFIG_AP
	wpa_supplicant_ap_deinit(wpa_s);
#endif /* CONFIG_AP */

#ifdef CONFIG_HS20
	/* Clear possibly configured frame filters */
	wpa_drv_configure_frame_filters(wpa_s, 0);
#endif /* CONFIG_HS20 */

	if (wpa_s->wpa_state == WPA_INTERFACE_DISABLED)
		return;

	if (os_reltime_initialized(&wpa_s->session_start)) {
		os_reltime_age(&wpa_s->session_start, &wpa_s->session_length);
		wpa_s->session_start.sec = 0;
		wpa_s->session_start.usec = 0;
		wpas_notify_session_length(wpa_s);
	}

	wpa_supplicant_set_state(wpa_s, WPA_DISCONNECTED);
	bssid_changed = !is_zero_ether_addr(wpa_s->bssid);
	os_memset(wpa_s->bssid, 0, ETH_ALEN);
	os_memset(wpa_s->pending_bssid, 0, ETH_ALEN);
	sme_clear_on_disassoc(wpa_s);
	wpa_s->current_bss = NULL;
	wpa_s->assoc_freq = 0;

	if (bssid_changed)
		wpas_notify_bssid_changed(wpa_s);

	eapol_sm_notify_portEnabled(wpa_s->eapol, FALSE);
	eapol_sm_notify_portValid(wpa_s->eapol, FALSE);
	if (wpa_key_mgmt_wpa_psk(wpa_s->key_mgmt) ||
	    wpa_s->key_mgmt == WPA_KEY_MGMT_OWE ||
	    wpa_s->key_mgmt == WPA_KEY_MGMT_DPP)
		eapol_sm_notify_eap_success(wpa_s->eapol, FALSE);
	wpa_s->ap_ies_from_associnfo = 0;
	wpa_s->current_ssid = NULL;
	eapol_sm_notify_config(wpa_s->eapol, NULL, NULL);
	wpa_s->key_mgmt = 0;

	wpas_rrm_reset(wpa_s);
	wpa_s->wnmsleep_used = 0;
	wnm_clear_coloc_intf_reporting(wpa_s);

#ifdef CONFIG_TESTING_OPTIONS
	wpa_s->last_tk_alg = WPA_ALG_NONE;
	os_memset(wpa_s->last_tk, 0, sizeof(wpa_s->last_tk));
#endif /* CONFIG_TESTING_OPTIONS */
	wpa_s->ieee80211ac = 0;

	if (wpa_s->enabled_4addr_mode && wpa_drv_set_4addr_mode(wpa_s, 0) == 0)
		wpa_s->enabled_4addr_mode = 0;
}