#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct ulptx_sgl {int dummy; } ;
struct sk_buff {int dummy; } ;
struct crypto_aead {int dummy; } ;
struct cpl_rx_phys_dsgl {int dummy; } ;
struct TYPE_11__ {int /*<<< orphan*/ * key; int /*<<< orphan*/  ctx_hdr; } ;
struct TYPE_10__ {int /*<<< orphan*/  ivgen_hdrlen; int /*<<< orphan*/  seqno_numivs; int /*<<< orphan*/  cipherstop_lo_authinsert; int /*<<< orphan*/  aadstart_cipherstop_hi; void* pldlen; int /*<<< orphan*/  op_ivinsrtofst; } ;
struct chcr_wr {TYPE_3__ key_ctx; TYPE_2__ sec_cpl; } ;
struct chcr_aead_reqctx {scalar_t__ op; int imm; struct sk_buff* skb; int /*<<< orphan*/  verify; scalar_t__ b0_len; } ;
struct chcr_aead_ctx {unsigned int enckey_len; int /*<<< orphan*/  salt; int /*<<< orphan*/  key; int /*<<< orphan*/  key_ctx_hdr; int /*<<< orphan*/  hmac_ctrl; } ;
struct TYPE_13__ {int flags; } ;
struct aead_request {unsigned int assoclen; scalar_t__ cryptlen; TYPE_5__ base; int /*<<< orphan*/  iv; int /*<<< orphan*/  src; int /*<<< orphan*/  dst; } ;
struct TYPE_9__ {int /*<<< orphan*/  aead_rqst; int /*<<< orphan*/  fallback; } ;
struct adapter {TYPE_1__ chcr_stats; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_14__ {int /*<<< orphan*/  ghash_h; } ;
struct TYPE_12__ {int /*<<< orphan*/  tx_chan_id; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct chcr_aead_ctx* AEAD_CTX (TYPE_4__*) ; 
 int AEAD_H_SIZE ; 
 int /*<<< orphan*/  CHCR_DST_SG_SIZE ; 
 scalar_t__ CHCR_ENCRYPT_OP ; 
 int /*<<< orphan*/  CHCR_SCMD_AUTH_MODE_GHASH ; 
 int /*<<< orphan*/  CHCR_SCMD_CIPHER_MODE_AES_GCM ; 
 int /*<<< orphan*/  CHCR_SRC_SG_SIZE ; 
 unsigned int CIPHER_TRANSHDR_SIZE (unsigned int,unsigned int) ; 
 scalar_t__ CRYPTO_ALG_SUB_TYPE_AEAD_RFC4106 ; 
 int CRYPTO_TFM_REQ_MAY_SLEEP ; 
 int EINVAL ; 
 int ENOMEM ; 
 struct sk_buff* ERR_PTR (int) ; 
 int /*<<< orphan*/  FILL_SEC_CPL_AUTHINSERT (int /*<<< orphan*/ ,int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  FILL_SEC_CPL_CIPHERSTOP_HI (int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FILL_SEC_CPL_IVGEN_HDRLEN (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  FILL_SEC_CPL_OP_IVINSR (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  FILL_SEC_CPL_SCMD0_SEQNO (scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int GCM_AES_IV_SIZE ; 
 TYPE_7__* GCM_CTX (struct chcr_aead_ctx*) ; 
 int GCM_RFC4106_IV_SIZE ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IV ; 
 scalar_t__ MIN_GCM_SG ; 
 scalar_t__ SGE_MAX_WR_LEN ; 
 int /*<<< orphan*/  T6_MAX_AAD_SIZE ; 
 struct chcr_wr* __skb_put_zero (struct sk_buff*,unsigned int) ; 
 TYPE_4__* a_ctx (struct crypto_aead*) ; 
 struct chcr_aead_reqctx* aead_request_ctx (struct aead_request*) ; 
 struct sk_buff* alloc_skb (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  chcr_add_aead_dst_ent (struct aead_request*,struct cpl_rx_phys_dsgl*,unsigned short) ; 
 int /*<<< orphan*/  chcr_add_aead_src_ent (struct aead_request*,struct ulptx_sgl*) ; 
 int /*<<< orphan*/  chcr_aead_common_exit (struct aead_request*) ; 
 int chcr_aead_common_init (struct aead_request*) ; 
 int chcr_aead_fallback (struct aead_request*,scalar_t__) ; 
 scalar_t__ chcr_aead_need_fallback (struct aead_request*,unsigned int,int /*<<< orphan*/ ,unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  create_wreq (TYPE_4__*,struct chcr_wr*,TYPE_5__*,int,int,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int crypto_aead_authsize (struct crypto_aead*) ; 
 struct crypto_aead* crypto_aead_reqtfm (struct aead_request*) ; 
 scalar_t__ get_aead_subtype (struct crypto_aead*) ; 
 unsigned int get_space_for_phys_dsgl (unsigned int) ; 
 void* htonl (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct adapter* padap (int /*<<< orphan*/ ) ; 
 int roundup (unsigned int,int) ; 
 unsigned int sg_nents_xlen (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sgl_len (unsigned int) ; 

__attribute__((used)) static struct sk_buff *create_gcm_wr(struct aead_request *req,
				     unsigned short qid,
				     int size)
{
	struct crypto_aead *tfm = crypto_aead_reqtfm(req);
	struct chcr_aead_ctx *aeadctx = AEAD_CTX(a_ctx(tfm));
	struct chcr_aead_reqctx  *reqctx = aead_request_ctx(req);
	struct sk_buff *skb = NULL;
	struct chcr_wr *chcr_req;
	struct cpl_rx_phys_dsgl *phys_cpl;
	struct ulptx_sgl *ulptx;
	unsigned int transhdr_len, dnents = 0, snents;
	unsigned int dst_size = 0, temp = 0, kctx_len, assoclen = req->assoclen;
	unsigned int authsize = crypto_aead_authsize(tfm);
	int error = -EINVAL;
	u8 *ivptr;
	gfp_t flags = req->base.flags & CRYPTO_TFM_REQ_MAY_SLEEP ? GFP_KERNEL :
		GFP_ATOMIC;
	struct adapter *adap = padap(a_ctx(tfm)->dev);

	if (get_aead_subtype(tfm) == CRYPTO_ALG_SUB_TYPE_AEAD_RFC4106)
		assoclen = req->assoclen - 8;

	reqctx->b0_len = 0;
	error = chcr_aead_common_init(req);
	if (error)
		return ERR_PTR(error);
	dnents = sg_nents_xlen(req->dst, req->assoclen + req->cryptlen +
				(reqctx->op ? -authsize : authsize),
				CHCR_DST_SG_SIZE, 0);
	snents = sg_nents_xlen(req->src, req->assoclen + req->cryptlen,
			       CHCR_SRC_SG_SIZE, 0);
	dnents += MIN_GCM_SG; // For IV
	dst_size = get_space_for_phys_dsgl(dnents);
	kctx_len = roundup(aeadctx->enckey_len, 16) + AEAD_H_SIZE;
	transhdr_len = CIPHER_TRANSHDR_SIZE(kctx_len, dst_size);
	reqctx->imm = (transhdr_len + req->assoclen + req->cryptlen) <=
			SGE_MAX_WR_LEN;
	temp = reqctx->imm ? roundup(req->assoclen + req->cryptlen, 16) :
		(sgl_len(snents) * 8);
	transhdr_len += temp;
	transhdr_len = roundup(transhdr_len, 16);
	if (chcr_aead_need_fallback(req, dnents, T6_MAX_AAD_SIZE,
			    transhdr_len, reqctx->op)) {

		atomic_inc(&adap->chcr_stats.fallback);
		chcr_aead_common_exit(req);
		return ERR_PTR(chcr_aead_fallback(req, reqctx->op));
	}
	skb = alloc_skb(transhdr_len, flags);
	if (!skb) {
		error = -ENOMEM;
		goto err;
	}

	chcr_req = __skb_put_zero(skb, transhdr_len);

	//Offset of tag from end
	temp = (reqctx->op == CHCR_ENCRYPT_OP) ? 0 : authsize;
	chcr_req->sec_cpl.op_ivinsrtofst = FILL_SEC_CPL_OP_IVINSR(
					a_ctx(tfm)->tx_chan_id, 2, 1);
	chcr_req->sec_cpl.pldlen =
		htonl(req->assoclen + IV + req->cryptlen);
	chcr_req->sec_cpl.aadstart_cipherstop_hi = FILL_SEC_CPL_CIPHERSTOP_HI(
					assoclen ? 1 + IV : 0,
					assoclen ? IV + assoclen : 0,
					req->assoclen + IV + 1, 0);
	chcr_req->sec_cpl.cipherstop_lo_authinsert =
			FILL_SEC_CPL_AUTHINSERT(0, req->assoclen + IV + 1,
						temp, temp);
	chcr_req->sec_cpl.seqno_numivs =
			FILL_SEC_CPL_SCMD0_SEQNO(reqctx->op, (reqctx->op ==
					CHCR_ENCRYPT_OP) ? 1 : 0,
					CHCR_SCMD_CIPHER_MODE_AES_GCM,
					CHCR_SCMD_AUTH_MODE_GHASH,
					aeadctx->hmac_ctrl, IV >> 1);
	chcr_req->sec_cpl.ivgen_hdrlen =  FILL_SEC_CPL_IVGEN_HDRLEN(0, 0, 1,
					0, 0, dst_size);
	chcr_req->key_ctx.ctx_hdr = aeadctx->key_ctx_hdr;
	memcpy(chcr_req->key_ctx.key, aeadctx->key, aeadctx->enckey_len);
	memcpy(chcr_req->key_ctx.key + roundup(aeadctx->enckey_len, 16),
	       GCM_CTX(aeadctx)->ghash_h, AEAD_H_SIZE);

	phys_cpl = (struct cpl_rx_phys_dsgl *)((u8 *)(chcr_req + 1) + kctx_len);
	ivptr = (u8 *)(phys_cpl + 1) + dst_size;
	/* prepare a 16 byte iv */
	/* S   A   L  T |  IV | 0x00000001 */
	if (get_aead_subtype(tfm) ==
	    CRYPTO_ALG_SUB_TYPE_AEAD_RFC4106) {
		memcpy(ivptr, aeadctx->salt, 4);
		memcpy(ivptr + 4, req->iv, GCM_RFC4106_IV_SIZE);
	} else {
		memcpy(ivptr, req->iv, GCM_AES_IV_SIZE);
	}
	*((unsigned int *)(ivptr + 12)) = htonl(0x01);

	ulptx = (struct ulptx_sgl *)(ivptr + 16);

	chcr_add_aead_dst_ent(req, phys_cpl, qid);
	chcr_add_aead_src_ent(req, ulptx);
	atomic_inc(&adap->chcr_stats.aead_rqst);
	temp = sizeof(struct cpl_rx_phys_dsgl) + dst_size + IV +
		kctx_len + (reqctx->imm ? (req->assoclen + req->cryptlen) : 0);
	create_wreq(a_ctx(tfm), chcr_req, &req->base, reqctx->imm, size,
		    transhdr_len, temp, reqctx->verify);
	reqctx->skb = skb;
	return skb;

err:
	chcr_aead_common_exit(req);
	return ERR_PTR(error);
}