#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_3__ {struct flexi_crypto_context* fctx; } ;
struct nitrox_crypto_ctx {TYPE_1__ u; } ;
struct TYPE_4__ {int /*<<< orphan*/  iv; } ;
struct flexi_crypto_context {TYPE_2__ crypto; } ;
struct crypto_tfm {int dummy; } ;
struct crypto_skcipher {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_TFM_RES_BAD_KEY_LEN ; 
 unsigned int CTR_RFC3686_NONCE_SIZE ; 
 int EINVAL ; 
 int /*<<< orphan*/  crypto_skcipher_set_flags (struct crypto_skcipher*,int /*<<< orphan*/ ) ; 
 struct crypto_tfm* crypto_skcipher_tfm (struct crypto_skcipher*) ; 
 struct nitrox_crypto_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int flexi_aes_keylen (unsigned int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 
 int nitrox_skcipher_setkey (struct crypto_skcipher*,int,int /*<<< orphan*/  const*,unsigned int) ; 

__attribute__((used)) static int nitrox_aes_ctr_rfc3686_setkey(struct crypto_skcipher *cipher,
					 const u8 *key, unsigned int keylen)
{
	struct crypto_tfm *tfm = crypto_skcipher_tfm(cipher);
	struct nitrox_crypto_ctx *nctx = crypto_tfm_ctx(tfm);
	struct flexi_crypto_context *fctx;
	int aes_keylen;

	if (keylen < CTR_RFC3686_NONCE_SIZE)
		return -EINVAL;

	fctx = nctx->u.fctx;

	memcpy(fctx->crypto.iv, key + (keylen - CTR_RFC3686_NONCE_SIZE),
	       CTR_RFC3686_NONCE_SIZE);

	keylen -= CTR_RFC3686_NONCE_SIZE;

	aes_keylen = flexi_aes_keylen(keylen);
	if (aes_keylen < 0) {
		crypto_skcipher_set_flags(cipher, CRYPTO_TFM_RES_BAD_KEY_LEN);
		return -EINVAL;
	}
	return nitrox_skcipher_setkey(cipher, aes_keylen, key, keylen);
}