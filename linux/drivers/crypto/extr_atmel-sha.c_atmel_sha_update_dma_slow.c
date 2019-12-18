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
struct atmel_sha_reqctx {int flags; size_t bufcnt; size_t buflen; int /*<<< orphan*/ * digcnt; int /*<<< orphan*/  total; } ;
struct atmel_sha_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  req; } ;

/* Variables and functions */
 int SHA_FLAGS_FINUP ; 
 struct atmel_sha_reqctx* ahash_request_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atmel_sha_append_sg (struct atmel_sha_reqctx*) ; 
 int /*<<< orphan*/  atmel_sha_fill_padding (struct atmel_sha_reqctx*,int /*<<< orphan*/ ) ; 
 int atmel_sha_xmit_dma_map (struct atmel_sha_dev*,struct atmel_sha_reqctx*,size_t,unsigned int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int atmel_sha_update_dma_slow(struct atmel_sha_dev *dd)
{
	struct atmel_sha_reqctx *ctx = ahash_request_ctx(dd->req);
	unsigned int final;
	size_t count;

	atmel_sha_append_sg(ctx);

	final = (ctx->flags & SHA_FLAGS_FINUP) && !ctx->total;

	dev_dbg(dd->dev, "slow: bufcnt: %zu, digcnt: 0x%llx 0x%llx, final: %d\n",
		 ctx->bufcnt, ctx->digcnt[1], ctx->digcnt[0], final);

	if (final)
		atmel_sha_fill_padding(ctx, 0);

	if (final || (ctx->bufcnt == ctx->buflen)) {
		count = ctx->bufcnt;
		ctx->bufcnt = 0;
		return atmel_sha_xmit_dma_map(dd, ctx, count, final);
	}

	return 0;
}