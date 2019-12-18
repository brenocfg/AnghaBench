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
typedef  int /*<<< orphan*/  wpa_ie ;
typedef  int /*<<< orphan*/  u8 ;
struct wpa_supplicant {struct wpa_ssid* current_ssid; int /*<<< orphan*/  eapol; int /*<<< orphan*/  bssid; TYPE_1__* conf; } ;
struct wpa_ssid {size_t ssid_len; int /*<<< orphan*/  key_mgmt; int /*<<< orphan*/  ssid; } ;
struct TYPE_2__ {int ap_scan; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int SSID_MAX_LEN ; 
 scalar_t__ disallowed_bssid (struct wpa_supplicant*,int /*<<< orphan*/ ) ; 
 scalar_t__ disallowed_ssid (struct wpa_supplicant*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  eapol_sm_invalidate_cached_session (int /*<<< orphan*/ ) ; 
 scalar_t__ os_memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  wpa_dbg (struct wpa_supplicant*,int /*<<< orphan*/ ,char*,...) ; 
 int wpa_drv_get_ssid (struct wpa_supplicant*,int /*<<< orphan*/ *) ; 
 scalar_t__ wpa_key_mgmt_wpa_any (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_msg (struct wpa_supplicant*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wpa_ssid_txt (int /*<<< orphan*/ *,size_t) ; 
 struct wpa_ssid* wpa_supplicant_get_ssid (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wpa_supplicant_initiate_eapol (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wpa_supplicant_rsn_supp_set_config (struct wpa_supplicant*,struct wpa_ssid*) ; 
 int /*<<< orphan*/  wpa_supplicant_set_non_wpa_policy (struct wpa_supplicant*,struct wpa_ssid*) ; 
 scalar_t__ wpa_supplicant_set_suites (struct wpa_supplicant*,int /*<<< orphan*/ *,struct wpa_ssid*,int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  wpa_supplicant_update_current_bss (struct wpa_supplicant*) ; 
 scalar_t__ wpas_network_disabled (struct wpa_supplicant*,struct wpa_ssid*) ; 
 int /*<<< orphan*/  wpas_notify_network_changed (struct wpa_supplicant*) ; 
 int wpas_temp_disabled (struct wpa_supplicant*,struct wpa_ssid*) ; 

__attribute__((used)) static int wpa_supplicant_select_config(struct wpa_supplicant *wpa_s)
{
	struct wpa_ssid *ssid, *old_ssid;
	u8 drv_ssid[SSID_MAX_LEN];
	size_t drv_ssid_len;
	int res;

	if (wpa_s->conf->ap_scan == 1 && wpa_s->current_ssid) {
		wpa_supplicant_update_current_bss(wpa_s);

		if (wpa_s->current_ssid->ssid_len == 0)
			return 0; /* current profile still in use */
		res = wpa_drv_get_ssid(wpa_s, drv_ssid);
		if (res < 0) {
			wpa_msg(wpa_s, MSG_INFO,
				"Failed to read SSID from driver");
			return 0; /* try to use current profile */
		}
		drv_ssid_len = res;

		if (drv_ssid_len == wpa_s->current_ssid->ssid_len &&
		    os_memcmp(drv_ssid, wpa_s->current_ssid->ssid,
			      drv_ssid_len) == 0)
			return 0; /* current profile still in use */

		wpa_msg(wpa_s, MSG_DEBUG,
			"Driver-initiated BSS selection changed the SSID to %s",
			wpa_ssid_txt(drv_ssid, drv_ssid_len));
		/* continue selecting a new network profile */
	}

	wpa_dbg(wpa_s, MSG_DEBUG, "Select network based on association "
		"information");
	ssid = wpa_supplicant_get_ssid(wpa_s);
	if (ssid == NULL) {
		wpa_msg(wpa_s, MSG_INFO,
			"No network configuration found for the current AP");
		return -1;
	}

	if (wpas_network_disabled(wpa_s, ssid)) {
		wpa_dbg(wpa_s, MSG_DEBUG, "Selected network is disabled");
		return -1;
	}

	if (disallowed_bssid(wpa_s, wpa_s->bssid) ||
	    disallowed_ssid(wpa_s, ssid->ssid, ssid->ssid_len)) {
		wpa_dbg(wpa_s, MSG_DEBUG, "Selected BSS is disallowed");
		return -1;
	}

	res = wpas_temp_disabled(wpa_s, ssid);
	if (res > 0) {
		wpa_dbg(wpa_s, MSG_DEBUG, "Selected network is temporarily "
			"disabled for %d second(s)", res);
		return -1;
	}

	wpa_dbg(wpa_s, MSG_DEBUG, "Network configuration found for the "
		"current AP");
	if (wpa_key_mgmt_wpa_any(ssid->key_mgmt)) {
		u8 wpa_ie[80];
		size_t wpa_ie_len = sizeof(wpa_ie);
		if (wpa_supplicant_set_suites(wpa_s, NULL, ssid,
					      wpa_ie, &wpa_ie_len) < 0)
			wpa_dbg(wpa_s, MSG_DEBUG, "Could not set WPA suites");
	} else {
		wpa_supplicant_set_non_wpa_policy(wpa_s, ssid);
	}

	if (wpa_s->current_ssid && wpa_s->current_ssid != ssid)
		eapol_sm_invalidate_cached_session(wpa_s->eapol);
	old_ssid = wpa_s->current_ssid;
	wpa_s->current_ssid = ssid;

	wpa_supplicant_update_current_bss(wpa_s);

	wpa_supplicant_rsn_supp_set_config(wpa_s, wpa_s->current_ssid);
	wpa_supplicant_initiate_eapol(wpa_s);
	if (old_ssid != wpa_s->current_ssid)
		wpas_notify_network_changed(wpa_s);

	return 0;
}