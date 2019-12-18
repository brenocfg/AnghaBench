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
struct ikev2_keys {int /*<<< orphan*/  SK_d_len; int /*<<< orphan*/ * SK_d; } ;

/* Variables and functions */
 scalar_t__ EAP_EMSK_LEN ; 
 scalar_t__ EAP_MSK_LEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ ikev2_prf_plus (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * os_malloc (size_t) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,scalar_t__) ; 

int eap_ikev2_derive_keymat(int prf, struct ikev2_keys *keys,
			    const u8 *i_nonce, size_t i_nonce_len,
			    const u8 *r_nonce, size_t r_nonce_len,
			    u8 *keymat)
{
	u8 *nonces;
	size_t nlen;

	/* KEYMAT = prf+(SK_d, Ni | Nr) */
	if (keys->SK_d == NULL || i_nonce == NULL || r_nonce == NULL)
		return -1;

	nlen = i_nonce_len + r_nonce_len;
	nonces = os_malloc(nlen);
	if (nonces == NULL)
		return -1;
	os_memcpy(nonces, i_nonce, i_nonce_len);
	os_memcpy(nonces + i_nonce_len, r_nonce, r_nonce_len);

	if (ikev2_prf_plus(prf, keys->SK_d, keys->SK_d_len, nonces, nlen,
			   keymat, EAP_MSK_LEN + EAP_EMSK_LEN)) {
		os_free(nonces);
		return -1;
	}
	os_free(nonces);

	wpa_hexdump_key(MSG_DEBUG, "EAP-IKEV2: KEYMAT",
			keymat, EAP_MSK_LEN + EAP_EMSK_LEN);

	return 0;
}