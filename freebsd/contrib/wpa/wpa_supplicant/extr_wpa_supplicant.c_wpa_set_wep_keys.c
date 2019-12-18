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
struct wpa_supplicant {int dummy; } ;
struct wpa_ssid {scalar_t__* wep_key_len; int wep_tx_keyidx; int /*<<< orphan*/ * wep_key; } ;

/* Variables and functions */
 int NUM_WEP_KEYS ; 
 int /*<<< orphan*/  WPA_ALG_WEP ; 
 int /*<<< orphan*/  wpa_drv_set_key (struct wpa_supplicant*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

int wpa_set_wep_keys(struct wpa_supplicant *wpa_s, struct wpa_ssid *ssid)
{
	int i, set = 0;

	for (i = 0; i < NUM_WEP_KEYS; i++) {
		if (ssid->wep_key_len[i] == 0)
			continue;

		set = 1;
		wpa_drv_set_key(wpa_s, WPA_ALG_WEP, NULL,
				i, i == ssid->wep_tx_keyidx, NULL, 0,
				ssid->wep_key[i], ssid->wep_key_len[i]);
	}

	return set;
}