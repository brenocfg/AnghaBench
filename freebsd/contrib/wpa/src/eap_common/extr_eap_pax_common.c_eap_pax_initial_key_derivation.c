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
typedef  int /*<<< orphan*/  const u8 ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_PAX_AK_LEN ; 
 int /*<<< orphan*/  EAP_PAX_CK_LEN ; 
 int /*<<< orphan*/  EAP_PAX_ICK_LEN ; 
 int /*<<< orphan*/  EAP_PAX_MID_LEN ; 
 int /*<<< orphan*/  EAP_PAX_MK_LEN ; 
 int EAP_PAX_RAND_LEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 scalar_t__ eap_pax_kdf (int /*<<< orphan*/  const,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

int eap_pax_initial_key_derivation(u8 mac_id, const u8 *ak, const u8 *e,
				   u8 *mk, u8 *ck, u8 *ick, u8 *mid)
{
	wpa_printf(MSG_DEBUG, "EAP-PAX: initial key derivation");
	if (eap_pax_kdf(mac_id, ak, EAP_PAX_AK_LEN, "Master Key",
			e, 2 * EAP_PAX_RAND_LEN, EAP_PAX_MK_LEN, mk) ||
	    eap_pax_kdf(mac_id, mk, EAP_PAX_MK_LEN, "Confirmation Key",
			e, 2 * EAP_PAX_RAND_LEN, EAP_PAX_CK_LEN, ck) ||
	    eap_pax_kdf(mac_id, mk, EAP_PAX_MK_LEN, "Integrity Check Key",
			e, 2 * EAP_PAX_RAND_LEN, EAP_PAX_ICK_LEN, ick) ||
	    eap_pax_kdf(mac_id, mk, EAP_PAX_MK_LEN, "Method ID",
			e, 2 * EAP_PAX_RAND_LEN, EAP_PAX_MID_LEN, mid))
		return -1;

	wpa_hexdump_key(MSG_MSGDUMP, "EAP-PAX: AK", ak, EAP_PAX_AK_LEN);
	wpa_hexdump_key(MSG_MSGDUMP, "EAP-PAX: MK", mk, EAP_PAX_MK_LEN);
	wpa_hexdump_key(MSG_MSGDUMP, "EAP-PAX: CK", ck, EAP_PAX_CK_LEN);
	wpa_hexdump_key(MSG_MSGDUMP, "EAP-PAX: ICK", ick, EAP_PAX_ICK_LEN);
	wpa_hexdump_key(MSG_MSGDUMP, "EAP-PAX: MID", mid, EAP_PAX_MID_LEN);

	return 0;
}