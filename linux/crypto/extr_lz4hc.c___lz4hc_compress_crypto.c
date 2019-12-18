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

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  LZ4HC_DEFAULT_CLEVEL ; 
 int LZ4_compress_HC (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,unsigned int,unsigned int,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int __lz4hc_compress_crypto(const u8 *src, unsigned int slen,
				   u8 *dst, unsigned int *dlen, void *ctx)
{
	int out_len = LZ4_compress_HC(src, dst, slen,
		*dlen, LZ4HC_DEFAULT_CLEVEL, ctx);

	if (!out_len)
		return -EINVAL;

	*dlen = out_len;
	return 0;
}