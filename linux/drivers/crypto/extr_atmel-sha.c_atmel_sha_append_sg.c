#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct atmel_sha_reqctx {scalar_t__ bufcnt; scalar_t__ buflen; scalar_t__ total; size_t offset; scalar_t__ buffer; TYPE_1__* sg; } ;
struct TYPE_4__ {size_t length; } ;

/* Variables and functions */
 size_t min (size_t,scalar_t__) ; 
 int /*<<< orphan*/  scatterwalk_map_and_copy (scalar_t__,TYPE_1__*,size_t,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_is_last (TYPE_1__*) ; 
 void* sg_next (TYPE_1__*) ; 

__attribute__((used)) static size_t atmel_sha_append_sg(struct atmel_sha_reqctx *ctx)
{
	size_t count;

	while ((ctx->bufcnt < ctx->buflen) && ctx->total) {
		count = min(ctx->sg->length - ctx->offset, ctx->total);
		count = min(count, ctx->buflen - ctx->bufcnt);

		if (count <= 0) {
			/*
			* Check if count <= 0 because the buffer is full or
			* because the sg length is 0. In the latest case,
			* check if there is another sg in the list, a 0 length
			* sg doesn't necessarily mean the end of the sg list.
			*/
			if ((ctx->sg->length == 0) && !sg_is_last(ctx->sg)) {
				ctx->sg = sg_next(ctx->sg);
				continue;
			} else {
				break;
			}
		}

		scatterwalk_map_and_copy(ctx->buffer + ctx->bufcnt, ctx->sg,
			ctx->offset, count, 0);

		ctx->bufcnt += count;
		ctx->offset += count;
		ctx->total -= count;

		if (ctx->offset == ctx->sg->length) {
			ctx->sg = sg_next(ctx->sg);
			if (ctx->sg)
				ctx->offset = 0;
			else
				ctx->total = 0;
		}
	}

	return 0;
}