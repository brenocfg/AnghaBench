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
struct crypto_aead {int dummy; } ;
struct chacha_req {int /*<<< orphan*/  req; int /*<<< orphan*/  iv; int /*<<< orphan*/  src; } ;
struct TYPE_2__ {struct chacha_req chacha; } ;
struct chachapoly_req_ctx {int assoclen; int /*<<< orphan*/  flags; int /*<<< orphan*/  key; TYPE_1__ u; } ;
struct chachapoly_ctx {int /*<<< orphan*/  chacha; } ;
struct aead_request {int assoclen; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  POLY1305_KEY_SIZE ; 
 struct chachapoly_req_ctx* aead_request_ctx (struct aead_request*) ; 
 int /*<<< orphan*/  chacha_iv (int /*<<< orphan*/ ,struct aead_request*,int /*<<< orphan*/ ) ; 
 struct chachapoly_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 int crypto_aead_ivsize (struct crypto_aead*) ; 
 struct crypto_aead* crypto_aead_reqtfm (struct aead_request*) ; 
 int crypto_skcipher_decrypt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  poly_genkey_done ; 
 int poly_init (struct aead_request*) ; 
 int /*<<< orphan*/  sg_init_one (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skcipher_request_set_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct aead_request*) ; 
 int /*<<< orphan*/  skcipher_request_set_crypt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skcipher_request_set_tfm (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int poly_genkey(struct aead_request *req)
{
	struct crypto_aead *tfm = crypto_aead_reqtfm(req);
	struct chachapoly_ctx *ctx = crypto_aead_ctx(tfm);
	struct chachapoly_req_ctx *rctx = aead_request_ctx(req);
	struct chacha_req *creq = &rctx->u.chacha;
	int err;

	rctx->assoclen = req->assoclen;

	if (crypto_aead_ivsize(tfm) == 8) {
		if (rctx->assoclen < 8)
			return -EINVAL;
		rctx->assoclen -= 8;
	}

	memset(rctx->key, 0, sizeof(rctx->key));
	sg_init_one(creq->src, rctx->key, sizeof(rctx->key));

	chacha_iv(creq->iv, req, 0);

	skcipher_request_set_callback(&creq->req, rctx->flags,
				      poly_genkey_done, req);
	skcipher_request_set_tfm(&creq->req, ctx->chacha);
	skcipher_request_set_crypt(&creq->req, creq->src, creq->src,
				   POLY1305_KEY_SIZE, creq->iv);

	err = crypto_skcipher_decrypt(&creq->req);
	if (err)
		return err;

	return poly_init(req);
}