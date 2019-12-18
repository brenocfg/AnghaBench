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
struct p8_aes_ctx {int /*<<< orphan*/  enc_key; int /*<<< orphan*/  fallback; } ;
struct crypto_tfm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  aes_p8_encrypt (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_cipher_encrypt_one (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  crypto_simd_usable () ; 
 struct p8_aes_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  disable_kernel_vsx () ; 
 int /*<<< orphan*/  enable_kernel_vsx () ; 
 int /*<<< orphan*/  pagefault_disable () ; 
 int /*<<< orphan*/  pagefault_enable () ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 

__attribute__((used)) static void p8_aes_encrypt(struct crypto_tfm *tfm, u8 *dst, const u8 *src)
{
	struct p8_aes_ctx *ctx = crypto_tfm_ctx(tfm);

	if (!crypto_simd_usable()) {
		crypto_cipher_encrypt_one(ctx->fallback, dst, src);
	} else {
		preempt_disable();
		pagefault_disable();
		enable_kernel_vsx();
		aes_p8_encrypt(src, dst, &ctx->enc_key);
		disable_kernel_vsx();
		pagefault_enable();
		preempt_enable();
	}
}