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
typedef  int /*<<< orphan*/  u8 ;
struct zstd_ctx {int /*<<< orphan*/  cctx; } ;
typedef  int /*<<< orphan*/  ZSTD_parameters ;

/* Variables and functions */
 int EINVAL ; 
 size_t ZSTD_compressCCtx (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/  const*,unsigned int,int /*<<< orphan*/  const) ; 
 scalar_t__ ZSTD_isError (size_t) ; 
 int /*<<< orphan*/  zstd_params () ; 

__attribute__((used)) static int __zstd_compress(const u8 *src, unsigned int slen,
			   u8 *dst, unsigned int *dlen, void *ctx)
{
	size_t out_len;
	struct zstd_ctx *zctx = ctx;
	const ZSTD_parameters params = zstd_params();

	out_len = ZSTD_compressCCtx(zctx->cctx, dst, *dlen, src, slen, params);
	if (ZSTD_isError(out_len))
		return -EINVAL;
	*dlen = out_len;
	return 0;
}