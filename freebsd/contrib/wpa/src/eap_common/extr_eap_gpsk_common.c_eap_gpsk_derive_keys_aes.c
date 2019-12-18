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
typedef  int /*<<< orphan*/  kdf_out ;

/* Variables and functions */
 scalar_t__ EAP_EMSK_LEN ; 
 int /*<<< orphan*/  EAP_GPSK_CIPHER_AES ; 
 size_t EAP_GPSK_PK_LEN_AES ; 
 size_t EAP_GPSK_SK_LEN_AES ; 
 scalar_t__ EAP_MSK_LEN ; 
 int eap_gpsk_derive_keys_helper (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static int eap_gpsk_derive_keys_aes(const u8 *psk, size_t psk_len,
				    const u8 *seed, size_t seed_len,
				    u8 *msk, u8 *emsk, u8 *sk, size_t *sk_len,
				    u8 *pk, size_t *pk_len)
{
#define EAP_GPSK_SK_LEN_AES 16
#define EAP_GPSK_PK_LEN_AES 16
	u8 kdf_out[EAP_MSK_LEN + EAP_EMSK_LEN + EAP_GPSK_SK_LEN_AES +
		   EAP_GPSK_PK_LEN_AES];

	/*
	 * inputString = RAND_Peer || ID_Peer || RAND_Server || ID_Server
	 *            (= seed)
	 * KS = 16, PL = psk_len, CSuite_Sel = 0x00000000 0x0001
	 * MK = GKDF-16 (PSK[0..15], PL || PSK || CSuite_Sel || inputString)
	 * MSK = GKDF-160 (MK, inputString)[0..63]
	 * EMSK = GKDF-160 (MK, inputString)[64..127]
	 * SK = GKDF-160 (MK, inputString)[128..143]
	 * PK = GKDF-160 (MK, inputString)[144..159]
	 * zero = 0x00 || 0x00 || ... || 0x00 (16 times)
	 * Method-ID = GKDF-16 (zero, "Method ID" || EAP_Method_Type ||
	 *                      CSuite_Sel || inputString)
	 */

	*sk_len = EAP_GPSK_SK_LEN_AES;
	*pk_len = EAP_GPSK_PK_LEN_AES;

	return eap_gpsk_derive_keys_helper(EAP_GPSK_CIPHER_AES,
					   kdf_out, sizeof(kdf_out),
					   psk, psk_len, seed, seed_len,
					   msk, emsk, sk, *sk_len,
					   pk, *pk_len);
}