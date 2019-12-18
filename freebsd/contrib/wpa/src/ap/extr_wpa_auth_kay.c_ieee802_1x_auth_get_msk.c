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
typedef  int /*<<< orphan*/  u8 ;
struct sta_info {int /*<<< orphan*/  eapol_sm; } ;
struct hostapd_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/ * ieee802_1x_get_key (int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int ieee802_1x_auth_get_msk(struct hostapd_data *hapd,
				   struct sta_info *sta, u8 *msk, size_t *len)
{
	const u8 *key;
	size_t keylen;

	if (!sta->eapol_sm)
		return -1;

	key = ieee802_1x_get_key(sta->eapol_sm, &keylen);
	if (key == NULL) {
		wpa_printf(MSG_DEBUG,
			   "MACsec: Failed to get MSK from EAPOL state machines");
		return -1;
	}
	wpa_printf(MSG_DEBUG, "MACsec: Successfully fetched key (len=%lu)",
		   (unsigned long) keylen);
	wpa_hexdump_key(MSG_DEBUG, "MSK: ", key, keylen);

	if (keylen > *len)
		keylen = *len;
	os_memcpy(msk, key, keylen);
	*len = keylen;

	return 0;
}