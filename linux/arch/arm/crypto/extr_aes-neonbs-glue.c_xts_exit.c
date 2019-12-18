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
struct crypto_tfm {int dummy; } ;
struct aesbs_xts_ctx {int /*<<< orphan*/  cts_tfm; int /*<<< orphan*/  tweak_tfm; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_free_cipher (int /*<<< orphan*/ ) ; 
 struct aesbs_xts_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 

__attribute__((used)) static void xts_exit(struct crypto_tfm *tfm)
{
	struct aesbs_xts_ctx *ctx = crypto_tfm_ctx(tfm);

	crypto_free_cipher(ctx->tweak_tfm);
	crypto_free_cipher(ctx->cts_tfm);
}