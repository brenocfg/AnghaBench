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
struct TYPE_2__ {int flags; } ;
struct skcipher_request {TYPE_1__ base; int /*<<< orphan*/  cryptlen; } ;
struct skcipher_edesc {int dummy; } ;
struct crypto_skcipher {int dummy; } ;
struct caam_request {struct skcipher_edesc* edesc; TYPE_1__* ctx; int /*<<< orphan*/  cbk; int /*<<< orphan*/  flc_dma; int /*<<< orphan*/ * flc; } ;
struct caam_ctx {int /*<<< orphan*/  dev; int /*<<< orphan*/ * flc_dma; int /*<<< orphan*/ * flc; } ;

/* Variables and functions */
 int CRYPTO_TFM_REQ_MAY_BACKLOG ; 
 size_t DECRYPT ; 
 int EBUSY ; 
 int EINPROGRESS ; 
 scalar_t__ IS_ERR (struct skcipher_edesc*) ; 
 int PTR_ERR (struct skcipher_edesc*) ; 
 struct caam_ctx* crypto_skcipher_ctx (struct crypto_skcipher*) ; 
 struct crypto_skcipher* crypto_skcipher_reqtfm (struct skcipher_request*) ; 
 int dpaa2_caam_enqueue (int /*<<< orphan*/ ,struct caam_request*) ; 
 int /*<<< orphan*/  qi_cache_free (struct skcipher_edesc*) ; 
 int /*<<< orphan*/  skcipher_decrypt_done ; 
 struct skcipher_edesc* skcipher_edesc_alloc (struct skcipher_request*) ; 
 struct caam_request* skcipher_request_ctx (struct skcipher_request*) ; 
 int /*<<< orphan*/  skcipher_unmap (int /*<<< orphan*/ ,struct skcipher_edesc*,struct skcipher_request*) ; 

__attribute__((used)) static int skcipher_decrypt(struct skcipher_request *req)
{
	struct skcipher_edesc *edesc;
	struct crypto_skcipher *skcipher = crypto_skcipher_reqtfm(req);
	struct caam_ctx *ctx = crypto_skcipher_ctx(skcipher);
	struct caam_request *caam_req = skcipher_request_ctx(req);
	int ret;

	if (!req->cryptlen)
		return 0;
	/* allocate extended descriptor */
	edesc = skcipher_edesc_alloc(req);
	if (IS_ERR(edesc))
		return PTR_ERR(edesc);

	caam_req->flc = &ctx->flc[DECRYPT];
	caam_req->flc_dma = ctx->flc_dma[DECRYPT];
	caam_req->cbk = skcipher_decrypt_done;
	caam_req->ctx = &req->base;
	caam_req->edesc = edesc;
	ret = dpaa2_caam_enqueue(ctx->dev, caam_req);
	if (ret != -EINPROGRESS &&
	    !(ret == -EBUSY && req->base.flags & CRYPTO_TFM_REQ_MAY_BACKLOG)) {
		skcipher_unmap(ctx->dev, edesc, req);
		qi_cache_free(edesc);
	}

	return ret;
}