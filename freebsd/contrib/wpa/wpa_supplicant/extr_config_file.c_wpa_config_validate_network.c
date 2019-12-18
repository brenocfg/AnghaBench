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
struct wpa_ssid {int disabled; int p2p_persistent_group; int group_cipher; int pairwise_cipher; scalar_t__ mode; scalar_t__ key_mgmt; scalar_t__ ieee80211w; scalar_t__ ocv; scalar_t__ psk_set; scalar_t__ passphrase; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 scalar_t__ NO_MGMT_FRAME_PROTECTION ; 
 scalar_t__ WPAS_MODE_MESH ; 
 int WPA_CIPHER_CCMP ; 
 int WPA_CIPHER_CCMP_256 ; 
 int WPA_CIPHER_GCMP ; 
 int WPA_CIPHER_GCMP_256 ; 
 int WPA_CIPHER_NONE ; 
 scalar_t__ WPA_KEY_MGMT_NONE ; 
 scalar_t__ WPA_KEY_MGMT_SAE ; 
 int /*<<< orphan*/  wpa_config_update_psk (struct wpa_ssid*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int wpa_config_validate_network(struct wpa_ssid *ssid, int line)
{
	int errors = 0;

	if (ssid->passphrase) {
		if (ssid->psk_set) {
			wpa_printf(MSG_ERROR, "Line %d: both PSK and "
				   "passphrase configured.", line);
			errors++;
		}
		wpa_config_update_psk(ssid);
	}

	if (ssid->disabled == 2)
		ssid->p2p_persistent_group = 1;

	if ((ssid->group_cipher & WPA_CIPHER_CCMP) &&
	    !(ssid->pairwise_cipher & (WPA_CIPHER_CCMP | WPA_CIPHER_CCMP_256 |
				       WPA_CIPHER_GCMP | WPA_CIPHER_GCMP_256 |
				       WPA_CIPHER_NONE))) {
		/* Group cipher cannot be stronger than the pairwise cipher. */
		wpa_printf(MSG_DEBUG, "Line %d: removed CCMP from group cipher"
			   " list since it was not allowed for pairwise "
			   "cipher", line);
		ssid->group_cipher &= ~WPA_CIPHER_CCMP;
	}

	if (ssid->mode == WPAS_MODE_MESH &&
	    (ssid->key_mgmt != WPA_KEY_MGMT_NONE &&
	    ssid->key_mgmt != WPA_KEY_MGMT_SAE)) {
		wpa_printf(MSG_ERROR,
			   "Line %d: key_mgmt for mesh network should be open or SAE",
			   line);
		errors++;
	}

#ifdef CONFIG_OCV
	if (ssid->ocv && ssid->ieee80211w == NO_MGMT_FRAME_PROTECTION) {
		wpa_printf(MSG_ERROR,
			   "Line %d: PMF needs to be enabled whenever using OCV",
			   line);
		errors++;
	}
#endif /* CONFIG_OCV */

	return errors;
}