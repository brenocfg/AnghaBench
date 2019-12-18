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
struct mtk_aes_reqctx {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  start; } ;
struct mtk_aes_gcm_ctx {TYPE_1__ base; int /*<<< orphan*/  ctr; } ;
struct crypto_aead {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_ALG_ASYNC ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 struct mtk_aes_gcm_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 int /*<<< orphan*/  crypto_aead_set_reqsize (struct crypto_aead*,int) ; 
 int /*<<< orphan*/  crypto_alloc_skcipher (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_aes_gcm_start ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int mtk_aes_gcm_init(struct crypto_aead *aead)
{
	struct mtk_aes_gcm_ctx *ctx = crypto_aead_ctx(aead);

	ctx->ctr = crypto_alloc_skcipher("ctr(aes)", 0,
					 CRYPTO_ALG_ASYNC);
	if (IS_ERR(ctx->ctr)) {
		pr_err("Error allocating ctr(aes)\n");
		return PTR_ERR(ctx->ctr);
	}

	crypto_aead_set_reqsize(aead, sizeof(struct mtk_aes_reqctx));
	ctx->base.start = mtk_aes_gcm_start;
	return 0;
}