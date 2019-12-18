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
struct omap_sham_reqctx {int flags; scalar_t__ total; int /*<<< orphan*/  digcnt; } ;
struct omap_sham_dev {scalar_t__ fallback_sz; int /*<<< orphan*/  dev; struct ahash_request* req; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FLAGS_CPU ; 
 int /*<<< orphan*/  FLAGS_FINUP ; 
 struct omap_sham_reqctx* ahash_request_ctx (struct ahash_request*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,...) ; 
 scalar_t__ get_block_size (struct omap_sham_reqctx*) ; 
 int omap_sham_xmit_cpu (struct omap_sham_dev*,scalar_t__,int) ; 
 int omap_sham_xmit_dma (struct omap_sham_dev*,scalar_t__,int) ; 

__attribute__((used)) static int omap_sham_update_req(struct omap_sham_dev *dd)
{
	struct ahash_request *req = dd->req;
	struct omap_sham_reqctx *ctx = ahash_request_ctx(req);
	int err;
	bool final = ctx->flags & BIT(FLAGS_FINUP);

	dev_dbg(dd->dev, "update_req: total: %u, digcnt: %d, finup: %d\n",
		 ctx->total, ctx->digcnt, (ctx->flags & BIT(FLAGS_FINUP)) != 0);

	if (ctx->total < get_block_size(ctx) ||
	    ctx->total < dd->fallback_sz)
		ctx->flags |= BIT(FLAGS_CPU);

	if (ctx->flags & BIT(FLAGS_CPU))
		err = omap_sham_xmit_cpu(dd, ctx->total, final);
	else
		err = omap_sham_xmit_dma(dd, ctx->total, final);

	/* wait for dma completion before can take more data */
	dev_dbg(dd->dev, "update: err: %d, digcnt: %d\n", err, ctx->digcnt);

	return err;
}