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
struct wpa_supplicant {TYPE_1__* conf; int /*<<< orphan*/  own_addr; } ;
struct wpa_ssid {int key_mgmt; scalar_t__ ssid_len; int /*<<< orphan*/  eap; int /*<<< orphan*/  ssid; struct wpa_ssid* next; } ;
struct wpa_bss {scalar_t__ ssid_len; int /*<<< orphan*/  ssid; } ;
struct TYPE_2__ {struct wpa_ssid* ssid; } ;

/* Variables and functions */
 int WPA_KEY_MGMT_WPS ; 
 int /*<<< orphan*/  WPS_IE_VENDOR_TYPE ; 
 int eap_is_wps_pbc_enrollee (int /*<<< orphan*/ *) ; 
 int eap_is_wps_pin_enrollee (int /*<<< orphan*/ *) ; 
 scalar_t__ os_memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 struct wpabuf* wpa_bss_get_vendor_ie_multi (struct wpa_bss*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 int /*<<< orphan*/  wps_is_addr_authorized (struct wpabuf*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ wps_is_selected_pbc_registrar (struct wpabuf*) ; 

__attribute__((used)) static int wpa_bss_is_wps_candidate(struct wpa_supplicant *wpa_s,
				    struct wpa_bss *bss)
{
#ifdef CONFIG_WPS
	struct wpa_ssid *ssid;
	struct wpabuf *wps_ie;
	int pbc = 0, ret;

	wps_ie = wpa_bss_get_vendor_ie_multi(bss, WPS_IE_VENDOR_TYPE);
	if (!wps_ie)
		return 0;

	if (wps_is_selected_pbc_registrar(wps_ie)) {
		pbc = 1;
	} else if (!wps_is_addr_authorized(wps_ie, wpa_s->own_addr, 1)) {
		wpabuf_free(wps_ie);
		return 0;
	}

	for (ssid = wpa_s->conf->ssid; ssid; ssid = ssid->next) {
		if (!(ssid->key_mgmt & WPA_KEY_MGMT_WPS))
			continue;
		if (ssid->ssid_len &&
		    (ssid->ssid_len != bss->ssid_len ||
		     os_memcmp(ssid->ssid, bss->ssid, ssid->ssid_len) != 0))
			continue;

		if (pbc)
			ret = eap_is_wps_pbc_enrollee(&ssid->eap);
		else
			ret = eap_is_wps_pin_enrollee(&ssid->eap);
		wpabuf_free(wps_ie);
		return ret;
	}
	wpabuf_free(wps_ie);
#endif /* CONFIG_WPS */

	return 0;
}