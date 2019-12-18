#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct spacc_ablk_ctx {unsigned int key_len; int /*<<< orphan*/  key; int /*<<< orphan*/  sw_cipher; } ;
struct crypto_tfm {int crt_flags; } ;
struct TYPE_2__ {int crt_flags; } ;
struct crypto_ablkcipher {TYPE_1__ base; } ;

/* Variables and functions */
 unsigned int AES_KEYSIZE_128 ; 
 unsigned int AES_KEYSIZE_256 ; 
 unsigned int AES_MAX_KEY_SIZE ; 
 int CRYPTO_TFM_REQ_MASK ; 
 int /*<<< orphan*/  CRYPTO_TFM_RES_BAD_KEY_LEN ; 
 int CRYPTO_TFM_RES_MASK ; 
 int EINVAL ; 
 int /*<<< orphan*/  crypto_ablkcipher_set_flags (struct crypto_ablkcipher*,int /*<<< orphan*/ ) ; 
 struct crypto_tfm* crypto_ablkcipher_tfm (struct crypto_ablkcipher*) ; 
 int /*<<< orphan*/  crypto_sync_skcipher_clear_flags (int /*<<< orphan*/ ,int) ; 
 int crypto_sync_skcipher_get_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_sync_skcipher_set_flags (int /*<<< orphan*/ ,int) ; 
 int crypto_sync_skcipher_setkey (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 
 struct spacc_ablk_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 

__attribute__((used)) static int spacc_aes_setkey(struct crypto_ablkcipher *cipher, const u8 *key,
			    unsigned int len)
{
	struct crypto_tfm *tfm = crypto_ablkcipher_tfm(cipher);
	struct spacc_ablk_ctx *ctx = crypto_tfm_ctx(tfm);
	int err = 0;

	if (len > AES_MAX_KEY_SIZE) {
		crypto_ablkcipher_set_flags(cipher, CRYPTO_TFM_RES_BAD_KEY_LEN);
		return -EINVAL;
	}

	/*
	 * IPSec engine only supports 128 and 256 bit AES keys. If we get a
	 * request for any other size (192 bits) then we need to do a software
	 * fallback.
	 */
	if (len != AES_KEYSIZE_128 && len != AES_KEYSIZE_256) {
		if (!ctx->sw_cipher)
			return -EINVAL;

		/*
		 * Set the fallback transform to use the same request flags as
		 * the hardware transform.
		 */
		crypto_sync_skcipher_clear_flags(ctx->sw_cipher,
					    CRYPTO_TFM_REQ_MASK);
		crypto_sync_skcipher_set_flags(ctx->sw_cipher,
					  cipher->base.crt_flags &
					  CRYPTO_TFM_REQ_MASK);

		err = crypto_sync_skcipher_setkey(ctx->sw_cipher, key, len);

		tfm->crt_flags &= ~CRYPTO_TFM_RES_MASK;
		tfm->crt_flags |=
			crypto_sync_skcipher_get_flags(ctx->sw_cipher) &
			CRYPTO_TFM_RES_MASK;

		if (err)
			goto sw_setkey_failed;
	}

	memcpy(ctx->key, key, len);
	ctx->key_len = len;

sw_setkey_failed:
	return err;
}