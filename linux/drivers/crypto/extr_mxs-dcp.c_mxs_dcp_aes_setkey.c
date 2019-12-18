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
struct dcp_async_ctx {unsigned int key_len; int /*<<< orphan*/  fallback; int /*<<< orphan*/  key; } ;
struct TYPE_2__ {int crt_flags; } ;
struct crypto_ablkcipher {TYPE_1__ base; } ;

/* Variables and functions */
 unsigned int AES_KEYSIZE_128 ; 
 int CRYPTO_TFM_REQ_MASK ; 
 int CRYPTO_TFM_RES_MASK ; 
 struct dcp_async_ctx* crypto_ablkcipher_ctx (struct crypto_ablkcipher*) ; 
 int /*<<< orphan*/  crypto_sync_skcipher_clear_flags (int /*<<< orphan*/ ,int) ; 
 int crypto_sync_skcipher_get_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_sync_skcipher_set_flags (int /*<<< orphan*/ ,int) ; 
 unsigned int crypto_sync_skcipher_setkey (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 

__attribute__((used)) static int mxs_dcp_aes_setkey(struct crypto_ablkcipher *tfm, const u8 *key,
			      unsigned int len)
{
	struct dcp_async_ctx *actx = crypto_ablkcipher_ctx(tfm);
	unsigned int ret;

	/*
	 * AES 128 is supposed by the hardware, store key into temporary
	 * buffer and exit. We must use the temporary buffer here, since
	 * there can still be an operation in progress.
	 */
	actx->key_len = len;
	if (len == AES_KEYSIZE_128) {
		memcpy(actx->key, key, len);
		return 0;
	}

	/*
	 * If the requested AES key size is not supported by the hardware,
	 * but is supported by in-kernel software implementation, we use
	 * software fallback.
	 */
	crypto_sync_skcipher_clear_flags(actx->fallback, CRYPTO_TFM_REQ_MASK);
	crypto_sync_skcipher_set_flags(actx->fallback,
				  tfm->base.crt_flags & CRYPTO_TFM_REQ_MASK);

	ret = crypto_sync_skcipher_setkey(actx->fallback, key, len);
	if (!ret)
		return 0;

	tfm->base.crt_flags &= ~CRYPTO_TFM_RES_MASK;
	tfm->base.crt_flags |= crypto_sync_skcipher_get_flags(actx->fallback) &
			       CRYPTO_TFM_RES_MASK;

	return ret;
}