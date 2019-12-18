#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct ulptx_sgl {int dummy; } ;
struct TYPE_19__ {TYPE_5__* pdev; } ;
struct uld_ctx {TYPE_6__ lldi; } ;
struct sk_buff {int dummy; } ;
struct hmac_ctx {int /*<<< orphan*/  opad; } ;
struct TYPE_16__ {int result_size; int /*<<< orphan*/  mk_size; int /*<<< orphan*/  auth_mode; } ;
struct hash_wr_param {int kctx_len; unsigned int bfr_len; unsigned int sg_len; int /*<<< orphan*/  hash_size; scalar_t__ scmd1; scalar_t__ opad_needed; TYPE_3__ alg_prm; int /*<<< orphan*/  more; int /*<<< orphan*/  last; } ;
struct crypto_ahash {int dummy; } ;
struct TYPE_17__ {int /*<<< orphan*/  scmd1; int /*<<< orphan*/  ivgen_hdrlen; int /*<<< orphan*/  seqno_numivs; int /*<<< orphan*/  cipherstop_lo_authinsert; int /*<<< orphan*/  aadstart_cipherstop_hi; int /*<<< orphan*/  pldlen; int /*<<< orphan*/  op_ivinsrtofst; } ;
struct TYPE_15__ {int key; int /*<<< orphan*/  ctx_hdr; } ;
struct chcr_wr {TYPE_4__ sec_cpl; TYPE_2__ key_ctx; } ;
struct TYPE_20__ {int imm; unsigned int dma_len; struct sk_buff* skb; scalar_t__ dma_addr; int /*<<< orphan*/  src_ofst; int /*<<< orphan*/  srcsg; } ;
struct chcr_ahash_req_ctx {TYPE_7__ hctx_wr; int /*<<< orphan*/  reqbfr; int /*<<< orphan*/  partial_hash; } ;
struct TYPE_13__ {int flags; } ;
struct ahash_request {TYPE_10__ base; } ;
struct TYPE_14__ {int /*<<< orphan*/  digest_rqst; } ;
struct adapter {TYPE_1__ chcr_stats; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_21__ {int /*<<< orphan*/  tx_chan_id; int /*<<< orphan*/  dev; } ;
struct TYPE_18__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int CHCR_HASH_MAX_DIGEST_SIZE ; 
 int /*<<< orphan*/  CHCR_KEYCTX_NO_KEY ; 
 int /*<<< orphan*/  CHCR_SRC_SG_SIZE ; 
 int CRYPTO_TFM_REQ_MAY_SLEEP ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int DUMMY_BYTES ; 
 int ENOMEM ; 
 struct sk_buff* ERR_PTR (int) ; 
 int /*<<< orphan*/  FILL_KEY_CTX_HDR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  FILL_SEC_CPL_AUTHINSERT (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FILL_SEC_CPL_CIPHERSTOP_HI (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FILL_SEC_CPL_IVGEN_HDRLEN (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FILL_SEC_CPL_OP_IVINSR (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FILL_SEC_CPL_SCMD0_SEQNO (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int HASH_TRANSHDR_SIZE (int) ; 
 struct hmac_ctx* HMAC_CTX (TYPE_8__*) ; 
 unsigned int SGE_MAX_WR_LEN ; 
 struct uld_ctx* ULD_CTX (TYPE_8__*) ; 
 struct chcr_wr* __skb_put_zero (struct sk_buff*,unsigned int) ; 
 struct chcr_ahash_req_ctx* ahash_request_ctx (struct ahash_request*) ; 
 struct sk_buff* alloc_skb (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  chcr_add_hash_src_ent (struct ahash_request*,struct ulptx_sgl*,struct hash_wr_param*) ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_wreq (TYPE_8__*,struct chcr_wr*,TYPE_10__*,int,int /*<<< orphan*/ ,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 struct crypto_ahash* crypto_ahash_reqtfm (struct ahash_request*) ; 
 scalar_t__ dma_map_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_8__* h_ctx (struct crypto_ahash*) ; 
 int /*<<< orphan*/  htonl (unsigned int) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (int,int /*<<< orphan*/ ,int) ; 
 struct adapter* padap (int /*<<< orphan*/ ) ; 
 int roundup (unsigned int,int) ; 
 unsigned int sg_nents_xlen (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sgl_len (unsigned int) ; 

__attribute__((used)) static struct sk_buff *create_hash_wr(struct ahash_request *req,
				      struct hash_wr_param *param)
{
	struct chcr_ahash_req_ctx *req_ctx = ahash_request_ctx(req);
	struct crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	struct hmac_ctx *hmacctx = HMAC_CTX(h_ctx(tfm));
	struct sk_buff *skb = NULL;
	struct uld_ctx *u_ctx = ULD_CTX(h_ctx(tfm));
	struct chcr_wr *chcr_req;
	struct ulptx_sgl *ulptx;
	unsigned int nents = 0, transhdr_len;
	unsigned int temp = 0;
	gfp_t flags = req->base.flags & CRYPTO_TFM_REQ_MAY_SLEEP ? GFP_KERNEL :
		GFP_ATOMIC;
	struct adapter *adap = padap(h_ctx(tfm)->dev);
	int error = 0;

	transhdr_len = HASH_TRANSHDR_SIZE(param->kctx_len);
	req_ctx->hctx_wr.imm = (transhdr_len + param->bfr_len +
				param->sg_len) <= SGE_MAX_WR_LEN;
	nents = sg_nents_xlen(req_ctx->hctx_wr.srcsg, param->sg_len,
		      CHCR_SRC_SG_SIZE, req_ctx->hctx_wr.src_ofst);
	nents += param->bfr_len ? 1 : 0;
	transhdr_len += req_ctx->hctx_wr.imm ? roundup(param->bfr_len +
				param->sg_len, 16) : (sgl_len(nents) * 8);
	transhdr_len = roundup(transhdr_len, 16);

	skb = alloc_skb(transhdr_len, flags);
	if (!skb)
		return ERR_PTR(-ENOMEM);
	chcr_req = __skb_put_zero(skb, transhdr_len);

	chcr_req->sec_cpl.op_ivinsrtofst =
		FILL_SEC_CPL_OP_IVINSR(h_ctx(tfm)->tx_chan_id, 2, 0);
	chcr_req->sec_cpl.pldlen = htonl(param->bfr_len + param->sg_len);

	chcr_req->sec_cpl.aadstart_cipherstop_hi =
		FILL_SEC_CPL_CIPHERSTOP_HI(0, 0, 0, 0);
	chcr_req->sec_cpl.cipherstop_lo_authinsert =
		FILL_SEC_CPL_AUTHINSERT(0, 1, 0, 0);
	chcr_req->sec_cpl.seqno_numivs =
		FILL_SEC_CPL_SCMD0_SEQNO(0, 0, 0, param->alg_prm.auth_mode,
					 param->opad_needed, 0);

	chcr_req->sec_cpl.ivgen_hdrlen =
		FILL_SEC_CPL_IVGEN_HDRLEN(param->last, param->more, 0, 1, 0, 0);

	memcpy(chcr_req->key_ctx.key, req_ctx->partial_hash,
	       param->alg_prm.result_size);

	if (param->opad_needed)
		memcpy(chcr_req->key_ctx.key +
		       ((param->alg_prm.result_size <= 32) ? 32 :
			CHCR_HASH_MAX_DIGEST_SIZE),
		       hmacctx->opad, param->alg_prm.result_size);

	chcr_req->key_ctx.ctx_hdr = FILL_KEY_CTX_HDR(CHCR_KEYCTX_NO_KEY,
					    param->alg_prm.mk_size, 0,
					    param->opad_needed,
					    ((param->kctx_len +
					     sizeof(chcr_req->key_ctx)) >> 4));
	chcr_req->sec_cpl.scmd1 = cpu_to_be64((u64)param->scmd1);
	ulptx = (struct ulptx_sgl *)((u8 *)(chcr_req + 1) + param->kctx_len +
				     DUMMY_BYTES);
	if (param->bfr_len != 0) {
		req_ctx->hctx_wr.dma_addr =
			dma_map_single(&u_ctx->lldi.pdev->dev, req_ctx->reqbfr,
				       param->bfr_len, DMA_TO_DEVICE);
		if (dma_mapping_error(&u_ctx->lldi.pdev->dev,
				       req_ctx->hctx_wr. dma_addr)) {
			error = -ENOMEM;
			goto err;
		}
		req_ctx->hctx_wr.dma_len = param->bfr_len;
	} else {
		req_ctx->hctx_wr.dma_addr = 0;
	}
	chcr_add_hash_src_ent(req, ulptx, param);
	/* Request upto max wr size */
	temp = param->kctx_len + DUMMY_BYTES + (req_ctx->hctx_wr.imm ?
				(param->sg_len + param->bfr_len) : 0);
	atomic_inc(&adap->chcr_stats.digest_rqst);
	create_wreq(h_ctx(tfm), chcr_req, &req->base, req_ctx->hctx_wr.imm,
		    param->hash_size, transhdr_len,
		    temp,  0);
	req_ctx->hctx_wr.skb = skb;
	return skb;
err:
	kfree_skb(skb);
	return  ERR_PTR(error);
}