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
struct wpa_supplicant {int /*<<< orphan*/  wpa; int /*<<< orphan*/  current_bss; TYPE_1__* current_ssid; } ;
struct TYPE_2__ {int /*<<< orphan*/  key_mgmt; } ;

/* Variables and functions */
 int /*<<< orphan*/  WLAN_EID_RSN ; 
 int /*<<< orphan*/  WPA_IE_VENDOR_TYPE ; 
 scalar_t__* wpa_bss_get_ie (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__* wpa_bss_get_vendor_ie (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_key_mgmt_wpa_any (int /*<<< orphan*/ ) ; 
 scalar_t__ wpa_sm_set_ap_rsn_ie (int /*<<< orphan*/ ,scalar_t__ const*,scalar_t__ const) ; 
 scalar_t__ wpa_sm_set_ap_wpa_ie (int /*<<< orphan*/ ,scalar_t__ const*,scalar_t__ const) ; 

__attribute__((used)) static int wpa_supplicant_assoc_update_ie(struct wpa_supplicant *wpa_s)
{
	const u8 *bss_wpa = NULL, *bss_rsn = NULL;

	if (!wpa_s->current_bss || !wpa_s->current_ssid)
		return -1;

	if (!wpa_key_mgmt_wpa_any(wpa_s->current_ssid->key_mgmt))
		return 0;

	bss_wpa = wpa_bss_get_vendor_ie(wpa_s->current_bss,
					WPA_IE_VENDOR_TYPE);
	bss_rsn = wpa_bss_get_ie(wpa_s->current_bss, WLAN_EID_RSN);

	if (wpa_sm_set_ap_wpa_ie(wpa_s->wpa, bss_wpa,
				 bss_wpa ? 2 + bss_wpa[1] : 0) ||
	    wpa_sm_set_ap_rsn_ie(wpa_s->wpa, bss_rsn,
				 bss_rsn ? 2 + bss_rsn[1] : 0))
		return -1;

	return 0;
}