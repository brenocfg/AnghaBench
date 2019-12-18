#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct ulptx_sgl {int dummy; } ;
struct sk_buff {int dummy; } ;
struct crypto_aead {int dummy; } ;
struct cpl_rx_phys_dsgl {int dummy; } ;
struct TYPE_7__ {scalar_t__ key; int /*<<< orphan*/  ctx_hdr; } ;
struct chcr_wr {TYPE_1__ key_ctx; int /*<<< orphan*/  sec_cpl; } ;
struct chcr_aead_reqctx {unsigned int b0_len; int imm; struct sk_buff* skb; scalar_t__ op; } ;
struct chcr_aead_ctx {unsigned int enckey_len; int /*<<< orphan*/  key; int /*<<< orphan*/  key_ctx_hdr; } ;
struct TYPE_10__ {int flags; } ;
struct aead_request {unsigned int assoclen; unsigned int cryptlen; TYPE_4__ base; int /*<<< orphan*/  src; int /*<<< orphan*/  dst; } ;
struct TYPE_8__ {int /*<<< orphan*/  aead_rqst; int /*<<< orphan*/  fallback; } ;
struct adapter {TYPE_2__ chcr_stats; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_9__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct chcr_aead_ctx* AEAD_CTX (TYPE_3__*) ; 
 int /*<<< orphan*/  CCM_AAD_FIELD_SIZE ; 
 unsigned int CCM_B0_SIZE ; 
 int /*<<< orphan*/  CHCR_DST_SG_SIZE ; 
 int /*<<< orphan*/  CHCR_SRC_SG_SIZE ; 
 unsigned int CIPHER_TRANSHDR_SIZE (unsigned int,unsigned int) ; 
 unsigned int CRYPTO_ALG_SUB_TYPE_AEAD_RFC4309 ; 
 int CRYPTO_TFM_REQ_MAY_SLEEP ; 
 int EINVAL ; 
 int ENOMEM ; 
 struct sk_buff* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IV ; 
 scalar_t__ MIN_CCM_SG ; 
 unsigned int SGE_MAX_WR_LEN ; 
 scalar_t__ T6_MAX_AAD_SIZE ; 
 struct chcr_wr* __skb_put_zero (struct sk_buff*,unsigned int) ; 
 TYPE_3__* a_ctx (struct crypto_aead*) ; 
 int aead_ccm_validate_input (scalar_t__,struct aead_request*,struct chcr_aead_ctx*,unsigned int) ; 
 struct chcr_aead_reqctx* aead_request_ctx (struct aead_request*) ; 
 struct sk_buff* alloc_skb (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int ccm_format_packet (struct aead_request*,int /*<<< orphan*/ *,unsigned int,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  chcr_add_aead_dst_ent (struct aead_request*,struct cpl_rx_phys_dsgl*,unsigned short) ; 
 int /*<<< orphan*/  chcr_add_aead_src_ent (struct aead_request*,struct ulptx_sgl*) ; 
 int /*<<< orphan*/  chcr_aead_common_exit (struct aead_request*) ; 
 int chcr_aead_common_init (struct aead_request*) ; 
 int chcr_aead_fallback (struct aead_request*,scalar_t__) ; 
 scalar_t__ chcr_aead_need_fallback (struct aead_request*,unsigned int,scalar_t__,unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  create_wreq (TYPE_3__*,struct chcr_wr*,TYPE_4__*,int,int /*<<< orphan*/ ,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int crypto_aead_authsize (struct crypto_aead*) ; 
 struct crypto_aead* crypto_aead_reqtfm (struct aead_request*) ; 
 int /*<<< orphan*/  fill_sec_cpl_for_aead (int /*<<< orphan*/ *,unsigned int,struct aead_request*,scalar_t__) ; 
 unsigned int get_aead_subtype (struct crypto_aead*) ; 
 unsigned int get_space_for_phys_dsgl (unsigned int) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ ,unsigned int) ; 
 struct adapter* padap (int /*<<< orphan*/ ) ; 
 int roundup (unsigned int,int) ; 
 unsigned int sg_nents_xlen (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sgl_len (unsigned int) ; 

__attribute__((used)) static struct sk_buff *create_aead_ccm_wr(struct aead_request *req,
					  unsigned short qid,
					  int size)
{
	struct crypto_aead *tfm = crypto_aead_reqtfm(req);
	struct chcr_aead_ctx *aeadctx = AEAD_CTX(a_ctx(tfm));
	struct chcr_aead_reqctx *reqctx = aead_request_ctx(req);
	struct sk_buff *skb = NULL;
	struct chcr_wr *chcr_req;
	struct cpl_rx_phys_dsgl *phys_cpl;
	struct ulptx_sgl *ulptx;
	unsigned int transhdr_len;
	unsigned int dst_size = 0, kctx_len, dnents, temp, snents;
	unsigned int sub_type, assoclen = req->assoclen;
	unsigned int authsize = crypto_aead_authsize(tfm);
	int error = -EINVAL;
	u8 *ivptr;
	gfp_t flags = req->base.flags & CRYPTO_TFM_REQ_MAY_SLEEP ? GFP_KERNEL :
		GFP_ATOMIC;
	struct adapter *adap = padap(a_ctx(tfm)->dev);

	sub_type = get_aead_subtype(tfm);
	if (sub_type == CRYPTO_ALG_SUB_TYPE_AEAD_RFC4309)
		assoclen -= 8;
	reqctx->b0_len = CCM_B0_SIZE + (assoclen ? CCM_AAD_FIELD_SIZE : 0);
	error = chcr_aead_common_init(req);
	if (error)
		return ERR_PTR(error);

	error = aead_ccm_validate_input(reqctx->op, req, aeadctx, sub_type);
	if (error)
		goto err;
	dnents = sg_nents_xlen(req->dst, req->assoclen + req->cryptlen
			+ (reqctx->op ? -authsize : authsize),
			CHCR_DST_SG_SIZE, 0);
	dnents += MIN_CCM_SG; // For IV and B0
	dst_size = get_space_for_phys_dsgl(dnents);
	snents = sg_nents_xlen(req->src, req->assoclen + req->cryptlen,
			       CHCR_SRC_SG_SIZE, 0);
	snents += MIN_CCM_SG; //For B0
	kctx_len = roundup(aeadctx->enckey_len, 16) * 2;
	transhdr_len = CIPHER_TRANSHDR_SIZE(kctx_len, dst_size);
	reqctx->imm = (transhdr_len + req->assoclen + req->cryptlen +
		       reqctx->b0_len) <= SGE_MAX_WR_LEN;
	temp = reqctx->imm ? roundup(req->assoclen + req->cryptlen +
				     reqctx->b0_len, 16) :
		(sgl_len(snents) *  8);
	transhdr_len += temp;
	transhdr_len = roundup(transhdr_len, 16);

	if (chcr_aead_need_fallback(req, dnents, T6_MAX_AAD_SIZE -
				reqctx->b0_len, transhdr_len, reqctx->op)) {
		atomic_inc(&adap->chcr_stats.fallback);
		chcr_aead_common_exit(req);
		return ERR_PTR(chcr_aead_fallback(req, reqctx->op));
	}
	skb = alloc_skb(transhdr_len,  flags);

	if (!skb) {
		error = -ENOMEM;
		goto err;
	}

	chcr_req = __skb_put_zero(skb, transhdr_len);

	fill_sec_cpl_for_aead(&chcr_req->sec_cpl, dst_size, req, reqctx->op);

	chcr_req->key_ctx.ctx_hdr = aeadctx->key_ctx_hdr;
	memcpy(chcr_req->key_ctx.key, aeadctx->key, aeadctx->enckey_len);
	memcpy(chcr_req->key_ctx.key + roundup(aeadctx->enckey_len, 16),
			aeadctx->key, aeadctx->enckey_len);

	phys_cpl = (struct cpl_rx_phys_dsgl *)((u8 *)(chcr_req + 1) + kctx_len);
	ivptr = (u8 *)(phys_cpl + 1) + dst_size;
	ulptx = (struct ulptx_sgl *)(ivptr + IV);
	error = ccm_format_packet(req, ivptr, sub_type, reqctx->op, assoclen);
	if (error)
		goto dstmap_fail;
	chcr_add_aead_dst_ent(req, phys_cpl, qid);
	chcr_add_aead_src_ent(req, ulptx);

	atomic_inc(&adap->chcr_stats.aead_rqst);
	temp = sizeof(struct cpl_rx_phys_dsgl) + dst_size + IV +
		kctx_len + (reqctx->imm ? (req->assoclen + req->cryptlen +
		reqctx->b0_len) : 0);
	create_wreq(a_ctx(tfm), chcr_req, &req->base, reqctx->imm, 0,
		    transhdr_len, temp, 0);
	reqctx->skb = skb;

	return skb;
dstmap_fail:
	kfree_skb(skb);
err:
	chcr_aead_common_exit(req);
	return ERR_PTR(error);
}