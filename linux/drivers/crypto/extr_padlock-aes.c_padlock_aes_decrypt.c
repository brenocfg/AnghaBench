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
struct crypto_tfm {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  encrypt; int /*<<< orphan*/  decrypt; } ;
struct aes_ctx {TYPE_1__ cword; int /*<<< orphan*/  D; } ;

/* Variables and functions */
 struct aes_ctx* aes_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  ecb_crypt (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  padlock_reset_key (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  padlock_store_cword (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void padlock_aes_decrypt(struct crypto_tfm *tfm, u8 *out, const u8 *in)
{
	struct aes_ctx *ctx = aes_ctx(tfm);

	padlock_reset_key(&ctx->cword.encrypt);
	ecb_crypt(in, out, ctx->D, &ctx->cword.decrypt, 1);
	padlock_store_cword(&ctx->cword.encrypt);
}