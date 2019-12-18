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
struct qce_cipher_reqctx {int dummy; } ;
struct qce_cipher_ctx {int /*<<< orphan*/  fallback; } ;
struct TYPE_2__ {int reqsize; } ;
struct crypto_tfm {TYPE_1__ crt_ablkcipher; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_ALG_NEED_FALLBACK ; 
 int PTR_ERR_OR_ZERO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_alloc_sync_skcipher (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_tfm_alg_name (struct crypto_tfm*) ; 
 struct qce_cipher_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  memset (struct qce_cipher_ctx*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int qce_ablkcipher_init(struct crypto_tfm *tfm)
{
	struct qce_cipher_ctx *ctx = crypto_tfm_ctx(tfm);

	memset(ctx, 0, sizeof(*ctx));
	tfm->crt_ablkcipher.reqsize = sizeof(struct qce_cipher_reqctx);

	ctx->fallback = crypto_alloc_sync_skcipher(crypto_tfm_alg_name(tfm),
						   0, CRYPTO_ALG_NEED_FALLBACK);
	return PTR_ERR_OR_ZERO(ctx->fallback);
}