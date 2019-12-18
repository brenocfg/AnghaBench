#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct TYPE_11__ {TYPE_3__* pdev; int /*<<< orphan*/ * ports; } ;
struct uld_ctx {TYPE_4__ lldi; } ;
struct sk_buff {int /*<<< orphan*/  dev; } ;
struct TYPE_13__ {int /*<<< orphan*/  result_size; } ;
struct hash_wr_param {int kctx_len; int opad_needed; scalar_t__ sg_len; int last; int more; scalar_t__ scmd1; scalar_t__ bfr_len; int /*<<< orphan*/  hash_size; TYPE_6__ alg_prm; } ;
struct crypto_ahash {int /*<<< orphan*/  (* init ) (struct ahash_request*) ;} ;
struct chcr_dev {int dummy; } ;
struct TYPE_9__ {int result; int /*<<< orphan*/  processed; int /*<<< orphan*/  srcsg; } ;
struct chcr_ahash_req_ctx {scalar_t__ data_len; TYPE_2__ hctx_wr; int /*<<< orphan*/  reqbfr; int /*<<< orphan*/  reqlen; } ;
struct TYPE_8__ {int flags; } ;
struct ahash_request {scalar_t__ nbytes; int /*<<< orphan*/  src; TYPE_1__ base; } ;
struct TYPE_12__ {int /*<<< orphan*/  tx_qidx; struct chcr_dev* dev; } ;
struct TYPE_10__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPL_PRIORITY_DATA ; 
 int CRYPTO_TFM_REQ_MAY_BACKLOG ; 
 int EBUSY ; 
 int EINPROGRESS ; 
 int ENOMEM ; 
 int ENOSPC ; 
 int ENXIO ; 
 int /*<<< orphan*/  HASH_SPACE_LEFT (int) ; 
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 int PTR_ERR (struct sk_buff*) ; 
 struct uld_ctx* ULD_CTX (TYPE_5__*) ; 
 struct chcr_ahash_req_ctx* ahash_request_ctx (struct ahash_request*) ; 
 int /*<<< orphan*/  chcr_dec_wrcount (struct chcr_dev*) ; 
 int chcr_hash_dma_map (int /*<<< orphan*/ *,struct ahash_request*) ; 
 int /*<<< orphan*/  chcr_hash_dma_unmap (int /*<<< orphan*/ *,struct ahash_request*) ; 
 scalar_t__ chcr_hash_ent_in_wr (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int chcr_inc_wrcount (struct chcr_dev*) ; 
 int /*<<< orphan*/  chcr_init_hctx_per_wr (struct chcr_ahash_req_ctx*) ; 
 int /*<<< orphan*/  chcr_send_wr (struct sk_buff*) ; 
 struct sk_buff* create_hash_wr (struct ahash_request*,struct hash_wr_param*) ; 
 int /*<<< orphan*/  create_last_hash_block (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_ahash_digestsize (struct crypto_ahash*) ; 
 struct crypto_ahash* crypto_ahash_reqtfm (struct ahash_request*) ; 
 int /*<<< orphan*/  crypto_ahash_tfm (struct crypto_ahash*) ; 
 scalar_t__ crypto_tfm_alg_blocksize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxgb4_is_crypto_q_full (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_alg_config (TYPE_6__*,int /*<<< orphan*/ ) ; 
 TYPE_5__* h_ctx (struct crypto_ahash*) ; 
 scalar_t__ is_hmac (int /*<<< orphan*/ ) ; 
 scalar_t__ rounddown (scalar_t__,scalar_t__) ; 
 int roundup (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_wr_txq (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct ahash_request*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int chcr_ahash_digest(struct ahash_request *req)
{
	struct chcr_ahash_req_ctx *req_ctx = ahash_request_ctx(req);
	struct crypto_ahash *rtfm = crypto_ahash_reqtfm(req);
	struct chcr_dev *dev = h_ctx(rtfm)->dev;
	struct uld_ctx *u_ctx = NULL;
	struct sk_buff *skb;
	struct hash_wr_param params;
	u8  bs;
	int error, isfull = 0;

	rtfm->init(req);
	bs = crypto_tfm_alg_blocksize(crypto_ahash_tfm(rtfm));
	error = chcr_inc_wrcount(dev);
	if (error)
		return -ENXIO;

	u_ctx = ULD_CTX(h_ctx(rtfm));
	if (unlikely(cxgb4_is_crypto_q_full(u_ctx->lldi.ports[0],
					    h_ctx(rtfm)->tx_qidx))) {
		isfull = 1;
		if (!(req->base.flags & CRYPTO_TFM_REQ_MAY_BACKLOG)) {
			error = -ENOSPC;
			goto err;
		}
	}

	chcr_init_hctx_per_wr(req_ctx);
	error = chcr_hash_dma_map(&u_ctx->lldi.pdev->dev, req);
	if (error) {
		error = -ENOMEM;
		goto err;
	}

	get_alg_config(&params.alg_prm, crypto_ahash_digestsize(rtfm));
	params.kctx_len = roundup(params.alg_prm.result_size, 16);
	if (is_hmac(crypto_ahash_tfm(rtfm))) {
		params.kctx_len *= 2;
		params.opad_needed = 1;
	} else {
		params.opad_needed = 0;
	}
	params.sg_len = chcr_hash_ent_in_wr(req->src, !!req_ctx->reqlen,
				HASH_SPACE_LEFT(params.kctx_len), 0);
	if (params.sg_len < req->nbytes) {
		if (is_hmac(crypto_ahash_tfm(rtfm))) {
			params.kctx_len /= 2;
			params.opad_needed = 0;
		}
		params.last = 0;
		params.more = 1;
		params.scmd1 = 0;
		params.sg_len = rounddown(params.sg_len, bs);
		params.hash_size = params.alg_prm.result_size;
	} else {
		params.sg_len = req->nbytes;
		params.hash_size = crypto_ahash_digestsize(rtfm);
		params.last = 1;
		params.more = 0;
		params.scmd1 = req->nbytes + req_ctx->data_len;

	}
	params.bfr_len = 0;
	req_ctx->hctx_wr.result = 1;
	req_ctx->hctx_wr.srcsg = req->src;
	req_ctx->data_len += params.bfr_len + params.sg_len;

	if (req->nbytes == 0) {
		create_last_hash_block(req_ctx->reqbfr, bs, 0);
		params.more = 1;
		params.bfr_len = bs;
	}

	skb = create_hash_wr(req, &params);
	if (IS_ERR(skb)) {
		error = PTR_ERR(skb);
		goto unmap;
	}
	req_ctx->hctx_wr.processed += params.sg_len;
	skb->dev = u_ctx->lldi.ports[0];
	set_wr_txq(skb, CPL_PRIORITY_DATA, h_ctx(rtfm)->tx_qidx);
	chcr_send_wr(skb);
	return isfull ? -EBUSY : -EINPROGRESS;
unmap:
	chcr_hash_dma_unmap(&u_ctx->lldi.pdev->dev, req);
err:
	chcr_dec_wrcount(dev);
	return error;
}