#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/ * expkey; } ;
struct des3_ede_x86_ctx {TYPE_1__ enc; } ;

/* Variables and functions */
 int /*<<< orphan*/  des3_ede_x86_64_crypt_blk_3way (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static inline void des3_ede_enc_blk_3way(struct des3_ede_x86_ctx *ctx, u8 *dst,
					 const u8 *src)
{
	u32 *enc_ctx = ctx->enc.expkey;

	des3_ede_x86_64_crypt_blk_3way(enc_ctx, dst, src);
}