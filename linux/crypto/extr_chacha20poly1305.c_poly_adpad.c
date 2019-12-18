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
struct poly_req {int /*<<< orphan*/  req; int /*<<< orphan*/  src; int /*<<< orphan*/  pad; } ;
struct TYPE_2__ {struct poly_req poly; } ;
struct chachapoly_req_ctx {unsigned int assoclen; int /*<<< orphan*/  flags; TYPE_1__ u; } ;
struct chachapoly_ctx {int /*<<< orphan*/  poly; } ;
struct aead_request {int dummy; } ;

/* Variables and functions */
 unsigned int POLY1305_BLOCK_SIZE ; 
 struct chachapoly_req_ctx* aead_request_ctx (struct aead_request*) ; 
 int /*<<< orphan*/  ahash_request_set_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct aead_request*) ; 
 int /*<<< orphan*/  ahash_request_set_crypt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  ahash_request_set_tfm (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct chachapoly_ctx* crypto_aead_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_aead_reqtfm (struct aead_request*) ; 
 int crypto_ahash_update (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  poly_adpad_done ; 
 int poly_cipher (struct aead_request*) ; 
 int /*<<< orphan*/  sg_init_one (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int poly_adpad(struct aead_request *req)
{
	struct chachapoly_ctx *ctx = crypto_aead_ctx(crypto_aead_reqtfm(req));
	struct chachapoly_req_ctx *rctx = aead_request_ctx(req);
	struct poly_req *preq = &rctx->u.poly;
	unsigned int padlen;
	int err;

	padlen = -rctx->assoclen % POLY1305_BLOCK_SIZE;
	memset(preq->pad, 0, sizeof(preq->pad));
	sg_init_one(preq->src, preq->pad, padlen);

	ahash_request_set_callback(&preq->req, rctx->flags,
				   poly_adpad_done, req);
	ahash_request_set_tfm(&preq->req, ctx->poly);
	ahash_request_set_crypt(&preq->req, preq->src, NULL, padlen);

	err = crypto_ahash_update(&preq->req);
	if (err)
		return err;

	return poly_cipher(req);
}