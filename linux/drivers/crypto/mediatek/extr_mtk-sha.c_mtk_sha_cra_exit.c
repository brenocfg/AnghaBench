#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mtk_sha_hmac_ctx {int /*<<< orphan*/  shash; } ;
struct mtk_sha_ctx {int flags; struct mtk_sha_hmac_ctx* base; } ;
struct crypto_tfm {int dummy; } ;

/* Variables and functions */
 int SHA_FLAGS_HMAC ; 
 int /*<<< orphan*/  crypto_free_shash (int /*<<< orphan*/ ) ; 
 struct mtk_sha_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 

__attribute__((used)) static void mtk_sha_cra_exit(struct crypto_tfm *tfm)
{
	struct mtk_sha_ctx *tctx = crypto_tfm_ctx(tfm);

	if (tctx->flags & SHA_FLAGS_HMAC) {
		struct mtk_sha_hmac_ctx *bctx = tctx->base;

		crypto_free_shash(bctx->shash);
	}
}