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
struct wpa_supplicant {scalar_t__ wpa_state; int /*<<< orphan*/  eapol; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ WPA_ASSOCIATED ; 
 int /*<<< orphan*/  WPA_COMPLETED ; 
 int /*<<< orphan*/  eapol_sm_notify_eap_success (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eapol_sm_notify_portValid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_supplicant_cancel_auth_timeout (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wpa_supplicant_set_state (struct wpa_supplicant*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wpa_supplicant_event_port_authorized(struct wpa_supplicant *wpa_s)
{
	if (wpa_s->wpa_state == WPA_ASSOCIATED) {
		wpa_supplicant_cancel_auth_timeout(wpa_s);
		wpa_supplicant_set_state(wpa_s, WPA_COMPLETED);
		eapol_sm_notify_portValid(wpa_s->eapol, TRUE);
		eapol_sm_notify_eap_success(wpa_s->eapol, TRUE);
	}
}