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
struct deflate_ctx {int dummy; } ;
struct crypto_tfm {int dummy; } ;

/* Variables and functions */
 int __deflate_decompress (int /*<<< orphan*/  const*,unsigned int,int /*<<< orphan*/ *,unsigned int*,struct deflate_ctx*) ; 
 struct deflate_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 

__attribute__((used)) static int deflate_decompress(struct crypto_tfm *tfm, const u8 *src,
			      unsigned int slen, u8 *dst, unsigned int *dlen)
{
	struct deflate_ctx *dctx = crypto_tfm_ctx(tfm);

	return __deflate_decompress(src, slen, dst, dlen, dctx);
}