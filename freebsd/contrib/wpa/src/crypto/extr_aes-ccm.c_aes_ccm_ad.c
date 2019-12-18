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

/* Variables and functions */
 int AES_BLOCK_SIZE ; 
 int /*<<< orphan*/  MSG_EXCESSIVE ; 
 int /*<<< orphan*/  aes_ccm_auth (void*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aes_ccm_auth_start (void*,size_t,size_t const,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aes_ccm_decr_auth (void*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aes_ccm_encr (void*,size_t const,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aes_ccm_encr_start (size_t const,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aes_encrypt_deinit (void*) ; 
 void* aes_encrypt_init (int /*<<< orphan*/  const*,size_t) ; 
 scalar_t__ os_memcmp_const (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

int aes_ccm_ad(const u8 *key, size_t key_len, const u8 *nonce,
	       size_t M, const u8 *crypt, size_t crypt_len,
	       const u8 *aad, size_t aad_len, const u8 *auth, u8 *plain)
{
	const size_t L = 2;
	void *aes;
	u8 x[AES_BLOCK_SIZE], a[AES_BLOCK_SIZE];
	u8 t[AES_BLOCK_SIZE];

	if (aad_len > 30 || M > AES_BLOCK_SIZE)
		return -1;

	aes = aes_encrypt_init(key, key_len);
	if (aes == NULL)
		return -1;

	/* Decryption */
	aes_ccm_encr_start(L, nonce, a);
	aes_ccm_decr_auth(aes, M, a, auth, t);

	/* plaintext = msg XOR (S_1 | S_2 | ... | S_n) */
	aes_ccm_encr(aes, L, crypt, crypt_len, plain, a);

	aes_ccm_auth_start(aes, M, L, nonce, aad, aad_len, crypt_len, x);
	aes_ccm_auth(aes, plain, crypt_len, x);

	aes_encrypt_deinit(aes);

	if (os_memcmp_const(x, t, M) != 0) {
		wpa_printf(MSG_EXCESSIVE, "CCM: Auth mismatch");
		return -1;
	}

	return 0;
}