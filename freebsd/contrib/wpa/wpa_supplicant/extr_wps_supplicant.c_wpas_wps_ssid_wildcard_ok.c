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
struct wpabuf {int dummy; } ;
struct wpa_supplicant {scalar_t__ scan_runs; int /*<<< orphan*/  own_addr; } ;
struct wpa_ssid {int /*<<< orphan*/  bssid; scalar_t__ bssid_set; int /*<<< orphan*/  eap; } ;
struct wpa_bss {scalar_t__ beacon_ie_len; int /*<<< orphan*/  bssid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  WPS_IE_VENDOR_TYPE ; 
 scalar_t__ WPS_PIN_SCAN_IGNORE_SEL_REG ; 
 scalar_t__ eap_is_wps_pbc_enrollee (int /*<<< orphan*/ *) ; 
 scalar_t__ eap_is_wps_pin_enrollee (int /*<<< orphan*/ *) ; 
 scalar_t__ os_memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct wpabuf* wpa_bss_get_vendor_ie_multi (struct wpa_bss*,int /*<<< orphan*/ ) ; 
 struct wpabuf* wpa_bss_get_vendor_ie_multi_beacon (struct wpa_bss*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 scalar_t__ wps_is_addr_authorized (struct wpabuf*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ wps_is_selected_pbc_registrar (struct wpabuf*) ; 
 scalar_t__ wps_validate_beacon (struct wpabuf*) ; 
 scalar_t__ wps_validate_beacon_probe_resp (struct wpabuf*,int,int /*<<< orphan*/ ) ; 

int wpas_wps_ssid_wildcard_ok(struct wpa_supplicant *wpa_s,
			      struct wpa_ssid *ssid,
			      struct wpa_bss *bss)
{
	struct wpabuf *wps_ie = NULL;
	int ret = 0;

	if (eap_is_wps_pbc_enrollee(&ssid->eap)) {
		wps_ie = wpa_bss_get_vendor_ie_multi(bss, WPS_IE_VENDOR_TYPE);
		if (wps_ie && wps_is_selected_pbc_registrar(wps_ie)) {
			/* allow wildcard SSID for WPS PBC */
			ret = 1;
		}
	} else if (eap_is_wps_pin_enrollee(&ssid->eap)) {
		wps_ie = wpa_bss_get_vendor_ie_multi(bss, WPS_IE_VENDOR_TYPE);
		if (wps_ie &&
		    (wps_is_addr_authorized(wps_ie, wpa_s->own_addr, 1) ||
		     wpa_s->scan_runs >= WPS_PIN_SCAN_IGNORE_SEL_REG)) {
			/* allow wildcard SSID for WPS PIN */
			ret = 1;
		}
	}

	if (!ret && ssid->bssid_set &&
	    os_memcmp(ssid->bssid, bss->bssid, ETH_ALEN) == 0) {
		/* allow wildcard SSID due to hardcoded BSSID match */
		ret = 1;
	}

#ifdef CONFIG_WPS_STRICT
	if (wps_ie) {
		if (wps_validate_beacon_probe_resp(wps_ie, bss->beacon_ie_len >
						   0, bss->bssid) < 0)
			ret = 0;
		if (bss->beacon_ie_len) {
			struct wpabuf *bcn_wps;
			bcn_wps = wpa_bss_get_vendor_ie_multi_beacon(
				bss, WPS_IE_VENDOR_TYPE);
			if (bcn_wps == NULL) {
				wpa_printf(MSG_DEBUG, "WPS: Mandatory WPS IE "
					   "missing from AP Beacon");
				ret = 0;
			} else {
				if (wps_validate_beacon(wps_ie) < 0)
					ret = 0;
				wpabuf_free(bcn_wps);
			}
		}
	}
#endif /* CONFIG_WPS_STRICT */

	wpabuf_free(wps_ie);

	return ret;
}