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
struct qce_sha_reqctx {int last_blk; scalar_t__ buflen; int /*<<< orphan*/  sg; int /*<<< orphan*/  tmpbuf; int /*<<< orphan*/  buf; scalar_t__ nbytes_orig; int /*<<< orphan*/  src_orig; } ;
struct qce_device {int (* async_req_enqueue ) (struct qce_device*,TYPE_1__*) ;} ;
struct qce_alg_template {struct qce_device* qce; } ;
struct TYPE_2__ {int /*<<< orphan*/  tfm; } ;
struct ahash_request {TYPE_1__ base; scalar_t__ nbytes; int /*<<< orphan*/  src; } ;

/* Variables and functions */
 struct qce_sha_reqctx* ahash_request_ctx (struct ahash_request*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  sg_init_one (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int stub1 (struct qce_device*,TYPE_1__*) ; 
 struct qce_alg_template* to_ahash_tmpl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qce_ahash_final(struct ahash_request *req)
{
	struct qce_sha_reqctx *rctx = ahash_request_ctx(req);
	struct qce_alg_template *tmpl = to_ahash_tmpl(req->base.tfm);
	struct qce_device *qce = tmpl->qce;

	if (!rctx->buflen)
		return 0;

	rctx->last_blk = true;

	rctx->src_orig = req->src;
	rctx->nbytes_orig = req->nbytes;

	memcpy(rctx->tmpbuf, rctx->buf, rctx->buflen);
	sg_init_one(rctx->sg, rctx->tmpbuf, rctx->buflen);

	req->src = rctx->sg;
	req->nbytes = rctx->buflen;

	return qce->async_req_enqueue(tmpl->qce, &req->base);
}