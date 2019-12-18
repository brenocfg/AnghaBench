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
struct wpa_supplicant {unsigned int drv_enc; scalar_t__ drv_capa_known; scalar_t__ p2p_mgmt; } ;
struct wpa_ssid {size_t* wep_key_len; scalar_t__ ssid_len; int /*<<< orphan*/  mem_only_psk; scalar_t__ sae_password; int /*<<< orphan*/  key_mgmt; int /*<<< orphan*/  ext_psk; int /*<<< orphan*/  passphrase; int /*<<< orphan*/  psk_set; scalar_t__ disabled; } ;

/* Variables and functions */
 int NUM_WEP_KEYS ; 
 unsigned int WPA_DRIVER_CAPA_ENC_WEP104 ; 
 unsigned int WPA_DRIVER_CAPA_ENC_WEP128 ; 
 unsigned int WPA_DRIVER_CAPA_ENC_WEP40 ; 
 scalar_t__ wpa_key_mgmt_sae (int /*<<< orphan*/ ) ; 
 scalar_t__ wpa_key_mgmt_wpa_psk (int /*<<< orphan*/ ) ; 

int wpas_network_disabled(struct wpa_supplicant *wpa_s, struct wpa_ssid *ssid)
{
	int i;
	unsigned int drv_enc;

	if (wpa_s->p2p_mgmt)
		return 1; /* no normal network profiles on p2p_mgmt interface */

	if (ssid == NULL)
		return 1;

	if (ssid->disabled)
		return 1;

	if (wpa_s->drv_capa_known)
		drv_enc = wpa_s->drv_enc;
	else
		drv_enc = (unsigned int) -1;

	for (i = 0; i < NUM_WEP_KEYS; i++) {
		size_t len = ssid->wep_key_len[i];
		if (len == 0)
			continue;
		if (len == 5 && (drv_enc & WPA_DRIVER_CAPA_ENC_WEP40))
			continue;
		if (len == 13 && (drv_enc & WPA_DRIVER_CAPA_ENC_WEP104))
			continue;
		if (len == 16 && (drv_enc & WPA_DRIVER_CAPA_ENC_WEP128))
			continue;
		return 1; /* invalid WEP key */
	}

	if (wpa_key_mgmt_wpa_psk(ssid->key_mgmt) && !ssid->psk_set &&
	    (!ssid->passphrase || ssid->ssid_len != 0) && !ssid->ext_psk &&
	    !(wpa_key_mgmt_sae(ssid->key_mgmt) && ssid->sae_password) &&
	    !ssid->mem_only_psk)
		return 1;

	return 0;
}