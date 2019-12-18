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
typedef  int /*<<< orphan*/  u8 ;
struct skcipher_request {int dummy; } ;
struct scatterlist {int dummy; } ;
struct crypto_ccm_req_priv_ctx {struct scatterlist* src; int /*<<< orphan*/  flags; struct scatterlist* dst; int /*<<< orphan*/ * idata; int /*<<< orphan*/ * odata; int /*<<< orphan*/ * auth_tag; struct skcipher_request skreq; } ;
struct crypto_ccm_ctx {int /*<<< orphan*/  ctr; } ;
struct crypto_aead {int dummy; } ;
struct aead_request {unsigned int cryptlen; scalar_t__ src; scalar_t__ dst; int /*<<< orphan*/  iv; } ;

/* Variables and functions */
 int EBADMSG ; 
 unsigned int crypto_aead_authsize (struct crypto_aead*) ; 
 struct crypto_ccm_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 struct crypto_aead* crypto_aead_reqtfm (struct aead_request*) ; 
 int crypto_ccm_auth (struct aead_request*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  crypto_ccm_decrypt_done ; 
 int crypto_ccm_init_crypt (struct aead_request*,int /*<<< orphan*/ *) ; 
 struct crypto_ccm_req_priv_ctx* crypto_ccm_reqctx (struct aead_request*) ; 
 scalar_t__ crypto_memneq (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 int crypto_skcipher_decrypt (struct skcipher_request*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  scatterwalk_map_and_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_next (struct scatterlist*) ; 
 int /*<<< orphan*/  skcipher_request_set_callback (struct skcipher_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct aead_request*) ; 
 int /*<<< orphan*/  skcipher_request_set_crypt (struct skcipher_request*,struct scatterlist*,struct scatterlist*,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skcipher_request_set_tfm (struct skcipher_request*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int crypto_ccm_decrypt(struct aead_request *req)
{
	struct crypto_aead *aead = crypto_aead_reqtfm(req);
	struct crypto_ccm_ctx *ctx = crypto_aead_ctx(aead);
	struct crypto_ccm_req_priv_ctx *pctx = crypto_ccm_reqctx(req);
	struct skcipher_request *skreq = &pctx->skreq;
	struct scatterlist *dst;
	unsigned int authsize = crypto_aead_authsize(aead);
	unsigned int cryptlen = req->cryptlen;
	u8 *authtag = pctx->auth_tag;
	u8 *odata = pctx->odata;
	u8 *iv = pctx->idata;
	int err;

	cryptlen -= authsize;

	err = crypto_ccm_init_crypt(req, authtag);
	if (err)
		return err;

	scatterwalk_map_and_copy(authtag, sg_next(pctx->src), cryptlen,
				 authsize, 0);

	dst = pctx->src;
	if (req->src != req->dst)
		dst = pctx->dst;

	memcpy(iv, req->iv, 16);

	skcipher_request_set_tfm(skreq, ctx->ctr);
	skcipher_request_set_callback(skreq, pctx->flags,
				      crypto_ccm_decrypt_done, req);
	skcipher_request_set_crypt(skreq, pctx->src, dst, cryptlen + 16, iv);
	err = crypto_skcipher_decrypt(skreq);
	if (err)
		return err;

	err = crypto_ccm_auth(req, sg_next(dst), cryptlen);
	if (err)
		return err;

	/* verify */
	if (crypto_memneq(authtag, odata, authsize))
		return -EBADMSG;

	return err;
}