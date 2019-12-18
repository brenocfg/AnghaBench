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
struct crypto_ahash {int dummy; } ;
struct chcr_ahash_req_ctx {int /*<<< orphan*/  partial_hash; int /*<<< orphan*/  bfr2; int /*<<< orphan*/  skbfr; int /*<<< orphan*/  bfr1; int /*<<< orphan*/  reqbfr; scalar_t__ reqlen; scalar_t__ data_len; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 struct chcr_ahash_req_ctx* ahash_request_ctx (struct ahash_request*) ; 
 int /*<<< orphan*/  copy_hash_init_values (int /*<<< orphan*/ ,int) ; 
 int crypto_ahash_digestsize (struct crypto_ahash*) ; 
 struct crypto_ahash* crypto_ahash_reqtfm (struct ahash_request*) ; 

__attribute__((used)) static int chcr_sha_init(struct ahash_request *areq)
{
	struct chcr_ahash_req_ctx *req_ctx = ahash_request_ctx(areq);
	struct crypto_ahash *tfm = crypto_ahash_reqtfm(areq);
	int digestsize =  crypto_ahash_digestsize(tfm);

	req_ctx->data_len = 0;
	req_ctx->reqlen = 0;
	req_ctx->reqbfr = req_ctx->bfr1;
	req_ctx->skbfr = req_ctx->bfr2;
	copy_hash_init_values(req_ctx->partial_hash, digestsize);

	return 0;
}