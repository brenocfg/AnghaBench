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
struct p8_aes_ctx {int /*<<< orphan*/  fallback; int /*<<< orphan*/  dec_key; int /*<<< orphan*/  enc_key; } ;
struct crypto_tfm {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int aes_p8_set_decrypt_key (int /*<<< orphan*/  const*,unsigned int,int /*<<< orphan*/ *) ; 
 int aes_p8_set_encrypt_key (int /*<<< orphan*/  const*,unsigned int,int /*<<< orphan*/ *) ; 
 int crypto_cipher_setkey (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 
 struct p8_aes_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  disable_kernel_vsx () ; 
 int /*<<< orphan*/  enable_kernel_vsx () ; 
 int /*<<< orphan*/  pagefault_disable () ; 
 int /*<<< orphan*/  pagefault_enable () ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 

__attribute__((used)) static int p8_aes_setkey(struct crypto_tfm *tfm, const u8 *key,
			 unsigned int keylen)
{
	int ret;
	struct p8_aes_ctx *ctx = crypto_tfm_ctx(tfm);

	preempt_disable();
	pagefault_disable();
	enable_kernel_vsx();
	ret = aes_p8_set_encrypt_key(key, keylen * 8, &ctx->enc_key);
	ret |= aes_p8_set_decrypt_key(key, keylen * 8, &ctx->dec_key);
	disable_kernel_vsx();
	pagefault_enable();
	preempt_enable();

	ret |= crypto_cipher_setkey(ctx->fallback, key, keylen);

	return ret ? -EINVAL : 0;
}