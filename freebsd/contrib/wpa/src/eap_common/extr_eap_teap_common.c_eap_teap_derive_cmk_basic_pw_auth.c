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
typedef  int /*<<< orphan*/  imck ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_TEAP_CMK_LEN ; 
 int EAP_TEAP_IMCK_LEN ; 
 size_t EAP_TEAP_SIMCK_LEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int eap_teap_tls_prf (int /*<<< orphan*/  const*,size_t,char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  forced_memzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int eap_teap_derive_cmk_basic_pw_auth(const u8 *s_imck_msk, u8 *cmk)
{
	u8 imsk[32], imck[EAP_TEAP_IMCK_LEN];
	int res;

	/* FIX: The Basic-Password-Auth (i.e., no inner EAP) case is
	 * not fully defined in RFC 7170, so this CMK derivation may
	 * need to be changed if a fixed definition is eventually
	 * published. For now, derive CMK[0] based on S-IMCK[0] and
	 * IMSK of 32 octets of zeros. */
	os_memset(imsk, 0, 32);
	res = eap_teap_tls_prf(s_imck_msk, EAP_TEAP_SIMCK_LEN,
			       "Inner Methods Compound Keys",
			       imsk, 32, imck, sizeof(imck));
	if (res < 0)
		return -1;
	os_memcpy(cmk, &imck[EAP_TEAP_SIMCK_LEN], EAP_TEAP_CMK_LEN);
	wpa_hexdump_key(MSG_DEBUG, "EAP-TEAP: CMK[no-inner-EAP]",
			cmk, EAP_TEAP_CMK_LEN);
	forced_memzero(imck, sizeof(imck));
	return 0;
}