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
struct TYPE_4__ {int size; void const* buf; } ;
typedef  TYPE_1__ blk_SHA256_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  blk_SHA256_Transform (TYPE_1__*,void const*) ; 
 int /*<<< orphan*/  memcpy (void const*,void const*,size_t) ; 

void blk_SHA256_Update(blk_SHA256_CTX *ctx, const void *data, size_t len)
{
	unsigned int len_buf = ctx->size & 63;

	ctx->size += len;

	/* Read the data into buf and process blocks as they get full */
	if (len_buf) {
		unsigned int left = 64 - len_buf;
		if (len < left)
			left = len;
		memcpy(len_buf + ctx->buf, data, left);
		len_buf = (len_buf + left) & 63;
		len -= left;
		data = ((const char *)data + left);
		if (len_buf)
			return;
		blk_SHA256_Transform(ctx, ctx->buf);
	}
	while (len >= 64) {
		blk_SHA256_Transform(ctx, data);
		data = ((const char *)data + 64);
		len -= 64;
	}
	if (len)
		memcpy(ctx->buf, data, len);
}