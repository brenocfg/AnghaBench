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
 struct crypto_aes_ctx* aes_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aes_decrypt (struct crypto_aes_ctx*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  aesni_dec (struct crypto_aes_ctx*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  crypto_simd_usable () ; 
 int /*<<< orphan*/  crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  kernel_fpu_begin () ; 
 int /*<<< orphan*/  kernel_fpu_end () ; 

__attribute__((used)) static void aesni_decrypt(struct crypto_tfm *tfm, u8 *dst, const u8 *src)
{
	struct crypto_aes_ctx *ctx = aes_ctx(crypto_tfm_ctx(tfm));

	if (!crypto_simd_usable()) {
		aes_decrypt(ctx, dst, src);
	} else {
		kernel_fpu_begin();
		aesni_dec(ctx, dst, src);
		kernel_fpu_end();
	}
}