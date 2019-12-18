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
struct crypto_tfm {int dummy; } ;
struct crypto_aes_ctx {int dummy; } ;
struct crypto_aead {int dummy; } ;
struct chcr_gcm_ctx {int /*<<< orphan*/  ghash_h; } ;
struct chcr_aead_ctx {unsigned int enckey_len; int /*<<< orphan*/  key_ctx_hdr; int /*<<< orphan*/  key; int /*<<< orphan*/  salt; struct crypto_aead* sw_cipher; } ;
struct _key_ctx {int dummy; } ;
typedef  int /*<<< orphan*/  aes ;

/* Variables and functions */
 struct chcr_aead_ctx* AEAD_CTX (int /*<<< orphan*/ ) ; 
 int AEAD_H_SIZE ; 
 unsigned int AES_KEYSIZE_128 ; 
 unsigned int AES_KEYSIZE_192 ; 
 unsigned int AES_KEYSIZE_256 ; 
 unsigned int CHCR_KEYCTX_CIPHER_KEY_SIZE_128 ; 
 unsigned int CHCR_KEYCTX_CIPHER_KEY_SIZE_192 ; 
 unsigned int CHCR_KEYCTX_CIPHER_KEY_SIZE_256 ; 
 int /*<<< orphan*/  CHCR_KEYCTX_MAC_KEY_SIZE_128 ; 
 scalar_t__ CRYPTO_ALG_SUB_TYPE_AEAD_RFC4106 ; 
 int CRYPTO_TFM_REQ_MASK ; 
 int /*<<< orphan*/  CRYPTO_TFM_RES_BAD_KEY_LEN ; 
 int CRYPTO_TFM_RES_MASK ; 
 int EINVAL ; 
 int /*<<< orphan*/  FILL_KEY_CTX_HDR (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct chcr_gcm_ctx* GCM_CTX (struct chcr_aead_ctx*) ; 
 int /*<<< orphan*/  a_ctx (struct crypto_aead*) ; 
 int /*<<< orphan*/  aes_encrypt (struct crypto_aes_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int aes_expandkey (struct crypto_aes_ctx*,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  crypto_aead_clear_flags (struct crypto_aead*,int) ; 
 int crypto_aead_get_flags (struct crypto_aead*) ; 
 int /*<<< orphan*/  crypto_aead_set_flags (struct crypto_aead*,int) ; 
 int crypto_aead_setkey (struct crypto_aead*,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  crypto_tfm_set_flags (struct crypto_tfm*,int /*<<< orphan*/ ) ; 
 scalar_t__ get_aead_subtype (struct crypto_aead*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memzero_explicit (struct crypto_aes_ctx*,int) ; 
 int /*<<< orphan*/  pr_err (char*,unsigned int) ; 
 int roundup (unsigned int,int) ; 

__attribute__((used)) static int chcr_gcm_setkey(struct crypto_aead *aead, const u8 *key,
			   unsigned int keylen)
{
	struct chcr_aead_ctx *aeadctx = AEAD_CTX(a_ctx(aead));
	struct chcr_gcm_ctx *gctx = GCM_CTX(aeadctx);
	unsigned int ck_size;
	int ret = 0, key_ctx_size = 0;
	struct crypto_aes_ctx aes;

	aeadctx->enckey_len = 0;
	crypto_aead_clear_flags(aeadctx->sw_cipher, CRYPTO_TFM_REQ_MASK);
	crypto_aead_set_flags(aeadctx->sw_cipher, crypto_aead_get_flags(aead)
			      & CRYPTO_TFM_REQ_MASK);
	ret = crypto_aead_setkey(aeadctx->sw_cipher, key, keylen);
	crypto_aead_clear_flags(aead, CRYPTO_TFM_RES_MASK);
	crypto_aead_set_flags(aead, crypto_aead_get_flags(aeadctx->sw_cipher) &
			      CRYPTO_TFM_RES_MASK);
	if (ret)
		goto out;

	if (get_aead_subtype(aead) == CRYPTO_ALG_SUB_TYPE_AEAD_RFC4106 &&
	    keylen > 3) {
		keylen -= 4;  /* nonce/salt is present in the last 4 bytes */
		memcpy(aeadctx->salt, key + keylen, 4);
	}
	if (keylen == AES_KEYSIZE_128) {
		ck_size = CHCR_KEYCTX_CIPHER_KEY_SIZE_128;
	} else if (keylen == AES_KEYSIZE_192) {
		ck_size = CHCR_KEYCTX_CIPHER_KEY_SIZE_192;
	} else if (keylen == AES_KEYSIZE_256) {
		ck_size = CHCR_KEYCTX_CIPHER_KEY_SIZE_256;
	} else {
		crypto_tfm_set_flags((struct crypto_tfm *)aead,
				     CRYPTO_TFM_RES_BAD_KEY_LEN);
		pr_err("GCM: Invalid key length %d\n", keylen);
		ret = -EINVAL;
		goto out;
	}

	memcpy(aeadctx->key, key, keylen);
	aeadctx->enckey_len = keylen;
	key_ctx_size = sizeof(struct _key_ctx) + roundup(keylen, 16) +
		AEAD_H_SIZE;
	aeadctx->key_ctx_hdr = FILL_KEY_CTX_HDR(ck_size,
						CHCR_KEYCTX_MAC_KEY_SIZE_128,
						0, 0,
						key_ctx_size >> 4);
	/* Calculate the H = CIPH(K, 0 repeated 16 times).
	 * It will go in key context
	 */
	ret = aes_expandkey(&aes, key, keylen);
	if (ret) {
		aeadctx->enckey_len = 0;
		goto out;
	}
	memset(gctx->ghash_h, 0, AEAD_H_SIZE);
	aes_encrypt(&aes, gctx->ghash_h, gctx->ghash_h);
	memzero_explicit(&aes, sizeof(aes));

out:
	return ret;
}