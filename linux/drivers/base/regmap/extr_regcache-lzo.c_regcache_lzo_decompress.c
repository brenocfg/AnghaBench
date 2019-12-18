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
struct regcache_lzo_ctx {size_t dst_len; int /*<<< orphan*/  dst; int /*<<< orphan*/  src_len; int /*<<< orphan*/  src; } ;

/* Variables and functions */
 int EINVAL ; 
 int LZO_E_OK ; 
 int lzo1x_decompress_safe (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*) ; 

__attribute__((used)) static int regcache_lzo_decompress(struct regcache_lzo_ctx *lzo_ctx)
{
	size_t dst_len;
	int ret;

	dst_len = lzo_ctx->dst_len;
	ret = lzo1x_decompress_safe(lzo_ctx->src, lzo_ctx->src_len,
				    lzo_ctx->dst, &dst_len);
	if (ret != LZO_E_OK || dst_len != lzo_ctx->dst_len)
		return -EINVAL;
	return 0;
}