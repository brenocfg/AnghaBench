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
struct sahara_ctx {unsigned int keylen; int /*<<< orphan*/  fallback; int /*<<< orphan*/  flags; int /*<<< orphan*/  key; } ;
struct TYPE_2__ {int crt_flags; } ;
struct crypto_ablkcipher {TYPE_1__ base; } ;

/* Variables and functions */
 unsigned int AES_KEYSIZE_128 ; 
 unsigned int AES_KEYSIZE_192 ; 
 unsigned int AES_KEYSIZE_256 ; 
 int CRYPTO_TFM_REQ_MASK ; 
 int CRYPTO_TFM_RES_MASK ; 
 int EINVAL ; 
 int /*<<< orphan*/  FLAGS_NEW_KEY ; 
 struct sahara_ctx* crypto_ablkcipher_ctx (struct crypto_ablkcipher*) ; 
 int /*<<< orphan*/  crypto_sync_skcipher_clear_flags (int /*<<< orphan*/ ,int) ; 
 int crypto_sync_skcipher_get_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_sync_skcipher_set_flags (int /*<<< orphan*/ ,int) ; 
 int crypto_sync_skcipher_setkey (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 

__attribute__((used)) static int sahara_aes_setkey(struct crypto_ablkcipher *tfm, const u8 *key,
			     unsigned int keylen)
{
	struct sahara_ctx *ctx = crypto_ablkcipher_ctx(tfm);
	int ret;

	ctx->keylen = keylen;

	/* SAHARA only supports 128bit keys */
	if (keylen == AES_KEYSIZE_128) {
		memcpy(ctx->key, key, keylen);
		ctx->flags |= FLAGS_NEW_KEY;
		return 0;
	}

	if (keylen != AES_KEYSIZE_192 && keylen != AES_KEYSIZE_256)
		return -EINVAL;

	/*
	 * The requested key size is not supported by HW, do a fallback.
	 */
	crypto_sync_skcipher_clear_flags(ctx->fallback, CRYPTO_TFM_REQ_MASK);
	crypto_sync_skcipher_set_flags(ctx->fallback, tfm->base.crt_flags &
						 CRYPTO_TFM_REQ_MASK);

	ret = crypto_sync_skcipher_setkey(ctx->fallback, key, keylen);

	tfm->base.crt_flags &= ~CRYPTO_TFM_RES_MASK;
	tfm->base.crt_flags |= crypto_sync_skcipher_get_flags(ctx->fallback) &
			       CRYPTO_TFM_RES_MASK;
	return ret;
}