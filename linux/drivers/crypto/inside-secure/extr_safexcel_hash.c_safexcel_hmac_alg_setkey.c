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
struct safexcel_crypto_priv {int flags; } ;
struct safexcel_ahash_export_state {int /*<<< orphan*/  state; } ;
struct TYPE_2__ {int needs_inv; scalar_t__ ctxr; } ;
struct safexcel_ahash_ctx {int /*<<< orphan*/  opad; int /*<<< orphan*/  ipad; TYPE_1__ base; struct safexcel_crypto_priv* priv; } ;
struct crypto_ahash {int dummy; } ;

/* Variables and functions */
 int EIP197_TRC_CACHE ; 
 int /*<<< orphan*/  crypto_ahash_tfm (struct crypto_ahash*) ; 
 struct safexcel_ahash_ctx* crypto_tfm_ctx (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int) ; 
 int safexcel_hmac_setkey (char const*,int /*<<< orphan*/  const*,unsigned int,struct safexcel_ahash_export_state*,struct safexcel_ahash_export_state*) ; 

__attribute__((used)) static int safexcel_hmac_alg_setkey(struct crypto_ahash *tfm, const u8 *key,
				    unsigned int keylen, const char *alg,
				    unsigned int state_sz)
{
	struct safexcel_ahash_ctx *ctx = crypto_tfm_ctx(crypto_ahash_tfm(tfm));
	struct safexcel_crypto_priv *priv = ctx->priv;
	struct safexcel_ahash_export_state istate, ostate;
	int ret;

	ret = safexcel_hmac_setkey(alg, key, keylen, &istate, &ostate);
	if (ret)
		return ret;

	if (priv->flags & EIP197_TRC_CACHE && ctx->base.ctxr &&
	    (memcmp(ctx->ipad, istate.state, state_sz) ||
	     memcmp(ctx->opad, ostate.state, state_sz)))
		ctx->base.needs_inv = true;

	memcpy(ctx->ipad, &istate.state, state_sz);
	memcpy(ctx->opad, &ostate.state, state_sz);

	return 0;
}