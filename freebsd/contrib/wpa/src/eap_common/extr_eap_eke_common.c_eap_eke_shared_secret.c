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
struct eap_eke_session {scalar_t__ encr; size_t auth_len; int /*<<< orphan*/ * shared_secret; int /*<<< orphan*/  prf; int /*<<< orphan*/  dhgroup; } ;
struct dh_group {size_t prime_len; int /*<<< orphan*/  prime; int /*<<< orphan*/ * generator; } ;

/* Variables and functions */
 int AES_BLOCK_SIZE ; 
 scalar_t__ EAP_EKE_ENCR_AES128_CBC ; 
 int EAP_EKE_MAX_DH_LEN ; 
 int EAP_EKE_MAX_HASH_LEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 scalar_t__ aes_128_cbc_decrypt (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ crypto_dh_derive_secret (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,size_t*) ; 
 struct dh_group* eap_eke_dh_group (int /*<<< orphan*/ ) ; 
 scalar_t__ eap_eke_prf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  os_memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  os_memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

int eap_eke_shared_secret(struct eap_eke_session *sess, const u8 *key,
			  const u8 *dhpriv, const u8 *peer_dhcomp)
{
	u8 zeros[EAP_EKE_MAX_HASH_LEN];
	u8 peer_pub[EAP_EKE_MAX_DH_LEN];
	u8 modexp[EAP_EKE_MAX_DH_LEN];
	size_t len;
	const struct dh_group *dh;

	dh = eap_eke_dh_group(sess->dhgroup);
	if (sess->encr != EAP_EKE_ENCR_AES128_CBC || !dh)
		return -1;

	/* Decrypt peer DHComponent */
	os_memcpy(peer_pub, peer_dhcomp + AES_BLOCK_SIZE, dh->prime_len);
	if (aes_128_cbc_decrypt(key, peer_dhcomp, peer_pub, dh->prime_len) < 0) {
		wpa_printf(MSG_INFO, "EAP-EKE: Failed to decrypt DHComponent");
		return -1;
	}
	wpa_hexdump_key(MSG_DEBUG, "EAP-EKE: Decrypted peer DH pubkey",
			peer_pub, dh->prime_len);

	/* SharedSecret = prf(0+, g ^ (x_s * x_p) (mod p)) */
	len = dh->prime_len;
	if (crypto_dh_derive_secret(*dh->generator, dh->prime, dh->prime_len,
				    NULL, 0, dhpriv, dh->prime_len, peer_pub,
				    dh->prime_len, modexp, &len) < 0)
		return -1;
	if (len < dh->prime_len) {
		size_t pad = dh->prime_len - len;
		os_memmove(modexp + pad, modexp, len);
		os_memset(modexp, 0, pad);
	}

	os_memset(zeros, 0, sess->auth_len);
	if (eap_eke_prf(sess->prf, zeros, sess->auth_len, modexp, dh->prime_len,
			NULL, 0, sess->shared_secret) < 0)
		return -1;
	wpa_hexdump_key(MSG_DEBUG, "EAP-EKE: SharedSecret",
			sess->shared_secret, sess->auth_len);

	return 0;
}