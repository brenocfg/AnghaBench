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
struct TYPE_2__ {int /*<<< orphan*/  blk; } ;
struct s390_aes_ctx {TYPE_1__ fallback; } ;
struct crypto_tfm {int crt_flags; } ;

/* Variables and functions */
 int CRYPTO_TFM_REQ_MASK ; 
 int CRYPTO_TFM_RES_MASK ; 
 int /*<<< orphan*/  crypto_sync_skcipher_clear_flags (int /*<<< orphan*/ ,int) ; 
 int crypto_sync_skcipher_get_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_sync_skcipher_set_flags (int /*<<< orphan*/ ,int) ; 
 unsigned int crypto_sync_skcipher_setkey (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 
 struct s390_aes_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 

__attribute__((used)) static int setkey_fallback_blk(struct crypto_tfm *tfm, const u8 *key,
		unsigned int len)
{
	struct s390_aes_ctx *sctx = crypto_tfm_ctx(tfm);
	unsigned int ret;

	crypto_sync_skcipher_clear_flags(sctx->fallback.blk,
					 CRYPTO_TFM_REQ_MASK);
	crypto_sync_skcipher_set_flags(sctx->fallback.blk, tfm->crt_flags &
						      CRYPTO_TFM_REQ_MASK);

	ret = crypto_sync_skcipher_setkey(sctx->fallback.blk, key, len);

	tfm->crt_flags &= ~CRYPTO_TFM_RES_MASK;
	tfm->crt_flags |= crypto_sync_skcipher_get_flags(sctx->fallback.blk) &
			  CRYPTO_TFM_RES_MASK;

	return ret;
}