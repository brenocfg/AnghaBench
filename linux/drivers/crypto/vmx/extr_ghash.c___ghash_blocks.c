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
struct p8_ghash_desc_ctx {scalar_t__ shash; } ;
struct p8_ghash_ctx {int /*<<< orphan*/  key; int /*<<< orphan*/  htable; } ;
typedef  int /*<<< orphan*/  be128 ;

/* Variables and functions */
 unsigned int GHASH_BLOCK_SIZE ; 
 scalar_t__ crypto_simd_usable () ; 
 int /*<<< orphan*/  crypto_xor (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  disable_kernel_vsx () ; 
 int /*<<< orphan*/  enable_kernel_vsx () ; 
 int /*<<< orphan*/  gcm_ghash_p8 (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  gf128mul_lle (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pagefault_disable () ; 
 int /*<<< orphan*/  pagefault_enable () ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 

__attribute__((used)) static inline void __ghash_blocks(struct p8_ghash_ctx *ctx,
				  struct p8_ghash_desc_ctx *dctx,
				  const u8 *src, unsigned int srclen)
{
	if (crypto_simd_usable()) {
		preempt_disable();
		pagefault_disable();
		enable_kernel_vsx();
		gcm_ghash_p8(dctx->shash, ctx->htable,
				src, srclen);
		disable_kernel_vsx();
		pagefault_enable();
		preempt_enable();
	} else {
		while (srclen >= GHASH_BLOCK_SIZE) {
			crypto_xor((u8 *)dctx->shash, src, GHASH_BLOCK_SIZE);
			gf128mul_lle((be128 *)dctx->shash, &ctx->key);
			srclen -= GHASH_BLOCK_SIZE;
			src += GHASH_BLOCK_SIZE;
		}
	}
}