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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int EAP_EMSK_LEN ; 
 int EAP_SIM_KEYING_DATA_LEN ; 
 int EAP_SIM_K_AUT_LEN ; 
 int EAP_SIM_K_ENCR_LEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 scalar_t__ eap_sim_prf (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  os_memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

int eap_sim_derive_keys(const u8 *mk, u8 *k_encr, u8 *k_aut, u8 *msk, u8 *emsk)
{
	u8 buf[EAP_SIM_K_ENCR_LEN + EAP_SIM_K_AUT_LEN +
	       EAP_SIM_KEYING_DATA_LEN + EAP_EMSK_LEN], *pos;
	if (eap_sim_prf(mk, buf, sizeof(buf)) < 0) {
		wpa_printf(MSG_ERROR, "EAP-SIM: Failed to derive keys");
		return -1;
	}
	pos = buf;
	os_memcpy(k_encr, pos, EAP_SIM_K_ENCR_LEN);
	pos += EAP_SIM_K_ENCR_LEN;
	os_memcpy(k_aut, pos, EAP_SIM_K_AUT_LEN);
	pos += EAP_SIM_K_AUT_LEN;
	os_memcpy(msk, pos, EAP_SIM_KEYING_DATA_LEN);
	pos += EAP_SIM_KEYING_DATA_LEN;
	os_memcpy(emsk, pos, EAP_EMSK_LEN);

	wpa_hexdump_key(MSG_DEBUG, "EAP-SIM: K_encr",
			k_encr, EAP_SIM_K_ENCR_LEN);
	wpa_hexdump_key(MSG_DEBUG, "EAP-SIM: K_aut",
			k_aut, EAP_SIM_K_AUT_LEN);
	wpa_hexdump_key(MSG_DEBUG, "EAP-SIM: keying material (MSK)",
			msk, EAP_SIM_KEYING_DATA_LEN);
	wpa_hexdump_key(MSG_DEBUG, "EAP-SIM: EMSK", emsk, EAP_EMSK_LEN);
	os_memset(buf, 0, sizeof(buf));

	return 0;
}