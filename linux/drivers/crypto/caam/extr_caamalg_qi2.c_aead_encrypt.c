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
struct crypto_aead {int dummy; } ;
struct caam_request {struct aead_edesc* edesc; TYPE_1__* ctx; int /*<<< orphan*/  cbk; int /*<<< orphan*/  flc_dma; int /*<<< orphan*/ * flc; } ;
struct caam_ctx {int /*<<< orphan*/  dev; int /*<<< orphan*/ * flc_dma; int /*<<< orphan*/ * flc; } ;
struct TYPE_2__ {int flags; } ;
struct aead_request {TYPE_1__ base; } ;
struct aead_edesc {int dummy; } ;

/* Variables and functions */
 int CRYPTO_TFM_REQ_MAY_BACKLOG ; 
 int EBUSY ; 
 int EINPROGRESS ; 
 size_t ENCRYPT ; 
 scalar_t__ IS_ERR (struct aead_edesc*) ; 
 int PTR_ERR (struct aead_edesc*) ; 
 struct aead_edesc* aead_edesc_alloc (struct aead_request*,int) ; 
 int /*<<< orphan*/  aead_encrypt_done ; 
 struct caam_request* aead_request_ctx (struct aead_request*) ; 
 int /*<<< orphan*/  aead_unmap (int /*<<< orphan*/ ,struct aead_edesc*,struct aead_request*) ; 
 struct caam_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 struct crypto_aead* crypto_aead_reqtfm (struct aead_request*) ; 
 int dpaa2_caam_enqueue (int /*<<< orphan*/ ,struct caam_request*) ; 
 int /*<<< orphan*/  qi_cache_free (struct aead_edesc*) ; 

__attribute__((used)) static int aead_encrypt(struct aead_request *req)
{
	struct aead_edesc *edesc;
	struct crypto_aead *aead = crypto_aead_reqtfm(req);
	struct caam_ctx *ctx = crypto_aead_ctx(aead);
	struct caam_request *caam_req = aead_request_ctx(req);
	int ret;

	/* allocate extended descriptor */
	edesc = aead_edesc_alloc(req, true);
	if (IS_ERR(edesc))
		return PTR_ERR(edesc);

	caam_req->flc = &ctx->flc[ENCRYPT];
	caam_req->flc_dma = ctx->flc_dma[ENCRYPT];
	caam_req->cbk = aead_encrypt_done;
	caam_req->ctx = &req->base;
	caam_req->edesc = edesc;
	ret = dpaa2_caam_enqueue(ctx->dev, caam_req);
	if (ret != -EINPROGRESS &&
	    !(ret == -EBUSY && req->base.flags & CRYPTO_TFM_REQ_MAY_BACKLOG)) {
		aead_unmap(ctx->dev, edesc, req);
		qi_cache_free(edesc);
	}

	return ret;
}