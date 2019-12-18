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
struct lzorle_ctx {int /*<<< orphan*/  lzorle_comp_mem; } ;
struct crypto_tfm {int dummy; } ;

/* Variables and functions */
 int __lzorle_compress (int /*<<< orphan*/  const*,unsigned int,int /*<<< orphan*/ *,unsigned int*,int /*<<< orphan*/ ) ; 
 struct lzorle_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 

__attribute__((used)) static int lzorle_compress(struct crypto_tfm *tfm, const u8 *src,
			unsigned int slen, u8 *dst, unsigned int *dlen)
{
	struct lzorle_ctx *ctx = crypto_tfm_ctx(tfm);

	return __lzorle_compress(src, slen, dst, dlen, ctx->lzorle_comp_mem);
}