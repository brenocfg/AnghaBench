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
struct shash_desc {int /*<<< orphan*/  tfm; } ;
struct ghash_desc_ctx {int bytes; int /*<<< orphan*/ * buffer; } ;
struct ghash_ctx {int /*<<< orphan*/  shash; } ;

/* Variables and functions */
 int GHASH_BLOCK_SIZE ; 
 int /*<<< orphan*/  clmul_ghash_mul (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clmul_ghash_update (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int,int /*<<< orphan*/ *) ; 
 struct ghash_ctx* crypto_shash_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kernel_fpu_begin () ; 
 int /*<<< orphan*/  kernel_fpu_end () ; 
 int min (unsigned int,int) ; 
 struct ghash_desc_ctx* shash_desc_ctx (struct shash_desc*) ; 

__attribute__((used)) static int ghash_update(struct shash_desc *desc,
			 const u8 *src, unsigned int srclen)
{
	struct ghash_desc_ctx *dctx = shash_desc_ctx(desc);
	struct ghash_ctx *ctx = crypto_shash_ctx(desc->tfm);
	u8 *dst = dctx->buffer;

	kernel_fpu_begin();
	if (dctx->bytes) {
		int n = min(srclen, dctx->bytes);
		u8 *pos = dst + (GHASH_BLOCK_SIZE - dctx->bytes);

		dctx->bytes -= n;
		srclen -= n;

		while (n--)
			*pos++ ^= *src++;

		if (!dctx->bytes)
			clmul_ghash_mul(dst, &ctx->shash);
	}

	clmul_ghash_update(dst, src, srclen, &ctx->shash);
	kernel_fpu_end();

	if (srclen & 0xf) {
		src += srclen - (srclen & 0xf);
		srclen &= 0xf;
		dctx->bytes = GHASH_BLOCK_SIZE - srclen;
		while (srclen--)
			*dst++ ^= *src++;
	}

	return 0;
}