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
typedef  scalar_t__ u8 ;
struct wps_credential {int /*<<< orphan*/  mac_addr; } ;
struct wpa_supplicant {TYPE_1__* conf; int /*<<< orphan*/  bssid; } ;
struct wpa_ssid {int proto; int pairwise_cipher; int /*<<< orphan*/  ssid_len; int /*<<< orphan*/ * ssid; } ;
struct wpa_ie_data {int pairwise_cipher; } ;
struct wpa_driver_capa {int key_mgmt; int enc; } ;
struct wpa_bss {int dummy; } ;
struct TYPE_2__ {int ap_scan; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  WLAN_EID_RSN ; 
 int WPA_CIPHER_CCMP ; 
 int WPA_CIPHER_TKIP ; 
 int WPA_DRIVER_CAPA_ENC_CCMP ; 
 int WPA_DRIVER_CAPA_KEY_MGMT_WPA2_PSK ; 
 int /*<<< orphan*/  WPA_IE_VENDOR_TYPE ; 
 int WPA_PROTO_RSN ; 
 int WPA_PROTO_WPA ; 
 struct wpa_bss* wpa_bss_get (struct wpa_supplicant*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__* wpa_bss_get_ie (struct wpa_bss*,int /*<<< orphan*/ ) ; 
 scalar_t__* wpa_bss_get_vendor_ie (struct wpa_bss*,int /*<<< orphan*/ ) ; 
 scalar_t__ wpa_drv_get_capa (struct wpa_supplicant*,struct wpa_driver_capa*) ; 
 scalar_t__ wpa_parse_wpa_ie (scalar_t__ const*,scalar_t__ const,struct wpa_ie_data*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void wpas_wps_security_workaround(struct wpa_supplicant *wpa_s,
					 struct wpa_ssid *ssid,
					 const struct wps_credential *cred)
{
	struct wpa_driver_capa capa;
	struct wpa_bss *bss;
	const u8 *ie;
	struct wpa_ie_data adv;
	int wpa2 = 0, ccmp = 0;

	/*
	 * Many existing WPS APs do not know how to negotiate WPA2 or CCMP in
	 * case they are configured for mixed mode operation (WPA+WPA2 and
	 * TKIP+CCMP). Try to use scan results to figure out whether the AP
	 * actually supports stronger security and select that if the client
	 * has support for it, too.
	 */

	if (wpa_drv_get_capa(wpa_s, &capa))
		return; /* Unknown what driver supports */

	if (ssid->ssid == NULL)
		return;
	bss = wpa_bss_get(wpa_s, cred->mac_addr, ssid->ssid, ssid->ssid_len);
	if (!bss)
		bss = wpa_bss_get(wpa_s, wpa_s->bssid,
				  ssid->ssid, ssid->ssid_len);
	if (bss == NULL) {
		wpa_printf(MSG_DEBUG, "WPS: The AP was not found from BSS "
			   "table - use credential as-is");
		return;
	}

	wpa_printf(MSG_DEBUG, "WPS: AP found from BSS table");

	ie = wpa_bss_get_ie(bss, WLAN_EID_RSN);
	if (ie && wpa_parse_wpa_ie(ie, 2 + ie[1], &adv) == 0) {
		wpa2 = 1;
		if (adv.pairwise_cipher & WPA_CIPHER_CCMP)
			ccmp = 1;
	} else {
		ie = wpa_bss_get_vendor_ie(bss, WPA_IE_VENDOR_TYPE);
		if (ie && wpa_parse_wpa_ie(ie, 2 + ie[1], &adv) == 0 &&
		    adv.pairwise_cipher & WPA_CIPHER_CCMP)
			ccmp = 1;
	}

	if (ie == NULL && (ssid->proto & WPA_PROTO_WPA) &&
	    (ssid->pairwise_cipher & WPA_CIPHER_TKIP)) {
		/*
		 * TODO: This could be the initial AP configuration and the
		 * Beacon contents could change shortly. Should request a new
		 * scan and delay addition of the network until the updated
		 * scan results are available.
		 */
		wpa_printf(MSG_DEBUG, "WPS: The AP did not yet advertise WPA "
			   "support - use credential as-is");
		return;
	}

	if (ccmp && !(ssid->pairwise_cipher & WPA_CIPHER_CCMP) &&
	    (ssid->pairwise_cipher & WPA_CIPHER_TKIP) &&
	    (capa.key_mgmt & WPA_DRIVER_CAPA_KEY_MGMT_WPA2_PSK)) {
		wpa_printf(MSG_DEBUG, "WPS: Add CCMP into the credential "
			   "based on scan results");
		if (wpa_s->conf->ap_scan == 1)
			ssid->pairwise_cipher |= WPA_CIPHER_CCMP;
		else
			ssid->pairwise_cipher = WPA_CIPHER_CCMP;
	}

	if (wpa2 && !(ssid->proto & WPA_PROTO_RSN) &&
	    (ssid->proto & WPA_PROTO_WPA) &&
	    (capa.enc & WPA_DRIVER_CAPA_ENC_CCMP)) {
		wpa_printf(MSG_DEBUG, "WPS: Add WPA2 into the credential "
			   "based on scan results");
		if (wpa_s->conf->ap_scan == 1)
			ssid->proto |= WPA_PROTO_RSN;
		else
			ssid->proto = WPA_PROTO_RSN;
	}
}