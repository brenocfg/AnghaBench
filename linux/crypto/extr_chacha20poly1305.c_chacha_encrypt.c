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
struct chacha_req {int /*<<< orphan*/  req; int /*<<< orphan*/  iv; } ;
struct TYPE_2__ {struct chacha_req chacha; } ;
struct chachapoly_req_ctx {int /*<<< orphan*/  flags; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; TYPE_1__ u; } ;
struct chachapoly_ctx {int /*<<< orphan*/  chacha; } ;
struct aead_request {int /*<<< orphan*/  cryptlen; int /*<<< orphan*/  assoclen; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;

/* Variables and functions */
 struct chachapoly_req_ctx* aead_request_ctx (struct aead_request*) ; 
 int /*<<< orphan*/  chacha_encrypt_done ; 
 int /*<<< orphan*/  chacha_iv (int /*<<< orphan*/ ,struct aead_request*,int) ; 
 struct chachapoly_ctx* crypto_aead_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_aead_reqtfm (struct aead_request*) ; 
 int crypto_skcipher_encrypt (int /*<<< orphan*/ *) ; 
 int poly_genkey (struct aead_request*) ; 
 struct scatterlist* scatterwalk_ffwd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skcipher_request_set_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct aead_request*) ; 
 int /*<<< orphan*/  skcipher_request_set_crypt (int /*<<< orphan*/ *,struct scatterlist*,struct scatterlist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skcipher_request_set_tfm (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int chacha_encrypt(struct aead_request *req)
{
	struct chachapoly_ctx *ctx = crypto_aead_ctx(crypto_aead_reqtfm(req));
	struct chachapoly_req_ctx *rctx = aead_request_ctx(req);
	struct chacha_req *creq = &rctx->u.chacha;
	struct scatterlist *src, *dst;
	int err;

	if (req->cryptlen == 0)
		goto skip;

	chacha_iv(creq->iv, req, 1);

	src = scatterwalk_ffwd(rctx->src, req->src, req->assoclen);
	dst = src;
	if (req->src != req->dst)
		dst = scatterwalk_ffwd(rctx->dst, req->dst, req->assoclen);

	skcipher_request_set_callback(&creq->req, rctx->flags,
				      chacha_encrypt_done, req);
	skcipher_request_set_tfm(&creq->req, ctx->chacha);
	skcipher_request_set_crypt(&creq->req, src, dst,
				   req->cryptlen, creq->iv);
	err = crypto_skcipher_encrypt(&creq->req);
	if (err)
		return err;

skip:
	return poly_genkey(req);
}