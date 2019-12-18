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
struct crypto_skcipher {int reqsize; int /*<<< orphan*/  base; } ;
struct artpec6_cryptotfm_context {int /*<<< orphan*/  crypto_type; int /*<<< orphan*/  fallback; } ;
struct artpec6_crypto_request_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARTPEC6_CRYPTO_CIPHER_AES_CTR ; 
 int /*<<< orphan*/  CRYPTO_ALG_NEED_FALLBACK ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_alloc_sync_skcipher (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct artpec6_cryptotfm_context* crypto_skcipher_ctx (struct crypto_skcipher*) ; 
 int /*<<< orphan*/  crypto_tfm_alg_name (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int artpec6_crypto_aes_ctr_init(struct crypto_skcipher *tfm)
{
	struct artpec6_cryptotfm_context *ctx = crypto_skcipher_ctx(tfm);

	ctx->fallback =
		crypto_alloc_sync_skcipher(crypto_tfm_alg_name(&tfm->base),
					   0, CRYPTO_ALG_NEED_FALLBACK);
	if (IS_ERR(ctx->fallback))
		return PTR_ERR(ctx->fallback);

	tfm->reqsize = sizeof(struct artpec6_crypto_request_context);
	ctx->crypto_type = ARTPEC6_CRYPTO_CIPHER_AES_CTR;

	return 0;
}