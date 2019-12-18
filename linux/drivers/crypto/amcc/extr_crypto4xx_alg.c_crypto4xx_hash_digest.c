#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct scatterlist {int dummy; } ;
struct crypto_ahash {int dummy; } ;
struct crypto4xx_ctx {int /*<<< orphan*/  sa_len; int /*<<< orphan*/  sa_in; } ;
struct TYPE_2__ {int /*<<< orphan*/  tfm; } ;
struct ahash_request {int /*<<< orphan*/  nbytes; int /*<<< orphan*/  src; TYPE_1__ base; int /*<<< orphan*/  result; } ;

/* Variables and functions */
 int crypto4xx_build_pd (TYPE_1__*,struct crypto4xx_ctx*,int /*<<< orphan*/ ,struct scatterlist*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 unsigned int crypto_ahash_digestsize (struct crypto_ahash*) ; 
 struct crypto_ahash* crypto_ahash_reqtfm (struct ahash_request*) ; 
 struct crypto4xx_ctx* crypto_tfm_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_init_one (struct scatterlist*,int /*<<< orphan*/ ,unsigned int) ; 

int crypto4xx_hash_digest(struct ahash_request *req)
{
	struct crypto_ahash *ahash = crypto_ahash_reqtfm(req);
	struct crypto4xx_ctx *ctx = crypto_tfm_ctx(req->base.tfm);
	struct scatterlist dst;
	unsigned int ds = crypto_ahash_digestsize(ahash);

	sg_init_one(&dst, req->result, ds);

	return crypto4xx_build_pd(&req->base, ctx, req->src, &dst,
				  req->nbytes, NULL, 0, ctx->sa_in,
				  ctx->sa_len, 0, NULL);
}