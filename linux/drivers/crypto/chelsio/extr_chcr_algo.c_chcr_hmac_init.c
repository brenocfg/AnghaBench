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
struct hmac_ctx {int /*<<< orphan*/  ipad; } ;
struct crypto_ahash {int dummy; } ;
struct chcr_ahash_req_ctx {unsigned int data_len; int /*<<< orphan*/  partial_hash; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 struct hmac_ctx* HMAC_CTX (int /*<<< orphan*/ ) ; 
 unsigned int SHA224_DIGEST_SIZE ; 
 unsigned int SHA256_DIGEST_SIZE ; 
 unsigned int SHA384_DIGEST_SIZE ; 
 unsigned int SHA512_DIGEST_SIZE ; 
 struct chcr_ahash_req_ctx* ahash_request_ctx (struct ahash_request*) ; 
 int /*<<< orphan*/  chcr_sha_init (struct ahash_request*) ; 
 unsigned int crypto_ahash_digestsize (struct crypto_ahash*) ; 
 struct crypto_ahash* crypto_ahash_reqtfm (struct ahash_request*) ; 
 int /*<<< orphan*/  crypto_ahash_tfm (struct crypto_ahash*) ; 
 unsigned int crypto_tfm_alg_blocksize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h_ctx (struct crypto_ahash*) ; 
 scalar_t__ is_hmac (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int chcr_hmac_init(struct ahash_request *areq)
{
	struct chcr_ahash_req_ctx *req_ctx = ahash_request_ctx(areq);
	struct crypto_ahash *rtfm = crypto_ahash_reqtfm(areq);
	struct hmac_ctx *hmacctx = HMAC_CTX(h_ctx(rtfm));
	unsigned int digestsize = crypto_ahash_digestsize(rtfm);
	unsigned int bs = crypto_tfm_alg_blocksize(crypto_ahash_tfm(rtfm));

	chcr_sha_init(areq);
	req_ctx->data_len = bs;
	if (is_hmac(crypto_ahash_tfm(rtfm))) {
		if (digestsize == SHA224_DIGEST_SIZE)
			memcpy(req_ctx->partial_hash, hmacctx->ipad,
			       SHA256_DIGEST_SIZE);
		else if (digestsize == SHA384_DIGEST_SIZE)
			memcpy(req_ctx->partial_hash, hmacctx->ipad,
			       SHA512_DIGEST_SIZE);
		else
			memcpy(req_ctx->partial_hash, hmacctx->ipad,
			       digestsize);
	}
	return 0;
}