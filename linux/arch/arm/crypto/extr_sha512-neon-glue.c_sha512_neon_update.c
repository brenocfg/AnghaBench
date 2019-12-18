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
struct sha512_state {unsigned int* count; } ;
typedef  int /*<<< orphan*/  sha512_block_fn ;

/* Variables and functions */
 unsigned int SHA512_BLOCK_SIZE ; 
 int /*<<< orphan*/  crypto_simd_usable () ; 
 int /*<<< orphan*/  kernel_neon_begin () ; 
 int /*<<< orphan*/  kernel_neon_end () ; 
 int sha512_arm_update (struct shash_desc*,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  sha512_base_do_update (struct shash_desc*,int /*<<< orphan*/  const*,unsigned int,int /*<<< orphan*/ *) ; 
 scalar_t__ sha512_block_data_order_neon ; 
 struct sha512_state* shash_desc_ctx (struct shash_desc*) ; 

__attribute__((used)) static int sha512_neon_update(struct shash_desc *desc, const u8 *data,
			      unsigned int len)
{
	struct sha512_state *sctx = shash_desc_ctx(desc);

	if (!crypto_simd_usable() ||
	    (sctx->count[0] % SHA512_BLOCK_SIZE) + len < SHA512_BLOCK_SIZE)
		return sha512_arm_update(desc, data, len);

	kernel_neon_begin();
	sha512_base_do_update(desc, data, len,
		(sha512_block_fn *)sha512_block_data_order_neon);
	kernel_neon_end();

	return 0;
}