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
struct shash_desc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  count; } ;
struct sha256_ce_state {int finalize; TYPE_1__ sst; } ;
typedef  int /*<<< orphan*/  sha256_block_fn ;

/* Variables and functions */
 unsigned int SHA256_BLOCK_SIZE ; 
 int /*<<< orphan*/  crypto_simd_usable () ; 
 int /*<<< orphan*/  kernel_neon_begin () ; 
 int /*<<< orphan*/  kernel_neon_end () ; 
 int /*<<< orphan*/  sha256_base_do_finalize (struct shash_desc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sha256_base_do_update (struct shash_desc*,int /*<<< orphan*/  const*,unsigned int,int /*<<< orphan*/ *) ; 
 int sha256_base_finish (struct shash_desc*,int /*<<< orphan*/ *) ; 
 scalar_t__ sha256_block_data_order ; 
 scalar_t__ sha2_ce_transform ; 
 struct sha256_ce_state* shash_desc_ctx (struct shash_desc*) ; 

__attribute__((used)) static int sha256_ce_finup(struct shash_desc *desc, const u8 *data,
			   unsigned int len, u8 *out)
{
	struct sha256_ce_state *sctx = shash_desc_ctx(desc);
	bool finalize = !sctx->sst.count && !(len % SHA256_BLOCK_SIZE) && len;

	if (!crypto_simd_usable()) {
		if (len)
			sha256_base_do_update(desc, data, len,
				(sha256_block_fn *)sha256_block_data_order);
		sha256_base_do_finalize(desc,
				(sha256_block_fn *)sha256_block_data_order);
		return sha256_base_finish(desc, out);
	}

	/*
	 * Allow the asm code to perform the finalization if there is no
	 * partial data and the input is a round multiple of the block size.
	 */
	sctx->finalize = finalize;

	kernel_neon_begin();
	sha256_base_do_update(desc, data, len,
			      (sha256_block_fn *)sha2_ce_transform);
	if (!finalize)
		sha256_base_do_finalize(desc,
					(sha256_block_fn *)sha2_ce_transform);
	kernel_neon_end();
	return sha256_base_finish(desc, out);
}