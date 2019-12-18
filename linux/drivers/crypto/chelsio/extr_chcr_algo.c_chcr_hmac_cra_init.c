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
struct hmac_ctx {int /*<<< orphan*/  base_hash; } ;
struct crypto_tfm {int dummy; } ;
struct chcr_context {int dummy; } ;
struct chcr_ahash_req_ctx {int dummy; } ;

/* Variables and functions */
 struct hmac_ctx* HMAC_CTX (struct chcr_context*) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __crypto_ahash_cast (struct crypto_tfm*) ; 
 int /*<<< orphan*/  chcr_alloc_shash (unsigned int) ; 
 int chcr_device_init (struct chcr_context*) ; 
 unsigned int crypto_ahash_digestsize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_ahash_set_reqsize (int /*<<< orphan*/ ,int) ; 
 struct chcr_context* crypto_tfm_ctx (struct crypto_tfm*) ; 

__attribute__((used)) static int chcr_hmac_cra_init(struct crypto_tfm *tfm)
{
	struct chcr_context *ctx = crypto_tfm_ctx(tfm);
	struct hmac_ctx *hmacctx = HMAC_CTX(ctx);
	unsigned int digestsize =
		crypto_ahash_digestsize(__crypto_ahash_cast(tfm));

	crypto_ahash_set_reqsize(__crypto_ahash_cast(tfm),
				 sizeof(struct chcr_ahash_req_ctx));
	hmacctx->base_hash = chcr_alloc_shash(digestsize);
	if (IS_ERR(hmacctx->base_hash))
		return PTR_ERR(hmacctx->base_hash);
	return chcr_device_init(crypto_tfm_ctx(tfm));
}