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
struct wpa_supplicant {scalar_t__ wpa_state; int own_disconnect_req; scalar_t__ key_mgmt; int reassociate; int /*<<< orphan*/ * ctrl_iface; struct wpa_config* conf; int /*<<< orphan*/  wpa; int /*<<< orphan*/  eapol; scalar_t__ current_ssid; int /*<<< orphan*/ * confanother; int /*<<< orphan*/ * confname; } ;
struct wpa_config {unsigned int changed_parameters; int ap_scan; int /*<<< orphan*/  fast_reauth; scalar_t__ ctrl_interface; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  WLAN_REASON_DEAUTH_LEAVING ; 
 scalar_t__ WPA_AUTHENTICATING ; 
 scalar_t__ WPA_KEY_MGMT_DPP ; 
 scalar_t__ WPA_KEY_MGMT_OWE ; 
 int /*<<< orphan*/  eapol_sm_invalidate_cached_session (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eapol_sm_notify_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eapol_sm_notify_eap_success (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ os_strcmp (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  rsn_preauth_deinit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_config_free (struct wpa_config*) ; 
 struct wpa_config* wpa_config_read (int /*<<< orphan*/ *,struct wpa_config*) ; 
 int /*<<< orphan*/  wpa_dbg (struct wpa_supplicant*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ wpa_key_mgmt_wpa_psk (scalar_t__) ; 
 int /*<<< orphan*/  wpa_msg (struct wpa_supplicant*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_sm_pmksa_cache_flush (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_sm_set_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_sm_set_fast_reauth (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_supplicant_clear_status (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wpa_supplicant_ctrl_iface_deinit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * wpa_supplicant_ctrl_iface_init (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wpa_supplicant_deauthenticate (struct wpa_supplicant*,int /*<<< orphan*/ ) ; 
 scalar_t__ wpa_supplicant_enabled_networks (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wpa_supplicant_req_scan (struct wpa_supplicant*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_supplicant_update_config (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wpas_notify_ap_scan_changed (struct wpa_supplicant*) ; 

int wpa_supplicant_reload_configuration(struct wpa_supplicant *wpa_s)
{
	struct wpa_config *conf;
	int reconf_ctrl;
	int old_ap_scan;

	if (wpa_s->confname == NULL)
		return -1;
	conf = wpa_config_read(wpa_s->confname, NULL);
	if (conf == NULL) {
		wpa_msg(wpa_s, MSG_ERROR, "Failed to parse the configuration "
			"file '%s' - exiting", wpa_s->confname);
		return -1;
	}
	if (wpa_s->confanother &&
	    !wpa_config_read(wpa_s->confanother, conf)) {
		wpa_msg(wpa_s, MSG_ERROR,
			"Failed to parse the configuration file '%s' - exiting",
			wpa_s->confanother);
		return -1;
	}

	conf->changed_parameters = (unsigned int) -1;

	reconf_ctrl = !!conf->ctrl_interface != !!wpa_s->conf->ctrl_interface
		|| (conf->ctrl_interface && wpa_s->conf->ctrl_interface &&
		    os_strcmp(conf->ctrl_interface,
			      wpa_s->conf->ctrl_interface) != 0);

	if (reconf_ctrl && wpa_s->ctrl_iface) {
		wpa_supplicant_ctrl_iface_deinit(wpa_s->ctrl_iface);
		wpa_s->ctrl_iface = NULL;
	}

	eapol_sm_invalidate_cached_session(wpa_s->eapol);
	if (wpa_s->current_ssid) {
		if (wpa_s->wpa_state >= WPA_AUTHENTICATING)
			wpa_s->own_disconnect_req = 1;
		wpa_supplicant_deauthenticate(wpa_s,
					      WLAN_REASON_DEAUTH_LEAVING);
	}

	/*
	 * TODO: should notify EAPOL SM about changes in opensc_engine_path,
	 * pkcs11_engine_path, pkcs11_module_path, openssl_ciphers.
	 */
	if (wpa_key_mgmt_wpa_psk(wpa_s->key_mgmt) ||
	    wpa_s->key_mgmt == WPA_KEY_MGMT_OWE ||
	    wpa_s->key_mgmt == WPA_KEY_MGMT_DPP) {
		/*
		 * Clear forced success to clear EAP state for next
		 * authentication.
		 */
		eapol_sm_notify_eap_success(wpa_s->eapol, FALSE);
	}
	eapol_sm_notify_config(wpa_s->eapol, NULL, NULL);
	wpa_sm_set_config(wpa_s->wpa, NULL);
	wpa_sm_pmksa_cache_flush(wpa_s->wpa, NULL);
	wpa_sm_set_fast_reauth(wpa_s->wpa, wpa_s->conf->fast_reauth);
	rsn_preauth_deinit(wpa_s->wpa);

	old_ap_scan = wpa_s->conf->ap_scan;
	wpa_config_free(wpa_s->conf);
	wpa_s->conf = conf;
	if (old_ap_scan != wpa_s->conf->ap_scan)
		wpas_notify_ap_scan_changed(wpa_s);

	if (reconf_ctrl)
		wpa_s->ctrl_iface = wpa_supplicant_ctrl_iface_init(wpa_s);

	wpa_supplicant_update_config(wpa_s);

	wpa_supplicant_clear_status(wpa_s);
	if (wpa_supplicant_enabled_networks(wpa_s)) {
		wpa_s->reassociate = 1;
		wpa_supplicant_req_scan(wpa_s, 0, 0);
	}
	wpa_dbg(wpa_s, MSG_DEBUG, "Reconfiguration completed");
	return 0;
}