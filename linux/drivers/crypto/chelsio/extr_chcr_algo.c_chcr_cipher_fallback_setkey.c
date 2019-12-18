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
struct crypto_tfm {int crt_flags; } ;
struct TYPE_2__ {int crt_flags; } ;
struct crypto_ablkcipher {TYPE_1__ base; } ;
struct ablk_ctx {int /*<<< orphan*/  sw_cipher; } ;

/* Variables and functions */
 struct ablk_ctx* ABLK_CTX (int /*<<< orphan*/ ) ; 
 int CRYPTO_TFM_REQ_MASK ; 
 int CRYPTO_TFM_RES_MASK ; 
 int /*<<< orphan*/  c_ctx (struct crypto_ablkcipher*) ; 
 struct crypto_tfm* crypto_ablkcipher_tfm (struct crypto_ablkcipher*) ; 
 int /*<<< orphan*/  crypto_sync_skcipher_clear_flags (int /*<<< orphan*/ ,int) ; 
 int crypto_sync_skcipher_get_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_sync_skcipher_set_flags (int /*<<< orphan*/ ,int) ; 
 int crypto_sync_skcipher_setkey (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 

__attribute__((used)) static int chcr_cipher_fallback_setkey(struct crypto_ablkcipher *cipher,
				       const u8 *key,
				       unsigned int keylen)
{
	struct crypto_tfm *tfm = crypto_ablkcipher_tfm(cipher);
	struct ablk_ctx *ablkctx = ABLK_CTX(c_ctx(cipher));
	int err = 0;

	crypto_sync_skcipher_clear_flags(ablkctx->sw_cipher,
				CRYPTO_TFM_REQ_MASK);
	crypto_sync_skcipher_set_flags(ablkctx->sw_cipher,
				cipher->base.crt_flags & CRYPTO_TFM_REQ_MASK);
	err = crypto_sync_skcipher_setkey(ablkctx->sw_cipher, key, keylen);
	tfm->crt_flags &= ~CRYPTO_TFM_RES_MASK;
	tfm->crt_flags |=
		crypto_sync_skcipher_get_flags(ablkctx->sw_cipher) &
		CRYPTO_TFM_RES_MASK;
	return err;
}