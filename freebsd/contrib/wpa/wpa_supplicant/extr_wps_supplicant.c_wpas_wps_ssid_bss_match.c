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
struct wpa_supplicant {scalar_t__ scan_runs; int /*<<< orphan*/  wps_pin_start_time; int /*<<< orphan*/  own_addr; } ;
struct wpa_ssid {int key_mgmt; int /*<<< orphan*/  eap; } ;
struct wpa_bss {int dummy; } ;
struct os_reltime {scalar_t__ sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int WPA_KEY_MGMT_WPS ; 
 int /*<<< orphan*/  WPS_IE_VENDOR_TYPE ; 
 scalar_t__ WPS_PIN_SCAN_IGNORE_SEL_REG ; 
 scalar_t__ WPS_PIN_TIME_IGNORE_SEL_REG ; 
 scalar_t__ eap_is_wps_pbc_enrollee (int /*<<< orphan*/ *) ; 
 scalar_t__ eap_is_wps_pin_enrollee (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_reltime_age (int /*<<< orphan*/ *,struct os_reltime*) ; 
 struct wpabuf* wpa_bss_get_vendor_ie_multi (struct wpa_bss*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 int /*<<< orphan*/  wps_is_addr_authorized (struct wpabuf*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wps_is_selected_pbc_registrar (struct wpabuf*) ; 

int wpas_wps_ssid_bss_match(struct wpa_supplicant *wpa_s,
			    struct wpa_ssid *ssid, struct wpa_bss *bss)
{
	struct wpabuf *wps_ie;

	if (!(ssid->key_mgmt & WPA_KEY_MGMT_WPS))
		return -1;

	wps_ie = wpa_bss_get_vendor_ie_multi(bss, WPS_IE_VENDOR_TYPE);
	if (eap_is_wps_pbc_enrollee(&ssid->eap)) {
		if (!wps_ie) {
			wpa_printf(MSG_DEBUG, "   skip - non-WPS AP");
			return 0;
		}

		if (!wps_is_selected_pbc_registrar(wps_ie)) {
			wpa_printf(MSG_DEBUG, "   skip - WPS AP "
				   "without active PBC Registrar");
			wpabuf_free(wps_ie);
			return 0;
		}

		/* TODO: overlap detection */
		wpa_printf(MSG_DEBUG, "   selected based on WPS IE "
			   "(Active PBC)");
		wpabuf_free(wps_ie);
		return 1;
	}

	if (eap_is_wps_pin_enrollee(&ssid->eap)) {
		if (!wps_ie) {
			wpa_printf(MSG_DEBUG, "   skip - non-WPS AP");
			return 0;
		}

		/*
		 * Start with WPS APs that advertise our address as an
		 * authorized MAC (v2.0) or active PIN Registrar (v1.0) and
		 * allow any WPS AP after couple of scans since some APs do not
		 * set Selected Registrar attribute properly when using
		 * external Registrar.
		 */
		if (!wps_is_addr_authorized(wps_ie, wpa_s->own_addr, 1)) {
			struct os_reltime age;

			os_reltime_age(&wpa_s->wps_pin_start_time, &age);

			if (wpa_s->scan_runs < WPS_PIN_SCAN_IGNORE_SEL_REG ||
			    age.sec < WPS_PIN_TIME_IGNORE_SEL_REG) {
				wpa_printf(MSG_DEBUG,
					   "   skip - WPS AP without active PIN Registrar (scan_runs=%d age=%d)",
					   wpa_s->scan_runs, (int) age.sec);
				wpabuf_free(wps_ie);
				return 0;
			}
			wpa_printf(MSG_DEBUG, "   selected based on WPS IE");
		} else {
			wpa_printf(MSG_DEBUG, "   selected based on WPS IE "
				   "(Authorized MAC or Active PIN)");
		}
		wpabuf_free(wps_ie);
		return 1;
	}

	if (wps_ie) {
		wpa_printf(MSG_DEBUG, "   selected based on WPS IE");
		wpabuf_free(wps_ie);
		return 1;
	}

	return -1;
}