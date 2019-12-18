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
typedef  unsigned char u8 ;
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int EAP_SIM_KC_LEN ; 
 int /*<<< orphan*/  EAP_SIM_MK_LEN ; 
 size_t EAP_SIM_NONCE_MT_LEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  WPA_PUT_BE16 (unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sha1_vector (int,unsigned char const**,size_t*,unsigned char*) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,unsigned char*,int /*<<< orphan*/ ) ; 

void eap_sim_derive_mk(const u8 *identity, size_t identity_len,
		       const u8 *nonce_mt, u16 selected_version,
		       const u8 *ver_list, size_t ver_list_len,
		       int num_chal, const u8 *kc, u8 *mk)
{
	u8 sel_ver[2];
	const unsigned char *addr[5];
	size_t len[5];

	addr[0] = identity;
	len[0] = identity_len;
	addr[1] = kc;
	len[1] = num_chal * EAP_SIM_KC_LEN;
	addr[2] = nonce_mt;
	len[2] = EAP_SIM_NONCE_MT_LEN;
	addr[3] = ver_list;
	len[3] = ver_list_len;
	addr[4] = sel_ver;
	len[4] = 2;

	WPA_PUT_BE16(sel_ver, selected_version);

	/* MK = SHA1(Identity|n*Kc|NONCE_MT|Version List|Selected Version) */
	sha1_vector(5, addr, len, mk);
	wpa_hexdump_key(MSG_DEBUG, "EAP-SIM: MK", mk, EAP_SIM_MK_LEN);
}