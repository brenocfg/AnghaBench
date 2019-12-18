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
struct crypto_skcipher {int dummy; } ;
struct crypto_aes_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  aes_encrypt (struct crypto_aes_ctx*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 struct crypto_aes_ctx* crypto_skcipher_ctx (struct crypto_skcipher*) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 

__attribute__((used)) static void ctr_encrypt_one(struct crypto_skcipher *tfm, const u8 *src, u8 *dst)
{
	struct crypto_aes_ctx *ctx = crypto_skcipher_ctx(tfm);
	unsigned long flags;

	/*
	 * Temporarily disable interrupts to avoid races where
	 * cachelines are evicted when the CPU is interrupted
	 * to do something else.
	 */
	local_irq_save(flags);
	aes_encrypt(ctx, dst, src);
	local_irq_restore(flags);
}