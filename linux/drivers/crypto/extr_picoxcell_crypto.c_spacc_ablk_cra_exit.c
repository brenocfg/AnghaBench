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
struct spacc_ablk_ctx {int /*<<< orphan*/  sw_cipher; } ;
struct crypto_tfm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_free_sync_skcipher (int /*<<< orphan*/ ) ; 
 struct spacc_ablk_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 

__attribute__((used)) static void spacc_ablk_cra_exit(struct crypto_tfm *tfm)
{
	struct spacc_ablk_ctx *ctx = crypto_tfm_ctx(tfm);

	crypto_free_sync_skcipher(ctx->sw_cipher);
}