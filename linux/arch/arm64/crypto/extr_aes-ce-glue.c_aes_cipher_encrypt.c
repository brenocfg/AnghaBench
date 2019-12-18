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
struct crypto_aes_ctx {int /*<<< orphan*/  key_enc; } ;

/* Variables and functions */
 int /*<<< orphan*/  __aes_ce_encrypt (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aes_encrypt (struct crypto_aes_ctx*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  crypto_simd_usable () ; 
 struct crypto_aes_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  kernel_neon_begin () ; 
 int /*<<< orphan*/  kernel_neon_end () ; 
 int /*<<< orphan*/  num_rounds (struct crypto_aes_ctx*) ; 

__attribute__((used)) static void aes_cipher_encrypt(struct crypto_tfm *tfm, u8 dst[], u8 const src[])
{
	struct crypto_aes_ctx *ctx = crypto_tfm_ctx(tfm);

	if (!crypto_simd_usable()) {
		aes_encrypt(ctx, dst, src);
		return;
	}

	kernel_neon_begin();
	__aes_ce_encrypt(ctx->key_enc, dst, src, num_rounds(ctx));
	kernel_neon_end();
}