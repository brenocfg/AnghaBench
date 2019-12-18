#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct omap_aes_reqctx {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  do_one_request; int /*<<< orphan*/ * unprepare_request; int /*<<< orphan*/  prepare_request; } ;
struct TYPE_6__ {TYPE_2__ op; } ;
struct omap_aes_ctx {TYPE_3__ enginectx; struct crypto_sync_skcipher* fallback; } ;
struct TYPE_4__ {int reqsize; } ;
struct crypto_tfm {TYPE_1__ crt_ablkcipher; } ;
struct crypto_sync_skcipher {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_ALG_NEED_FALLBACK ; 
 scalar_t__ IS_ERR (struct crypto_sync_skcipher*) ; 
 int PTR_ERR (struct crypto_sync_skcipher*) ; 
 struct crypto_sync_skcipher* crypto_alloc_sync_skcipher (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* crypto_tfm_alg_name (struct crypto_tfm*) ; 
 struct omap_aes_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  omap_aes_crypt_req ; 
 int /*<<< orphan*/  omap_aes_prepare_req ; 

__attribute__((used)) static int omap_aes_cra_init(struct crypto_tfm *tfm)
{
	const char *name = crypto_tfm_alg_name(tfm);
	struct omap_aes_ctx *ctx = crypto_tfm_ctx(tfm);
	struct crypto_sync_skcipher *blk;

	blk = crypto_alloc_sync_skcipher(name, 0, CRYPTO_ALG_NEED_FALLBACK);
	if (IS_ERR(blk))
		return PTR_ERR(blk);

	ctx->fallback = blk;

	tfm->crt_ablkcipher.reqsize = sizeof(struct omap_aes_reqctx);

	ctx->enginectx.op.prepare_request = omap_aes_prepare_req;
	ctx->enginectx.op.unprepare_request = NULL;
	ctx->enginectx.op.do_one_request = omap_aes_crypt_req;

	return 0;
}