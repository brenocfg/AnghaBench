#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct TYPE_7__ {int /*<<< orphan*/ * ports; } ;
struct uld_ctx {TYPE_2__ lldi; } ;
struct sk_buff {int /*<<< orphan*/  dev; } ;
struct TYPE_9__ {int /*<<< orphan*/  result_size; } ;
struct hash_wr_param {int opad_needed; scalar_t__ sg_len; int kctx_len; scalar_t__ bfr_len; int last; int more; scalar_t__ scmd1; int /*<<< orphan*/  hash_size; TYPE_4__ alg_prm; } ;
struct crypto_ahash {int dummy; } ;
struct chcr_dev {int dummy; } ;
struct TYPE_6__ {int isfinal; int result; int /*<<< orphan*/  srcsg; } ;
struct chcr_ahash_req_ctx {scalar_t__ reqlen; scalar_t__ data_len; int /*<<< orphan*/  reqbfr; TYPE_1__ hctx_wr; } ;
struct ahash_request {int /*<<< orphan*/  src; } ;
struct TYPE_8__ {int /*<<< orphan*/  tx_qidx; struct chcr_dev* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPL_PRIORITY_DATA ; 
 int EINPROGRESS ; 
 int EINVAL ; 
 int ENXIO ; 
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 int PTR_ERR (struct sk_buff*) ; 
 struct uld_ctx* ULD_CTX (TYPE_3__*) ; 
 struct chcr_ahash_req_ctx* ahash_request_ctx (struct ahash_request*) ; 
 int /*<<< orphan*/  chcr_dec_wrcount (struct chcr_dev*) ; 
 int chcr_inc_wrcount (struct chcr_dev*) ; 
 int /*<<< orphan*/  chcr_init_hctx_per_wr (struct chcr_ahash_req_ctx*) ; 
 int /*<<< orphan*/  chcr_send_wr (struct sk_buff*) ; 
 struct sk_buff* create_hash_wr (struct ahash_request*,struct hash_wr_param*) ; 
 int /*<<< orphan*/  create_last_hash_block (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  crypto_ahash_digestsize (struct crypto_ahash*) ; 
 struct crypto_ahash* crypto_ahash_reqtfm (struct ahash_request*) ; 
 int /*<<< orphan*/  crypto_ahash_tfm (struct crypto_ahash*) ; 
 scalar_t__ crypto_tfm_alg_blocksize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_alg_config (TYPE_4__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* h_ctx (struct crypto_ahash*) ; 
 scalar_t__ is_hmac (int /*<<< orphan*/ ) ; 
 int roundup (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_wr_txq (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int chcr_ahash_final(struct ahash_request *req)
{
	struct chcr_ahash_req_ctx *req_ctx = ahash_request_ctx(req);
	struct crypto_ahash *rtfm = crypto_ahash_reqtfm(req);
	struct chcr_dev *dev = h_ctx(rtfm)->dev;
	struct hash_wr_param params;
	struct sk_buff *skb;
	struct uld_ctx *u_ctx = NULL;
	u8 bs = crypto_tfm_alg_blocksize(crypto_ahash_tfm(rtfm));
	int error = -EINVAL;

	error = chcr_inc_wrcount(dev);
	if (error)
		return -ENXIO;

	chcr_init_hctx_per_wr(req_ctx);
	u_ctx = ULD_CTX(h_ctx(rtfm));
	if (is_hmac(crypto_ahash_tfm(rtfm)))
		params.opad_needed = 1;
	else
		params.opad_needed = 0;
	params.sg_len = 0;
	req_ctx->hctx_wr.isfinal = 1;
	get_alg_config(&params.alg_prm, crypto_ahash_digestsize(rtfm));
	params.kctx_len = roundup(params.alg_prm.result_size, 16);
	if (is_hmac(crypto_ahash_tfm(rtfm))) {
		params.opad_needed = 1;
		params.kctx_len *= 2;
	} else {
		params.opad_needed = 0;
	}

	req_ctx->hctx_wr.result = 1;
	params.bfr_len = req_ctx->reqlen;
	req_ctx->data_len += params.bfr_len + params.sg_len;
	req_ctx->hctx_wr.srcsg = req->src;
	if (req_ctx->reqlen == 0) {
		create_last_hash_block(req_ctx->reqbfr, bs, req_ctx->data_len);
		params.last = 0;
		params.more = 1;
		params.scmd1 = 0;
		params.bfr_len = bs;

	} else {
		params.scmd1 = req_ctx->data_len;
		params.last = 1;
		params.more = 0;
	}
	params.hash_size = crypto_ahash_digestsize(rtfm);
	skb = create_hash_wr(req, &params);
	if (IS_ERR(skb)) {
		error = PTR_ERR(skb);
		goto err;
	}
	req_ctx->reqlen = 0;
	skb->dev = u_ctx->lldi.ports[0];
	set_wr_txq(skb, CPL_PRIORITY_DATA, h_ctx(rtfm)->tx_qidx);
	chcr_send_wr(skb);
	return -EINPROGRESS;
err:
	chcr_dec_wrcount(dev);
	return error;
}