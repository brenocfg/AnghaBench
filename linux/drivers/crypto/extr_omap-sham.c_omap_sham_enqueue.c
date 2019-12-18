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
struct omap_sham_reqctx {unsigned int op; } ;
struct omap_sham_dev {int dummy; } ;
struct omap_sham_ctx {struct omap_sham_dev* dd; } ;
struct TYPE_2__ {int /*<<< orphan*/  tfm; } ;
struct ahash_request {TYPE_1__ base; } ;

/* Variables and functions */
 struct omap_sham_reqctx* ahash_request_ctx (struct ahash_request*) ; 
 struct omap_sham_ctx* crypto_tfm_ctx (int /*<<< orphan*/ ) ; 
 int omap_sham_handle_queue (struct omap_sham_dev*,struct ahash_request*) ; 

__attribute__((used)) static int omap_sham_enqueue(struct ahash_request *req, unsigned int op)
{
	struct omap_sham_reqctx *ctx = ahash_request_ctx(req);
	struct omap_sham_ctx *tctx = crypto_tfm_ctx(req->base.tfm);
	struct omap_sham_dev *dd = tctx->dd;

	ctx->op = op;

	return omap_sham_handle_queue(dd, req);
}