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
typedef  int /*<<< orphan*/  u8 ;
struct skcipher_request {int dummy; } ;
struct scatterlist {int dummy; } ;
struct crypto_authenc_ctx {int /*<<< orphan*/  enc; } ;
struct crypto_aead {int dummy; } ;
struct authenc_request_ctx {int /*<<< orphan*/  dst; int /*<<< orphan*/  src; scalar_t__ tail; } ;
struct authenc_instance_ctx {scalar_t__ reqoff; } ;
struct ahash_request {int /*<<< orphan*/ * result; int /*<<< orphan*/  nbytes; } ;
struct TYPE_2__ {int /*<<< orphan*/  data; int /*<<< orphan*/  complete; } ;
struct aead_request {int /*<<< orphan*/  iv; scalar_t__ cryptlen; TYPE_1__ base; int /*<<< orphan*/  assoclen; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
struct aead_instance {int dummy; } ;

/* Variables and functions */
 int EBADMSG ; 
 struct aead_instance* aead_alg_instance (struct crypto_aead*) ; 
 struct authenc_instance_ctx* aead_instance_ctx (struct aead_instance*) ; 
 struct authenc_request_ctx* aead_request_ctx (struct aead_request*) ; 
 int /*<<< orphan*/  aead_request_flags (struct aead_request*) ; 
 unsigned int crypto_aead_authsize (struct crypto_aead*) ; 
 struct crypto_authenc_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 struct crypto_aead* crypto_aead_reqtfm (struct aead_request*) ; 
 scalar_t__ crypto_memneq (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 int crypto_skcipher_decrypt (struct skcipher_request*) ; 
 struct scatterlist* scatterwalk_ffwd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scatterwalk_map_and_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skcipher_request_set_callback (struct skcipher_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skcipher_request_set_crypt (struct skcipher_request*,struct scatterlist*,struct scatterlist*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skcipher_request_set_tfm (struct skcipher_request*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int crypto_authenc_decrypt_tail(struct aead_request *req,
				       unsigned int flags)
{
	struct crypto_aead *authenc = crypto_aead_reqtfm(req);
	struct aead_instance *inst = aead_alg_instance(authenc);
	struct crypto_authenc_ctx *ctx = crypto_aead_ctx(authenc);
	struct authenc_instance_ctx *ictx = aead_instance_ctx(inst);
	struct authenc_request_ctx *areq_ctx = aead_request_ctx(req);
	struct ahash_request *ahreq = (void *)(areq_ctx->tail + ictx->reqoff);
	struct skcipher_request *skreq = (void *)(areq_ctx->tail +
						  ictx->reqoff);
	unsigned int authsize = crypto_aead_authsize(authenc);
	u8 *ihash = ahreq->result + authsize;
	struct scatterlist *src, *dst;

	scatterwalk_map_and_copy(ihash, req->src, ahreq->nbytes, authsize, 0);

	if (crypto_memneq(ihash, ahreq->result, authsize))
		return -EBADMSG;

	src = scatterwalk_ffwd(areq_ctx->src, req->src, req->assoclen);
	dst = src;

	if (req->src != req->dst)
		dst = scatterwalk_ffwd(areq_ctx->dst, req->dst, req->assoclen);

	skcipher_request_set_tfm(skreq, ctx->enc);
	skcipher_request_set_callback(skreq, aead_request_flags(req),
				      req->base.complete, req->base.data);
	skcipher_request_set_crypt(skreq, src, dst,
				   req->cryptlen - authsize, req->iv);

	return crypto_skcipher_decrypt(skreq);
}