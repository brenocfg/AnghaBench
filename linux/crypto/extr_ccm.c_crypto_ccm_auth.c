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
struct scatterlist {int dummy; } ;
struct ahash_request {int dummy; } ;
struct crypto_ccm_req_priv_ctx {int /*<<< orphan*/ * odata; int /*<<< orphan*/  flags; int /*<<< orphan*/ * idata; struct ahash_request ahreq; } ;
struct crypto_ccm_ctx {int /*<<< orphan*/  mac; } ;
struct crypto_aead {int dummy; } ;
struct aead_request {unsigned int assoclen; struct scatterlist* src; } ;

/* Variables and functions */
 int /*<<< orphan*/  ahash_request_set_callback (struct ahash_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ahash_request_set_crypt (struct ahash_request*,struct scatterlist*,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  ahash_request_set_tfm (struct ahash_request*,int /*<<< orphan*/ ) ; 
 struct crypto_ccm_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 struct crypto_aead* crypto_aead_reqtfm (struct aead_request*) ; 
 int crypto_ahash_finup (struct ahash_request*) ; 
 int crypto_ahash_init (struct ahash_request*) ; 
 int crypto_ahash_update (struct ahash_request*) ; 
 struct crypto_ccm_req_priv_ctx* crypto_ccm_reqctx (struct aead_request*) ; 
 int format_adata (int /*<<< orphan*/ *,unsigned int) ; 
 int format_input (int /*<<< orphan*/ *,struct aead_request*,unsigned int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sg_chain (struct scatterlist*,int,struct scatterlist*) ; 
 int /*<<< orphan*/  sg_init_table (struct scatterlist*,int) ; 
 int /*<<< orphan*/  sg_set_buf (struct scatterlist*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int crypto_ccm_auth(struct aead_request *req, struct scatterlist *plain,
			   unsigned int cryptlen)
{
	struct crypto_ccm_req_priv_ctx *pctx = crypto_ccm_reqctx(req);
	struct crypto_aead *aead = crypto_aead_reqtfm(req);
	struct crypto_ccm_ctx *ctx = crypto_aead_ctx(aead);
	struct ahash_request *ahreq = &pctx->ahreq;
	unsigned int assoclen = req->assoclen;
	struct scatterlist sg[3];
	u8 *odata = pctx->odata;
	u8 *idata = pctx->idata;
	int ilen, err;

	/* format control data for input */
	err = format_input(odata, req, cryptlen);
	if (err)
		goto out;

	sg_init_table(sg, 3);
	sg_set_buf(&sg[0], odata, 16);

	/* format associated data and compute into mac */
	if (assoclen) {
		ilen = format_adata(idata, assoclen);
		sg_set_buf(&sg[1], idata, ilen);
		sg_chain(sg, 3, req->src);
	} else {
		ilen = 0;
		sg_chain(sg, 2, req->src);
	}

	ahash_request_set_tfm(ahreq, ctx->mac);
	ahash_request_set_callback(ahreq, pctx->flags, NULL, NULL);
	ahash_request_set_crypt(ahreq, sg, NULL, assoclen + ilen + 16);
	err = crypto_ahash_init(ahreq);
	if (err)
		goto out;
	err = crypto_ahash_update(ahreq);
	if (err)
		goto out;

	/* we need to pad the MAC input to a round multiple of the block size */
	ilen = 16 - (assoclen + ilen) % 16;
	if (ilen < 16) {
		memset(idata, 0, ilen);
		sg_init_table(sg, 2);
		sg_set_buf(&sg[0], idata, ilen);
		if (plain)
			sg_chain(sg, 2, plain);
		plain = sg;
		cryptlen += ilen;
	}

	ahash_request_set_crypt(ahreq, plain, pctx->odata, cryptlen);
	err = crypto_ahash_finup(ahreq);
out:
	return err;
}