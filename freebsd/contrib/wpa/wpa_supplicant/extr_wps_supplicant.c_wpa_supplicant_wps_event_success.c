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
struct wpa_supplicant {int wps_success; int /*<<< orphan*/  bssid; scalar_t__ extra_blacklist_count; scalar_t__ current_ssid; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  WPS_EVENT_SUCCESS ; 
 int /*<<< orphan*/  eloop_register_timeout (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wpa_supplicant*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_msg (struct wpa_supplicant*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpas_clear_temp_disabled (struct wpa_supplicant*,scalar_t__,int) ; 
 int /*<<< orphan*/  wpas_notify_wps_event_success (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wpas_p2p_wps_success (struct wpa_supplicant*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpas_wps_reenable_networks_cb ; 

__attribute__((used)) static void wpa_supplicant_wps_event_success(struct wpa_supplicant *wpa_s)
{
	wpa_msg(wpa_s, MSG_INFO, WPS_EVENT_SUCCESS);
	wpa_s->wps_success = 1;
	wpas_notify_wps_event_success(wpa_s);
	if (wpa_s->current_ssid)
		wpas_clear_temp_disabled(wpa_s, wpa_s->current_ssid, 1);
	wpa_s->extra_blacklist_count = 0;

	/*
	 * Enable the networks disabled during wpas_wps_reassoc after 10
	 * seconds. The 10 seconds timer is to allow the data connection to be
	 * formed before allowing other networks to be selected.
	 */
	eloop_register_timeout(10, 0, wpas_wps_reenable_networks_cb, wpa_s,
			       NULL);

	wpas_p2p_wps_success(wpa_s, wpa_s->bssid, 0);
}