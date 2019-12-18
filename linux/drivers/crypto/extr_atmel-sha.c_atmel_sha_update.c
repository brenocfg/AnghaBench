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
struct atmel_sha_reqctx {scalar_t__ total; int flags; scalar_t__ bufcnt; scalar_t__ buflen; scalar_t__ offset; int /*<<< orphan*/  sg; } ;
struct ahash_request {scalar_t__ nbytes; int /*<<< orphan*/  src; } ;

/* Variables and functions */
 scalar_t__ ATMEL_SHA_DMA_THRESHOLD ; 
 int SHA_FLAGS_CPU ; 
 int SHA_FLAGS_FINUP ; 
 int /*<<< orphan*/  SHA_OP_UPDATE ; 
 struct atmel_sha_reqctx* ahash_request_ctx (struct ahash_request*) ; 
 int /*<<< orphan*/  atmel_sha_append_sg (struct atmel_sha_reqctx*) ; 
 int atmel_sha_enqueue (struct ahash_request*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int atmel_sha_update(struct ahash_request *req)
{
	struct atmel_sha_reqctx *ctx = ahash_request_ctx(req);

	if (!req->nbytes)
		return 0;

	ctx->total = req->nbytes;
	ctx->sg = req->src;
	ctx->offset = 0;

	if (ctx->flags & SHA_FLAGS_FINUP) {
		if (ctx->bufcnt + ctx->total < ATMEL_SHA_DMA_THRESHOLD)
			/* faster to use CPU for short transfers */
			ctx->flags |= SHA_FLAGS_CPU;
	} else if (ctx->bufcnt + ctx->total < ctx->buflen) {
		atmel_sha_append_sg(ctx);
		return 0;
	}
	return atmel_sha_enqueue(req, SHA_OP_UPDATE);
}