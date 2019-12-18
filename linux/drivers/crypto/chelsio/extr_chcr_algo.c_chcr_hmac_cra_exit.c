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
struct hmac_ctx {int /*<<< orphan*/ * base_hash; } ;
struct crypto_tfm {int dummy; } ;
struct chcr_context {int dummy; } ;

/* Variables and functions */
 struct hmac_ctx* HMAC_CTX (struct chcr_context*) ; 
 int /*<<< orphan*/  chcr_free_shash (int /*<<< orphan*/ *) ; 
 struct chcr_context* crypto_tfm_ctx (struct crypto_tfm*) ; 

__attribute__((used)) static void chcr_hmac_cra_exit(struct crypto_tfm *tfm)
{
	struct chcr_context *ctx = crypto_tfm_ctx(tfm);
	struct hmac_ctx *hmacctx = HMAC_CTX(ctx);

	if (hmacctx->base_hash) {
		chcr_free_shash(hmacctx->base_hash);
		hmacctx->base_hash = NULL;
	}
}