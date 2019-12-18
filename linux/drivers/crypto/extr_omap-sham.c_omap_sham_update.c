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
struct omap_sham_reqctx {scalar_t__ bufcnt; scalar_t__ buflen; scalar_t__ buffer; int /*<<< orphan*/  flags; struct omap_sham_dev* dd; } ;
struct omap_sham_dev {scalar_t__ polling_mode; } ;
struct ahash_request {scalar_t__ nbytes; int /*<<< orphan*/  src; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FLAGS_CPU ; 
 int /*<<< orphan*/  OP_UPDATE ; 
 struct omap_sham_reqctx* ahash_request_ctx (struct ahash_request*) ; 
 int omap_sham_enqueue (struct ahash_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scatterwalk_map_and_copy (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int omap_sham_update(struct ahash_request *req)
{
	struct omap_sham_reqctx *ctx = ahash_request_ctx(req);
	struct omap_sham_dev *dd = ctx->dd;

	if (!req->nbytes)
		return 0;

	if (ctx->bufcnt + req->nbytes <= ctx->buflen) {
		scatterwalk_map_and_copy(ctx->buffer + ctx->bufcnt, req->src,
					 0, req->nbytes, 0);
		ctx->bufcnt += req->nbytes;
		return 0;
	}

	if (dd->polling_mode)
		ctx->flags |= BIT(FLAGS_CPU);

	return omap_sham_enqueue(req, OP_UPDATE);
}