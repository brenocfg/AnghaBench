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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {int total; scalar_t__ buffer; } ;
typedef  TYPE_1__ SHA1_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (scalar_t__,char const*,size_t) ; 
 int /*<<< orphan*/  sha1_process (TYPE_1__*,int /*<<< orphan*/ *) ; 

void SHA1DCUpdate(SHA1_CTX* ctx, const char* buf, size_t len)
{
	unsigned left, fill;

	if (len == 0)
		return;

	left = ctx->total & 63;
	fill = 64 - left;

	if (left && len >= fill)
	{
		ctx->total += fill;
		memcpy(ctx->buffer + left, buf, fill);
		sha1_process(ctx, (uint32_t*)(ctx->buffer));
		buf += fill;
		len -= fill;
		left = 0;
	}
	while (len >= 64)
	{
		ctx->total += 64;

#if defined(SHA1DC_ALLOW_UNALIGNED_ACCESS)
		sha1_process(ctx, (uint32_t*)(buf));
#else
		memcpy(ctx->buffer, buf, 64);
		sha1_process(ctx, (uint32_t*)(ctx->buffer));
#endif /* defined(SHA1DC_ALLOW_UNALIGNED_ACCESS) */
		buf += 64;
		len -= 64;
	}
	if (len > 0)
	{
		ctx->total += len;
		memcpy(ctx->buffer + left, buf, len);
	}
}