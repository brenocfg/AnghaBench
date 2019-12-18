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
struct safexcel_crypto_priv {int flags; int /*<<< orphan*/  context_pool; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  ctxr_dma; int /*<<< orphan*/  ctxr; } ;
struct safexcel_cipher_ctx {TYPE_1__ base; struct safexcel_crypto_priv* priv; } ;
struct crypto_tfm {int dummy; } ;

/* Variables and functions */
 int EIP197_TRC_CACHE ; 
 struct safexcel_cipher_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ safexcel_cipher_cra_exit (struct crypto_tfm*) ; 
 int safexcel_skcipher_exit_inv (struct crypto_tfm*) ; 

__attribute__((used)) static void safexcel_skcipher_cra_exit(struct crypto_tfm *tfm)
{
	struct safexcel_cipher_ctx *ctx = crypto_tfm_ctx(tfm);
	struct safexcel_crypto_priv *priv = ctx->priv;
	int ret;

	if (safexcel_cipher_cra_exit(tfm))
		return;

	if (priv->flags & EIP197_TRC_CACHE) {
		ret = safexcel_skcipher_exit_inv(tfm);
		if (ret)
			dev_warn(priv->dev, "skcipher: invalidation error %d\n",
				 ret);
	} else {
		dma_pool_free(priv->context_pool, ctx->base.ctxr,
			      ctx->base.ctxr_dma);
	}
}