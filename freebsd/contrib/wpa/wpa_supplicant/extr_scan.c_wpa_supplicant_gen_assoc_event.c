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
typedef  union wpa_event_data {int dummy; } wpa_event_data ;
struct wpa_supplicant {struct wpa_ssid* current_ssid; } ;
struct wpa_ssid {int dummy; } ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_ASSOC ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  os_memset (union wpa_event_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_dbg (struct wpa_supplicant*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpa_supplicant_event (struct wpa_supplicant*,int /*<<< orphan*/ ,union wpa_event_data*) ; 
 struct wpa_ssid* wpa_supplicant_get_ssid (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wpa_supplicant_initiate_eapol (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wpas_notify_network_changed (struct wpa_supplicant*) ; 

__attribute__((used)) static void wpa_supplicant_gen_assoc_event(struct wpa_supplicant *wpa_s)
{
	struct wpa_ssid *ssid;
	union wpa_event_data data;

	ssid = wpa_supplicant_get_ssid(wpa_s);
	if (ssid == NULL)
		return;

	if (wpa_s->current_ssid == NULL) {
		wpa_s->current_ssid = ssid;
		wpas_notify_network_changed(wpa_s);
	}
	wpa_supplicant_initiate_eapol(wpa_s);
	wpa_dbg(wpa_s, MSG_DEBUG, "Already associated with a configured "
		"network - generating associated event");
	os_memset(&data, 0, sizeof(data));
	wpa_supplicant_event(wpa_s, EVENT_ASSOC, &data);
}