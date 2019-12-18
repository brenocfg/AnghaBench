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
typedef  int /*<<< orphan*/  u32 ;
struct mtk_sha_reqctx {int /*<<< orphan*/  op; } ;
struct mtk_sha_ctx {int /*<<< orphan*/  id; int /*<<< orphan*/  cryp; } ;
struct TYPE_2__ {int /*<<< orphan*/  tfm; } ;
struct ahash_request {TYPE_1__ base; } ;

/* Variables and functions */
 struct mtk_sha_reqctx* ahash_request_ctx (struct ahash_request*) ; 
 struct mtk_sha_ctx* crypto_tfm_ctx (int /*<<< orphan*/ ) ; 
 int mtk_sha_handle_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ahash_request*) ; 

__attribute__((used)) static int mtk_sha_enqueue(struct ahash_request *req, u32 op)
{
	struct mtk_sha_reqctx *ctx = ahash_request_ctx(req);
	struct mtk_sha_ctx *tctx = crypto_tfm_ctx(req->base.tfm);

	ctx->op = op;

	return mtk_sha_handle_queue(tctx->cryp, tctx->id, req);
}