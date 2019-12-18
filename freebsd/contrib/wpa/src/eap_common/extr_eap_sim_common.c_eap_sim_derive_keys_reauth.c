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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u16 ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int EAP_EMSK_LEN ; 
 int EAP_SIM_KEYING_DATA_LEN ; 
 size_t EAP_SIM_MK_LEN ; 
 int EAP_SIM_NONCE_S_LEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int SHA1_MAC_LEN ; 
 int /*<<< orphan*/  WPA_PUT_BE16 (scalar_t__*,int /*<<< orphan*/ ) ; 
 scalar_t__ eap_sim_prf (scalar_t__*,scalar_t__*,int) ; 
 int /*<<< orphan*/  os_memcpy (scalar_t__*,scalar_t__*,int) ; 
 int /*<<< orphan*/  os_memset (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sha1_vector (int,scalar_t__ const**,size_t*,scalar_t__*) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,scalar_t__ const*,int) ; 
 int /*<<< orphan*/  wpa_hexdump_ascii (int /*<<< orphan*/ ,char*,scalar_t__ const*,size_t) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,scalar_t__ const*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

int eap_sim_derive_keys_reauth(u16 _counter,
			       const u8 *identity, size_t identity_len,
			       const u8 *nonce_s, const u8 *mk, u8 *msk,
			       u8 *emsk)
{
	u8 xkey[SHA1_MAC_LEN];
	u8 buf[EAP_SIM_KEYING_DATA_LEN + EAP_EMSK_LEN + 32];
	u8 counter[2];
	const u8 *addr[4];
	size_t len[4];

	while (identity_len > 0 && identity[identity_len - 1] == 0) {
		wpa_printf(MSG_DEBUG, "EAP-SIM: Workaround - drop null "
			   "character from the end of identity");
		identity_len--;
	}
	addr[0] = identity;
	len[0] = identity_len;
	addr[1] = counter;
	len[1] = 2;
	addr[2] = nonce_s;
	len[2] = EAP_SIM_NONCE_S_LEN;
	addr[3] = mk;
	len[3] = EAP_SIM_MK_LEN;

	WPA_PUT_BE16(counter, _counter);

	wpa_printf(MSG_DEBUG, "EAP-SIM: Deriving keying data from reauth");
	wpa_hexdump_ascii(MSG_DEBUG, "EAP-SIM: Identity",
			  identity, identity_len);
	wpa_hexdump(MSG_DEBUG, "EAP-SIM: counter", counter, 2);
	wpa_hexdump(MSG_DEBUG, "EAP-SIM: NONCE_S", nonce_s,
		    EAP_SIM_NONCE_S_LEN);
	wpa_hexdump_key(MSG_DEBUG, "EAP-SIM: MK", mk, EAP_SIM_MK_LEN);

	/* XKEY' = SHA1(Identity|counter|NONCE_S|MK) */
	sha1_vector(4, addr, len, xkey);
	wpa_hexdump(MSG_DEBUG, "EAP-SIM: XKEY'", xkey, SHA1_MAC_LEN);

	if (eap_sim_prf(xkey, buf, sizeof(buf)) < 0) {
		wpa_printf(MSG_ERROR, "EAP-SIM: Failed to derive keys");
		return -1;
	}
	if (msk) {
		os_memcpy(msk, buf, EAP_SIM_KEYING_DATA_LEN);
		wpa_hexdump(MSG_DEBUG, "EAP-SIM: keying material (MSK)",
			    msk, EAP_SIM_KEYING_DATA_LEN);
	}
	if (emsk) {
		os_memcpy(emsk, buf + EAP_SIM_KEYING_DATA_LEN, EAP_EMSK_LEN);
		wpa_hexdump(MSG_DEBUG, "EAP-SIM: EMSK", emsk, EAP_EMSK_LEN);
	}
	os_memset(buf, 0, sizeof(buf));

	return 0;
}