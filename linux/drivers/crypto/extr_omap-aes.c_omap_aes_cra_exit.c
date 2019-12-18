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
struct omap_aes_ctx {int /*<<< orphan*/ * fallback; } ;
struct crypto_tfm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_free_sync_skcipher (int /*<<< orphan*/ *) ; 
 struct omap_aes_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 

__attribute__((used)) static void omap_aes_cra_exit(struct crypto_tfm *tfm)
{
	struct omap_aes_ctx *ctx = crypto_tfm_ctx(tfm);

	if (ctx->fallback)
		crypto_free_sync_skcipher(ctx->fallback);

	ctx->fallback = NULL;
}