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
typedef  unsigned int u16 ;
struct crypto_ablkcipher {int dummy; } ;
struct ablk_ctx {unsigned int enckey_len; int /*<<< orphan*/  ciph_mode; int /*<<< orphan*/  key_ctx_hdr; int /*<<< orphan*/  key; int /*<<< orphan*/  nonce; } ;

/* Variables and functions */
 struct ablk_ctx* ABLK_CTX (int /*<<< orphan*/ ) ; 
 unsigned int CHCR_KEYCTX_CIPHER_KEY_SIZE_192 ; 
 int /*<<< orphan*/  CHCR_KEYCTX_NO_KEY ; 
 int /*<<< orphan*/  CHCR_SCMD_CIPHER_MODE_AES_CTR ; 
 int /*<<< orphan*/  CRYPTO_TFM_RES_BAD_KEY_LEN ; 
 unsigned int CTR_RFC3686_NONCE_SIZE ; 
 int EINVAL ; 
 int /*<<< orphan*/  FILL_KEY_CTX_HDR (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int KEY_CONTEXT_HDR_SALT_AND_PAD ; 
 int /*<<< orphan*/  c_ctx (struct crypto_ablkcipher*) ; 
 int chcr_cipher_fallback_setkey (struct crypto_ablkcipher*,int /*<<< orphan*/  const*,unsigned int) ; 
 unsigned int chcr_keyctx_ck_size (unsigned int) ; 
 int /*<<< orphan*/  crypto_ablkcipher_set_flags (struct crypto_ablkcipher*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 

__attribute__((used)) static int chcr_aes_rfc3686_setkey(struct crypto_ablkcipher *cipher,
				   const u8 *key,
				   unsigned int keylen)
{
	struct ablk_ctx *ablkctx = ABLK_CTX(c_ctx(cipher));
	unsigned int ck_size, context_size;
	u16 alignment = 0;
	int err;

	if (keylen < CTR_RFC3686_NONCE_SIZE)
		return -EINVAL;
	memcpy(ablkctx->nonce, key + (keylen - CTR_RFC3686_NONCE_SIZE),
	       CTR_RFC3686_NONCE_SIZE);

	keylen -= CTR_RFC3686_NONCE_SIZE;
	err = chcr_cipher_fallback_setkey(cipher, key, keylen);
	if (err)
		goto badkey_err;

	ck_size = chcr_keyctx_ck_size(keylen);
	alignment = (ck_size == CHCR_KEYCTX_CIPHER_KEY_SIZE_192) ? 8 : 0;
	memcpy(ablkctx->key, key, keylen);
	ablkctx->enckey_len = keylen;
	context_size = (KEY_CONTEXT_HDR_SALT_AND_PAD +
			keylen + alignment) >> 4;

	ablkctx->key_ctx_hdr = FILL_KEY_CTX_HDR(ck_size, CHCR_KEYCTX_NO_KEY,
						0, 0, context_size);
	ablkctx->ciph_mode = CHCR_SCMD_CIPHER_MODE_AES_CTR;

	return 0;
badkey_err:
	crypto_ablkcipher_set_flags(cipher, CRYPTO_TFM_RES_BAD_KEY_LEN);
	ablkctx->enckey_len = 0;

	return err;
}