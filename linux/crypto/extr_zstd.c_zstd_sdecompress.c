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
struct crypto_scomp {int dummy; } ;

/* Variables and functions */
 int __zstd_decompress (int /*<<< orphan*/  const*,unsigned int,int /*<<< orphan*/ *,unsigned int*,void*) ; 

__attribute__((used)) static int zstd_sdecompress(struct crypto_scomp *tfm, const u8 *src,
			    unsigned int slen, u8 *dst, unsigned int *dlen,
			    void *ctx)
{
	return __zstd_decompress(src, slen, dst, dlen, ctx);
}