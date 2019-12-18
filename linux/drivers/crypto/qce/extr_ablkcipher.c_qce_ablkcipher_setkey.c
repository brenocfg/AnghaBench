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
struct qce_cipher_ctx {unsigned int enc_keylen; int /*<<< orphan*/  fallback; int /*<<< orphan*/  enc_key; } ;
struct crypto_tfm {int dummy; } ;
struct crypto_ablkcipher {int dummy; } ;

/* Variables and functions */
#define  AES_KEYSIZE_128 129 
#define  AES_KEYSIZE_256 128 
 int EINVAL ; 
 struct crypto_tfm* crypto_ablkcipher_tfm (struct crypto_ablkcipher*) ; 
 int crypto_sync_skcipher_setkey (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 
 struct qce_cipher_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 

__attribute__((used)) static int qce_ablkcipher_setkey(struct crypto_ablkcipher *ablk, const u8 *key,
				 unsigned int keylen)
{
	struct crypto_tfm *tfm = crypto_ablkcipher_tfm(ablk);
	struct qce_cipher_ctx *ctx = crypto_tfm_ctx(tfm);
	int ret;

	if (!key || !keylen)
		return -EINVAL;

	switch (keylen) {
	case AES_KEYSIZE_128:
	case AES_KEYSIZE_256:
		break;
	default:
		goto fallback;
	}

	ctx->enc_keylen = keylen;
	memcpy(ctx->enc_key, key, keylen);
	return 0;
fallback:
	ret = crypto_sync_skcipher_setkey(ctx->fallback, key, keylen);
	if (!ret)
		ctx->enc_keylen = keylen;
	return ret;
}