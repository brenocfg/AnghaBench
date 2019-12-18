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
struct sahara_ctx {int /*<<< orphan*/  fallback; } ;
struct sahara_aes_reqctx {int dummy; } ;
struct TYPE_2__ {int reqsize; } ;
struct crypto_tfm {TYPE_1__ crt_ablkcipher; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_ALG_NEED_FALLBACK ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_alloc_sync_skcipher (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* crypto_tfm_alg_name (struct crypto_tfm*) ; 
 struct sahara_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  pr_err (char*,char const*) ; 

__attribute__((used)) static int sahara_aes_cra_init(struct crypto_tfm *tfm)
{
	const char *name = crypto_tfm_alg_name(tfm);
	struct sahara_ctx *ctx = crypto_tfm_ctx(tfm);

	ctx->fallback = crypto_alloc_sync_skcipher(name, 0,
					      CRYPTO_ALG_NEED_FALLBACK);
	if (IS_ERR(ctx->fallback)) {
		pr_err("Error allocating fallback algo %s\n", name);
		return PTR_ERR(ctx->fallback);
	}

	tfm->crt_ablkcipher.reqsize = sizeof(struct sahara_aes_reqctx);

	return 0;
}