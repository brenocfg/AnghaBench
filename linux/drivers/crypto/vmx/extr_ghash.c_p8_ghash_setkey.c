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
typedef  int /*<<< orphan*/  u64 ;
struct p8_ghash_ctx {int /*<<< orphan*/  key; int /*<<< orphan*/  htable; } ;
struct crypto_shash {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int GHASH_BLOCK_SIZE ; 
 int /*<<< orphan*/  crypto_shash_tfm (struct crypto_shash*) ; 
 struct p8_ghash_ctx* crypto_tfm_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_kernel_vsx () ; 
 int /*<<< orphan*/  enable_kernel_vsx () ; 
 int /*<<< orphan*/  gcm_init_p8 (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  pagefault_disable () ; 
 int /*<<< orphan*/  pagefault_enable () ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 

__attribute__((used)) static int p8_ghash_setkey(struct crypto_shash *tfm, const u8 *key,
			   unsigned int keylen)
{
	struct p8_ghash_ctx *ctx = crypto_tfm_ctx(crypto_shash_tfm(tfm));

	if (keylen != GHASH_BLOCK_SIZE)
		return -EINVAL;

	preempt_disable();
	pagefault_disable();
	enable_kernel_vsx();
	gcm_init_p8(ctx->htable, (const u64 *) key);
	disable_kernel_vsx();
	pagefault_enable();
	preempt_enable();

	memcpy(&ctx->key, key, GHASH_BLOCK_SIZE);

	return 0;
}