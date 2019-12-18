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
struct TYPE_2__ {scalar_t__ prev_bssid_set; } ;
struct wpa_supplicant {int /*<<< orphan*/  pending_bssid; int /*<<< orphan*/  bssid; TYPE_1__ sme; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  WLAN_REASON_DEAUTH_LEAVING ; 
 int /*<<< orphan*/  WPA_DISCONNECTED ; 
 int /*<<< orphan*/  is_zero_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ wpa_drv_deauthenticate (struct wpa_supplicant*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_msg (struct wpa_supplicant*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpa_supplicant_set_state (struct wpa_supplicant*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpas_connection_failed (struct wpa_supplicant*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpas_notify_bssid_changed (struct wpa_supplicant*) ; 

__attribute__((used)) static void sme_deauth(struct wpa_supplicant *wpa_s)
{
	int bssid_changed;

	bssid_changed = !is_zero_ether_addr(wpa_s->bssid);

	if (wpa_drv_deauthenticate(wpa_s, wpa_s->pending_bssid,
				   WLAN_REASON_DEAUTH_LEAVING) < 0) {
		wpa_msg(wpa_s, MSG_INFO, "SME: Deauth request to the driver "
			"failed");
	}
	wpa_s->sme.prev_bssid_set = 0;

	wpas_connection_failed(wpa_s, wpa_s->pending_bssid);
	wpa_supplicant_set_state(wpa_s, WPA_DISCONNECTED);
	os_memset(wpa_s->bssid, 0, ETH_ALEN);
	os_memset(wpa_s->pending_bssid, 0, ETH_ALEN);
	if (bssid_changed)
		wpas_notify_bssid_changed(wpa_s);
}