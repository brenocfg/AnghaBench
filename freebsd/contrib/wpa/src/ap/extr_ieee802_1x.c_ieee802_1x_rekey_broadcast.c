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
struct hostapd_data {TYPE_1__* conf; struct eapol_authenticator* eapol_auth; } ;
struct eapol_authenticator {int /*<<< orphan*/ * default_wep_key; } ;
struct TYPE_2__ {int default_wep_key_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * os_malloc (int) ; 
 scalar_t__ random_get_bytes (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int ieee802_1x_rekey_broadcast(struct hostapd_data *hapd)
{
	struct eapol_authenticator *eapol = hapd->eapol_auth;

	if (hapd->conf->default_wep_key_len < 1)
		return 0;

	os_free(eapol->default_wep_key);
	eapol->default_wep_key = os_malloc(hapd->conf->default_wep_key_len);
	if (eapol->default_wep_key == NULL ||
	    random_get_bytes(eapol->default_wep_key,
			     hapd->conf->default_wep_key_len)) {
		wpa_printf(MSG_INFO, "Could not generate random WEP key");
		os_free(eapol->default_wep_key);
		eapol->default_wep_key = NULL;
		return -1;
	}

	wpa_hexdump_key(MSG_DEBUG, "IEEE 802.1X: New default WEP key",
			eapol->default_wep_key,
			hapd->conf->default_wep_key_len);

	return 0;
}