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
struct wpabuf {int dummy; } ;
struct wpa_supplicant {scalar_t__ key_mgmt; int drv_flags; int /*<<< orphan*/  eapol; scalar_t__ current_bss; TYPE_1__* conf; struct wpa_ssid* current_ssid; } ;
struct wpa_ssid {scalar_t__ mode; int eapol_flags; scalar_t__ mka_psk_set; int /*<<< orphan*/  eap; int /*<<< orphan*/  eap_workaround; } ;
struct eapol_config {int accept_802_1x_keys; int eap_disabled; int /*<<< orphan*/  wps; int /*<<< orphan*/  external_sim; int /*<<< orphan*/  workaround; int /*<<< orphan*/  fast_reauth; int /*<<< orphan*/  required_keys; } ;
typedef  int /*<<< orphan*/  eapol_conf ;
struct TYPE_2__ {int /*<<< orphan*/  external_sim; int /*<<< orphan*/  fast_reauth; } ;

/* Variables and functions */
 int /*<<< orphan*/  Auto ; 
 int EAPOL_FLAG_REQUIRE_KEY_BROADCAST ; 
 int EAPOL_FLAG_REQUIRE_KEY_UNICAST ; 
 int /*<<< orphan*/  EAPOL_LOCAL_WPS_IN_USE ; 
 int /*<<< orphan*/  EAPOL_PEER_IS_WPS20_AP ; 
 int /*<<< orphan*/  EAPOL_REQUIRE_KEY_BROADCAST ; 
 int /*<<< orphan*/  EAPOL_REQUIRE_KEY_UNICAST ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  ForceAuthorized ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ WPAS_MODE_IBSS ; 
 int WPA_DRIVER_FLAGS_WIRED ; 
 scalar_t__ WPA_KEY_MGMT_IEEE8021X_NO_WPA ; 
 scalar_t__ WPA_KEY_MGMT_NONE ; 
 scalar_t__ WPA_KEY_MGMT_WPA_NONE ; 
 scalar_t__ WPA_KEY_MGMT_WPS ; 
 int /*<<< orphan*/  WPS_IE_VENDOR_TYPE ; 
 int /*<<< orphan*/  eapol_sm_notify_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct eapol_config*) ; 
 int /*<<< orphan*/  eapol_sm_notify_eap_fail (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eapol_sm_notify_eap_success (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eapol_sm_notify_portControl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee802_1x_alloc_kay_sm (struct wpa_supplicant*,struct wpa_ssid*) ; 
 int /*<<< orphan*/  ieee802_1x_create_preshared_mka (struct wpa_supplicant*,struct wpa_ssid*) ; 
 int /*<<< orphan*/  os_memset (struct eapol_config*,int /*<<< orphan*/ ,int) ; 
 struct wpabuf* wpa_bss_get_vendor_ie_multi (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_key_mgmt_wpa_ieee8021x (scalar_t__) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 scalar_t__ wps_is_20 (struct wpabuf*) ; 

void wpa_supplicant_initiate_eapol(struct wpa_supplicant *wpa_s)
{
#ifdef IEEE8021X_EAPOL
	struct eapol_config eapol_conf;
	struct wpa_ssid *ssid = wpa_s->current_ssid;

#ifdef CONFIG_IBSS_RSN
	if (ssid->mode == WPAS_MODE_IBSS &&
	    wpa_s->key_mgmt != WPA_KEY_MGMT_NONE &&
	    wpa_s->key_mgmt != WPA_KEY_MGMT_WPA_NONE) {
		/*
		 * RSN IBSS authentication is per-STA and we can disable the
		 * per-BSSID EAPOL authentication.
		 */
		eapol_sm_notify_portControl(wpa_s->eapol, ForceAuthorized);
		eapol_sm_notify_eap_success(wpa_s->eapol, TRUE);
		eapol_sm_notify_eap_fail(wpa_s->eapol, FALSE);
		return;
	}
#endif /* CONFIG_IBSS_RSN */

	eapol_sm_notify_eap_success(wpa_s->eapol, FALSE);
	eapol_sm_notify_eap_fail(wpa_s->eapol, FALSE);

	if (wpa_s->key_mgmt == WPA_KEY_MGMT_NONE ||
	    wpa_s->key_mgmt == WPA_KEY_MGMT_WPA_NONE)
		eapol_sm_notify_portControl(wpa_s->eapol, ForceAuthorized);
	else
		eapol_sm_notify_portControl(wpa_s->eapol, Auto);

	os_memset(&eapol_conf, 0, sizeof(eapol_conf));
	if (wpa_s->key_mgmt == WPA_KEY_MGMT_IEEE8021X_NO_WPA) {
		eapol_conf.accept_802_1x_keys = 1;
		eapol_conf.required_keys = 0;
		if (ssid->eapol_flags & EAPOL_FLAG_REQUIRE_KEY_UNICAST) {
			eapol_conf.required_keys |= EAPOL_REQUIRE_KEY_UNICAST;
		}
		if (ssid->eapol_flags & EAPOL_FLAG_REQUIRE_KEY_BROADCAST) {
			eapol_conf.required_keys |=
				EAPOL_REQUIRE_KEY_BROADCAST;
		}

		if (wpa_s->drv_flags & WPA_DRIVER_FLAGS_WIRED)
			eapol_conf.required_keys = 0;
	}
	eapol_conf.fast_reauth = wpa_s->conf->fast_reauth;
	eapol_conf.workaround = ssid->eap_workaround;
	eapol_conf.eap_disabled =
		!wpa_key_mgmt_wpa_ieee8021x(wpa_s->key_mgmt) &&
		wpa_s->key_mgmt != WPA_KEY_MGMT_IEEE8021X_NO_WPA &&
		wpa_s->key_mgmt != WPA_KEY_MGMT_WPS;
	eapol_conf.external_sim = wpa_s->conf->external_sim;

#ifdef CONFIG_WPS
	if (wpa_s->key_mgmt == WPA_KEY_MGMT_WPS) {
		eapol_conf.wps |= EAPOL_LOCAL_WPS_IN_USE;
		if (wpa_s->current_bss) {
			struct wpabuf *ie;
			ie = wpa_bss_get_vendor_ie_multi(wpa_s->current_bss,
							 WPS_IE_VENDOR_TYPE);
			if (ie) {
				if (wps_is_20(ie))
					eapol_conf.wps |=
						EAPOL_PEER_IS_WPS20_AP;
				wpabuf_free(ie);
			}
		}
	}
#endif /* CONFIG_WPS */

	eapol_sm_notify_config(wpa_s->eapol, &ssid->eap, &eapol_conf);

#ifdef CONFIG_MACSEC
	if (wpa_s->key_mgmt == WPA_KEY_MGMT_NONE && ssid->mka_psk_set)
		ieee802_1x_create_preshared_mka(wpa_s, ssid);
	else
		ieee802_1x_alloc_kay_sm(wpa_s, ssid);
#endif /* CONFIG_MACSEC */
#endif /* IEEE8021X_EAPOL */
}