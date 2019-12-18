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
struct shash_desc {int dummy; } ;
struct sha1_ce_state {scalar_t__ finalize; } ;
typedef  int /*<<< orphan*/  sha1_block_fn ;

/* Variables and functions */
 int crypto_sha1_finup (struct shash_desc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_simd_usable () ; 
 int /*<<< orphan*/  kernel_neon_begin () ; 
 int /*<<< orphan*/  kernel_neon_end () ; 
 int /*<<< orphan*/  sha1_base_do_finalize (struct shash_desc*,int /*<<< orphan*/ *) ; 
 int sha1_base_finish (struct shash_desc*,int /*<<< orphan*/ *) ; 
 scalar_t__ sha1_ce_transform ; 
 struct sha1_ce_state* shash_desc_ctx (struct shash_desc*) ; 

__attribute__((used)) static int sha1_ce_final(struct shash_desc *desc, u8 *out)
{
	struct sha1_ce_state *sctx = shash_desc_ctx(desc);

	if (!crypto_simd_usable())
		return crypto_sha1_finup(desc, NULL, 0, out);

	sctx->finalize = 0;
	kernel_neon_begin();
	sha1_base_do_finalize(desc, (sha1_block_fn *)sha1_ce_transform);
	kernel_neon_end();
	return sha1_base_finish(desc, out);
}