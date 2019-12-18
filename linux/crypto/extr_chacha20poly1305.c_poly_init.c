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
struct poly_req {int /*<<< orphan*/  req; } ;
struct TYPE_2__ {struct poly_req poly; } ;
struct chachapoly_req_ctx {int /*<<< orphan*/  flags; TYPE_1__ u; } ;
struct chachapoly_ctx {int /*<<< orphan*/  poly; } ;
struct aead_request {int dummy; } ;

/* Variables and functions */
 struct chachapoly_req_ctx* aead_request_ctx (struct aead_request*) ; 
 int /*<<< orphan*/  ahash_request_set_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct aead_request*) ; 
 int /*<<< orphan*/  ahash_request_set_tfm (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct chachapoly_ctx* crypto_aead_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_aead_reqtfm (struct aead_request*) ; 
 int crypto_ahash_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poly_init_done ; 
 int poly_setkey (struct aead_request*) ; 

__attribute__((used)) static int poly_init(struct aead_request *req)
{
	struct chachapoly_ctx *ctx = crypto_aead_ctx(crypto_aead_reqtfm(req));
	struct chachapoly_req_ctx *rctx = aead_request_ctx(req);
	struct poly_req *preq = &rctx->u.poly;
	int err;

	ahash_request_set_callback(&preq->req, rctx->flags,
				   poly_init_done, req);
	ahash_request_set_tfm(&preq->req, ctx->poly);

	err = crypto_ahash_init(&preq->req);
	if (err)
		return err;

	return poly_setkey(req);
}