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
struct crypto_tfm {int dummy; } ;
struct crypto_aes_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  aes_decrypt (struct crypto_aes_ctx const*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 struct crypto_aes_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 

__attribute__((used)) static void aesti_decrypt(struct crypto_tfm *tfm, u8 *out, const u8 *in)
{
	const struct crypto_aes_ctx *ctx = crypto_tfm_ctx(tfm);
	unsigned long flags;

	/*
	 * Temporarily disable interrupts to avoid races where cachelines are
	 * evicted when the CPU is interrupted to do something else.
	 */
	local_irq_save(flags);

	aes_decrypt(ctx, out, in);

	local_irq_restore(flags);
}