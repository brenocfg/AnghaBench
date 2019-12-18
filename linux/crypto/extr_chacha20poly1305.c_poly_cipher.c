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
struct poly_req {int /*<<< orphan*/  req; } ;
struct TYPE_2__ {struct poly_req poly; } ;
struct chachapoly_req_ctx {scalar_t__ cryptlen; int /*<<< orphan*/  flags; int /*<<< orphan*/  src; TYPE_1__ u; } ;
struct chachapoly_ctx {int /*<<< orphan*/  poly; } ;
struct aead_request {scalar_t__ cryptlen; int /*<<< orphan*/  assoclen; struct scatterlist* dst; struct scatterlist* src; } ;

/* Variables and functions */
 struct chachapoly_req_ctx* aead_request_ctx (struct aead_request*) ; 
 int /*<<< orphan*/  ahash_request_set_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct aead_request*) ; 
 int /*<<< orphan*/  ahash_request_set_crypt (int /*<<< orphan*/ *,struct scatterlist*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  ahash_request_set_tfm (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct chachapoly_ctx* crypto_aead_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_aead_reqtfm (struct aead_request*) ; 
 int crypto_ahash_update (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poly_cipher_done ; 
 int poly_cipherpad (struct aead_request*) ; 
 struct scatterlist* scatterwalk_ffwd (int /*<<< orphan*/ ,struct scatterlist*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int poly_cipher(struct aead_request *req)
{
	struct chachapoly_ctx *ctx = crypto_aead_ctx(crypto_aead_reqtfm(req));
	struct chachapoly_req_ctx *rctx = aead_request_ctx(req);
	struct poly_req *preq = &rctx->u.poly;
	struct scatterlist *crypt = req->src;
	int err;

	if (rctx->cryptlen == req->cryptlen) /* encrypting */
		crypt = req->dst;

	crypt = scatterwalk_ffwd(rctx->src, crypt, req->assoclen);

	ahash_request_set_callback(&preq->req, rctx->flags,
				   poly_cipher_done, req);
	ahash_request_set_tfm(&preq->req, ctx->poly);
	ahash_request_set_crypt(&preq->req, crypt, NULL, rctx->cryptlen);

	err = crypto_ahash_update(&preq->req);
	if (err)
		return err;

	return poly_cipherpad(req);
}