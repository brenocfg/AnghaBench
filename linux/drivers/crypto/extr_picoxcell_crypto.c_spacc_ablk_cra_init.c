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
struct spacc_req {int dummy; } ;
struct spacc_engine {int /*<<< orphan*/  dev; } ;
struct spacc_alg {int /*<<< orphan*/  iv_offs; int /*<<< orphan*/  key_offs; int /*<<< orphan*/  type; struct spacc_engine* engine; } ;
struct TYPE_3__ {int /*<<< orphan*/  iv_offs; int /*<<< orphan*/  key_offs; struct spacc_engine* engine; int /*<<< orphan*/  flags; } ;
struct spacc_ablk_ctx {TYPE_1__ generic; int /*<<< orphan*/  sw_cipher; } ;
struct TYPE_4__ {int reqsize; } ;
struct crypto_tfm {TYPE_2__ crt_ablkcipher; struct crypto_alg* __crt_alg; } ;
struct crypto_alg {int cra_flags; int /*<<< orphan*/  cra_name; } ;

/* Variables and functions */
 int CRYPTO_ALG_NEED_FALLBACK ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_alloc_sync_skcipher (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct spacc_ablk_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct spacc_alg* to_spacc_alg (struct crypto_alg*) ; 

__attribute__((used)) static int spacc_ablk_cra_init(struct crypto_tfm *tfm)
{
	struct spacc_ablk_ctx *ctx = crypto_tfm_ctx(tfm);
	struct crypto_alg *alg = tfm->__crt_alg;
	struct spacc_alg *spacc_alg = to_spacc_alg(alg);
	struct spacc_engine *engine = spacc_alg->engine;

	ctx->generic.flags = spacc_alg->type;
	ctx->generic.engine = engine;
	if (alg->cra_flags & CRYPTO_ALG_NEED_FALLBACK) {
		ctx->sw_cipher = crypto_alloc_sync_skcipher(
			alg->cra_name, 0, CRYPTO_ALG_NEED_FALLBACK);
		if (IS_ERR(ctx->sw_cipher)) {
			dev_warn(engine->dev, "failed to allocate fallback for %s\n",
				 alg->cra_name);
			return PTR_ERR(ctx->sw_cipher);
		}
	}
	ctx->generic.key_offs = spacc_alg->key_offs;
	ctx->generic.iv_offs = spacc_alg->iv_offs;

	tfm->crt_ablkcipher.reqsize = sizeof(struct spacc_req);

	return 0;
}