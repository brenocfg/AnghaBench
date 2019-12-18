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
struct safexcel_ahash_req {int hmac; void* block_sz; int /*<<< orphan*/  state_sz; int /*<<< orphan*/  digest; void* processed; void* len; int /*<<< orphan*/  state; } ;
struct safexcel_ahash_ctx {int /*<<< orphan*/  alg; int /*<<< orphan*/  ipad; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONTEXT_CONTROL_CRYPTO_ALG_SHA512 ; 
 int /*<<< orphan*/  CONTEXT_CONTROL_DIGEST_PRECOMPUTED ; 
 void* SHA512_BLOCK_SIZE ; 
 int /*<<< orphan*/  SHA512_DIGEST_SIZE ; 
 struct safexcel_ahash_req* ahash_request_ctx (struct ahash_request*) ; 
 struct safexcel_ahash_ctx* crypto_ahash_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_ahash_reqtfm (struct ahash_request*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct safexcel_ahash_req*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int safexcel_hmac_sha512_init(struct ahash_request *areq)
{
	struct safexcel_ahash_ctx *ctx = crypto_ahash_ctx(crypto_ahash_reqtfm(areq));
	struct safexcel_ahash_req *req = ahash_request_ctx(areq);

	memset(req, 0, sizeof(*req));

	/* Start from ipad precompute */
	memcpy(req->state, ctx->ipad, SHA512_DIGEST_SIZE);
	/* Already processed the key^ipad part now! */
	req->len	= SHA512_BLOCK_SIZE;
	req->processed	= SHA512_BLOCK_SIZE;

	ctx->alg = CONTEXT_CONTROL_CRYPTO_ALG_SHA512;
	req->digest = CONTEXT_CONTROL_DIGEST_PRECOMPUTED;
	req->state_sz = SHA512_DIGEST_SIZE;
	req->block_sz = SHA512_BLOCK_SIZE;
	req->hmac = true;

	return 0;
}