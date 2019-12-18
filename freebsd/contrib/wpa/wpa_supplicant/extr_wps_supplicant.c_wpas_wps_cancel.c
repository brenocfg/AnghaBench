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
struct wpa_supplicant {scalar_t__ wpa_state; int own_disconnect_req; scalar_t__ after_wps; scalar_t__ ap_iface; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  WLAN_REASON_DEAUTH_LEAVING ; 
 scalar_t__ WPA_ASSOCIATED ; 
 scalar_t__ WPA_DISCONNECTED ; 
 scalar_t__ WPA_SCANNING ; 
 scalar_t__ eloop_cancel_timeout (int /*<<< orphan*/ ,struct wpa_supplicant*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int wpa_supplicant_ap_wps_cancel (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wpa_supplicant_cancel_scan (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wpa_supplicant_deauthenticate (struct wpa_supplicant*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpas_clear_wps (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wpas_wps_clear_ap_info (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wpas_wps_clear_timeout ; 
 int /*<<< orphan*/  wpas_wps_reenable_networks (struct wpa_supplicant*) ; 

int wpas_wps_cancel(struct wpa_supplicant *wpa_s)
{
#ifdef CONFIG_AP
	if (wpa_s->ap_iface) {
		wpa_printf(MSG_DEBUG, "WPS: Cancelling in AP mode");
		return wpa_supplicant_ap_wps_cancel(wpa_s);
	}
#endif /* CONFIG_AP */

	if (wpa_s->wpa_state == WPA_SCANNING ||
	    wpa_s->wpa_state == WPA_DISCONNECTED) {
		wpa_printf(MSG_DEBUG, "WPS: Cancel operation - cancel scan");
		wpa_supplicant_cancel_scan(wpa_s);
		wpas_clear_wps(wpa_s);
	} else if (wpa_s->wpa_state >= WPA_ASSOCIATED) {
		wpa_printf(MSG_DEBUG, "WPS: Cancel operation - "
			   "deauthenticate");
		wpa_s->own_disconnect_req = 1;
		wpa_supplicant_deauthenticate(wpa_s,
					      WLAN_REASON_DEAUTH_LEAVING);
		wpas_clear_wps(wpa_s);
	} else {
		wpas_wps_reenable_networks(wpa_s);
		wpas_wps_clear_ap_info(wpa_s);
		if (eloop_cancel_timeout(wpas_wps_clear_timeout, wpa_s, NULL) >
		    0)
			wpas_clear_wps(wpa_s);
	}

	wpa_s->after_wps = 0;

	return 0;
}