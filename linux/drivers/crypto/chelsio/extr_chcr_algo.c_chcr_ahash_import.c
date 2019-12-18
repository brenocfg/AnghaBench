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
struct chcr_ahash_req_ctx {int /*<<< orphan*/  partial_hash; int /*<<< orphan*/  bfr1; int /*<<< orphan*/  bfr2; int /*<<< orphan*/  skbfr; int /*<<< orphan*/  reqbfr; int /*<<< orphan*/  data_len; int /*<<< orphan*/  reqlen; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHCR_HASH_MAX_BLOCK_SIZE_128 ; 
 int /*<<< orphan*/  CHCR_HASH_MAX_DIGEST_SIZE ; 
 struct chcr_ahash_req_ctx* ahash_request_ctx (struct ahash_request*) ; 
 int /*<<< orphan*/  chcr_init_hctx_per_wr (struct chcr_ahash_req_ctx*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int chcr_ahash_import(struct ahash_request *areq, const void *in)
{
	struct chcr_ahash_req_ctx *req_ctx = ahash_request_ctx(areq);
	struct chcr_ahash_req_ctx *state = (struct chcr_ahash_req_ctx *)in;

	req_ctx->reqlen = state->reqlen;
	req_ctx->data_len = state->data_len;
	req_ctx->reqbfr = req_ctx->bfr1;
	req_ctx->skbfr = req_ctx->bfr2;
	memcpy(req_ctx->bfr1, state->bfr1, CHCR_HASH_MAX_BLOCK_SIZE_128);
	memcpy(req_ctx->partial_hash, state->partial_hash,
	       CHCR_HASH_MAX_DIGEST_SIZE);
	chcr_init_hctx_per_wr(req_ctx);
	return 0;
}