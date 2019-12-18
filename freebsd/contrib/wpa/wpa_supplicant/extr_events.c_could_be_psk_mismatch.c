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
typedef  scalar_t__ u16 ;
struct wpa_supplicant {scalar_t__ wpa_state; int /*<<< orphan*/  key_mgmt; } ;

/* Variables and functions */
 scalar_t__ WLAN_REASON_IE_IN_4WAY_DIFFERS ; 
 scalar_t__ WPA_4WAY_HANDSHAKE ; 
 int /*<<< orphan*/  wpa_key_mgmt_wpa_psk (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int could_be_psk_mismatch(struct wpa_supplicant *wpa_s, u16 reason_code,
				 int locally_generated)
{
	if (wpa_s->wpa_state != WPA_4WAY_HANDSHAKE ||
	    !wpa_key_mgmt_wpa_psk(wpa_s->key_mgmt))
		return 0; /* Not in 4-way handshake with PSK */

	/*
	 * It looks like connection was lost while trying to go through PSK
	 * 4-way handshake. Filter out known disconnection cases that are caused
	 * by something else than PSK mismatch to avoid confusing reports.
	 */

	if (locally_generated) {
		if (reason_code == WLAN_REASON_IE_IN_4WAY_DIFFERS)
			return 0;
	}

	return 1;
}