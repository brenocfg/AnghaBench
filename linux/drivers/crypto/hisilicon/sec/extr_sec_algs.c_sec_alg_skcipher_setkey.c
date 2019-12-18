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
struct sec_alg_tfm_ctx {int /*<<< orphan*/  lock; scalar_t__ key; int /*<<< orphan*/  pkey; TYPE_2__* queue; } ;
struct device {int dummy; } ;
struct crypto_skcipher {int dummy; } ;
typedef  enum sec_cipher_alg { ____Placeholder_sec_cipher_alg } sec_cipher_alg ;
struct TYPE_4__ {TYPE_1__* dev_info; } ;
struct TYPE_3__ {struct device* dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SEC_MAX_CIPHER_KEY ; 
 struct sec_alg_tfm_ctx* crypto_skcipher_ctx (struct crypto_skcipher*) ; 
 scalar_t__ dma_alloc_coherent (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sec_alg_skcipher_init_context (struct crypto_skcipher*,int /*<<< orphan*/  const*,unsigned int,int) ; 

__attribute__((used)) static int sec_alg_skcipher_setkey(struct crypto_skcipher *tfm,
				   const u8 *key, unsigned int keylen,
				   enum sec_cipher_alg alg)
{
	struct sec_alg_tfm_ctx *ctx = crypto_skcipher_ctx(tfm);
	struct device *dev = ctx->queue->dev_info->dev;

	mutex_lock(&ctx->lock);
	if (ctx->key) {
		/* rekeying */
		memset(ctx->key, 0, SEC_MAX_CIPHER_KEY);
	} else {
		/* new key */
		ctx->key = dma_alloc_coherent(dev, SEC_MAX_CIPHER_KEY,
					      &ctx->pkey, GFP_KERNEL);
		if (!ctx->key) {
			mutex_unlock(&ctx->lock);
			return -ENOMEM;
		}
	}
	mutex_unlock(&ctx->lock);
	sec_alg_skcipher_init_context(tfm, key, keylen, alg);

	return 0;
}