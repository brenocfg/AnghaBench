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
struct crypto_aead {int dummy; } ;
struct chachapoly_ctx {unsigned int saltlen; int /*<<< orphan*/  chacha; int /*<<< orphan*/  salt; } ;

/* Variables and functions */
 unsigned int CHACHA_KEY_SIZE ; 
 int CRYPTO_TFM_REQ_MASK ; 
 int CRYPTO_TFM_RES_MASK ; 
 int EINVAL ; 
 struct chachapoly_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 int crypto_aead_get_flags (struct crypto_aead*) ; 
 int /*<<< orphan*/  crypto_aead_set_flags (struct crypto_aead*,int) ; 
 int /*<<< orphan*/  crypto_skcipher_clear_flags (int /*<<< orphan*/ ,int) ; 
 int crypto_skcipher_get_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_skcipher_set_flags (int /*<<< orphan*/ ,int) ; 
 int crypto_skcipher_setkey (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 

__attribute__((used)) static int chachapoly_setkey(struct crypto_aead *aead, const u8 *key,
			     unsigned int keylen)
{
	struct chachapoly_ctx *ctx = crypto_aead_ctx(aead);
	int err;

	if (keylen != ctx->saltlen + CHACHA_KEY_SIZE)
		return -EINVAL;

	keylen -= ctx->saltlen;
	memcpy(ctx->salt, key + keylen, ctx->saltlen);

	crypto_skcipher_clear_flags(ctx->chacha, CRYPTO_TFM_REQ_MASK);
	crypto_skcipher_set_flags(ctx->chacha, crypto_aead_get_flags(aead) &
					       CRYPTO_TFM_REQ_MASK);

	err = crypto_skcipher_setkey(ctx->chacha, key, keylen);
	crypto_aead_set_flags(aead, crypto_skcipher_get_flags(ctx->chacha) &
				    CRYPTO_TFM_RES_MASK);
	return err;
}