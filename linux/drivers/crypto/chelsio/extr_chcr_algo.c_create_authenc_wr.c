#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct ulptx_sgl {int dummy; } ;
struct sk_buff {int dummy; } ;
struct crypto_aead {int dummy; } ;
struct cpl_rx_phys_dsgl {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/ * key; int /*<<< orphan*/  ctx_hdr; } ;
struct TYPE_10__ {int /*<<< orphan*/  ivgen_hdrlen; int /*<<< orphan*/  seqno_numivs; int /*<<< orphan*/  cipherstop_lo_authinsert; int /*<<< orphan*/  aadstart_cipherstop_hi; int /*<<< orphan*/  pldlen; int /*<<< orphan*/  op_ivinsrtofst; } ;
struct chcr_wr {TYPE_1__ key_ctx; TYPE_3__ sec_cpl; } ;
struct chcr_authenc_ctx {int /*<<< orphan*/  h_iopad; int /*<<< orphan*/  dec_rrkey; int /*<<< orphan*/  auth_mode; } ;
struct chcr_aead_reqctx {scalar_t__ op; int imm; struct sk_buff* skb; scalar_t__ b0_len; } ;
struct chcr_aead_ctx {int enckey_len; int /*<<< orphan*/  nonce; int /*<<< orphan*/  key; int /*<<< orphan*/  key_ctx_hdr; int /*<<< orphan*/  hmac_ctrl; } ;
struct TYPE_12__ {int flags; } ;
struct aead_request {scalar_t__ cryptlen; scalar_t__ assoclen; TYPE_5__ base; int /*<<< orphan*/  iv; int /*<<< orphan*/  src; int /*<<< orphan*/  dst; } ;
struct TYPE_9__ {int /*<<< orphan*/  cipher_rqst; int /*<<< orphan*/  fallback; } ;
struct adapter {TYPE_2__ chcr_stats; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_11__ {int /*<<< orphan*/  tx_chan_id; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct chcr_aead_ctx* AEAD_CTX (TYPE_4__*) ; 
 struct chcr_authenc_ctx* AUTHENC_CTX (struct chcr_aead_ctx*) ; 
 int /*<<< orphan*/  CHCR_DST_SG_SIZE ; 
 scalar_t__ CHCR_ENCRYPT_OP ; 
 unsigned int CHCR_SCMD_CIPHER_MODE_AES_CBC ; 
 unsigned int CHCR_SCMD_CIPHER_MODE_AES_CTR ; 
 int /*<<< orphan*/  CHCR_SRC_SG_SIZE ; 
 unsigned int CIPHER_TRANSHDR_SIZE (unsigned int,unsigned int) ; 
 unsigned int CRYPTO_ALG_SUB_TYPE_CBC_NULL ; 
 unsigned int CRYPTO_ALG_SUB_TYPE_CTR_NULL ; 
 unsigned int CRYPTO_ALG_SUB_TYPE_CTR_SHA ; 
 int CRYPTO_TFM_REQ_MAY_SLEEP ; 
 int CTR_RFC3686_IV_SIZE ; 
 int CTR_RFC3686_NONCE_SIZE ; 
 int EINVAL ; 
 int ENOMEM ; 
 struct sk_buff* ERR_PTR (int) ; 
 int /*<<< orphan*/  FILL_SEC_CPL_AUTHINSERT (unsigned int,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  FILL_SEC_CPL_CIPHERSTOP_HI (int,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  FILL_SEC_CPL_IVGEN_HDRLEN (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  FILL_SEC_CPL_OP_IVINSR (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  FILL_SEC_CPL_SCMD0_SEQNO (scalar_t__,int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IV ; 
 int /*<<< orphan*/  KEY_CONTEXT_CTX_LEN_V (int /*<<< orphan*/ ) ; 
 scalar_t__ MIN_AUTH_SG ; 
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
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int /*<<< orphan*/  create_wreq (TYPE_4__*,struct chcr_wr*,TYPE_5__*,int,int,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int crypto_aead_authsize (struct crypto_aead*) ; 
 struct crypto_aead* crypto_aead_reqtfm (struct aead_request*) ; 
 unsigned int get_aead_subtype (struct crypto_aead*) ; 
 unsigned int get_space_for_phys_dsgl (unsigned int) ; 
 int /*<<< orphan*/  htonl (unsigned int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int ntohl (int /*<<< orphan*/ ) ; 
 struct adapter* padap (int /*<<< orphan*/ ) ; 
 unsigned int roundup (unsigned int,int) ; 
 unsigned int sg_nents_xlen (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sgl_len (unsigned int) ; 

__attribute__((used)) static struct sk_buff *create_authenc_wr(struct aead_request *req,
					 unsigned short qid,
					 int size)
{
	struct crypto_aead *tfm = crypto_aead_reqtfm(req);
	struct chcr_aead_ctx *aeadctx = AEAD_CTX(a_ctx(tfm));
	struct chcr_authenc_ctx *actx = AUTHENC_CTX(aeadctx);
	struct chcr_aead_reqctx *reqctx = aead_request_ctx(req);
	struct sk_buff *skb = NULL;
	struct chcr_wr *chcr_req;
	struct cpl_rx_phys_dsgl *phys_cpl;
	struct ulptx_sgl *ulptx;
	unsigned int transhdr_len;
	unsigned int dst_size = 0, temp, subtype = get_aead_subtype(tfm);
	unsigned int   kctx_len = 0, dnents, snents;
	unsigned int  authsize = crypto_aead_authsize(tfm);
	int error = -EINVAL;
	u8 *ivptr;
	int null = 0;
	gfp_t flags = req->base.flags & CRYPTO_TFM_REQ_MAY_SLEEP ? GFP_KERNEL :
		GFP_ATOMIC;
	struct adapter *adap = padap(a_ctx(tfm)->dev);

	if (req->cryptlen == 0)
		return NULL;

	reqctx->b0_len = 0;
	error = chcr_aead_common_init(req);
	if (error)
		return ERR_PTR(error);

	if (subtype == CRYPTO_ALG_SUB_TYPE_CBC_NULL ||
		subtype == CRYPTO_ALG_SUB_TYPE_CTR_NULL) {
		null = 1;
	}
	dnents = sg_nents_xlen(req->dst, req->assoclen + req->cryptlen +
		(reqctx->op ? -authsize : authsize), CHCR_DST_SG_SIZE, 0);
	dnents += MIN_AUTH_SG; // For IV
	snents = sg_nents_xlen(req->src, req->assoclen + req->cryptlen,
			       CHCR_SRC_SG_SIZE, 0);
	dst_size = get_space_for_phys_dsgl(dnents);
	kctx_len = (ntohl(KEY_CONTEXT_CTX_LEN_V(aeadctx->key_ctx_hdr)) << 4)
		- sizeof(chcr_req->key_ctx);
	transhdr_len = CIPHER_TRANSHDR_SIZE(kctx_len, dst_size);
	reqctx->imm = (transhdr_len + req->assoclen + req->cryptlen) <
			SGE_MAX_WR_LEN;
	temp = reqctx->imm ? roundup(req->assoclen + req->cryptlen, 16)
			: (sgl_len(snents) * 8);
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

	temp  = (reqctx->op == CHCR_ENCRYPT_OP) ? 0 : authsize;

	/*
	 * Input order	is AAD,IV and Payload. where IV should be included as
	 * the part of authdata. All other fields should be filled according
	 * to the hardware spec
	 */
	chcr_req->sec_cpl.op_ivinsrtofst =
		FILL_SEC_CPL_OP_IVINSR(a_ctx(tfm)->tx_chan_id, 2, 1);
	chcr_req->sec_cpl.pldlen = htonl(req->assoclen + IV + req->cryptlen);
	chcr_req->sec_cpl.aadstart_cipherstop_hi = FILL_SEC_CPL_CIPHERSTOP_HI(
					null ? 0 : 1 + IV,
					null ? 0 : IV + req->assoclen,
					req->assoclen + IV + 1,
					(temp & 0x1F0) >> 4);
	chcr_req->sec_cpl.cipherstop_lo_authinsert = FILL_SEC_CPL_AUTHINSERT(
					temp & 0xF,
					null ? 0 : req->assoclen + IV + 1,
					temp, temp);
	if (subtype == CRYPTO_ALG_SUB_TYPE_CTR_NULL ||
	    subtype == CRYPTO_ALG_SUB_TYPE_CTR_SHA)
		temp = CHCR_SCMD_CIPHER_MODE_AES_CTR;
	else
		temp = CHCR_SCMD_CIPHER_MODE_AES_CBC;
	chcr_req->sec_cpl.seqno_numivs = FILL_SEC_CPL_SCMD0_SEQNO(reqctx->op,
					(reqctx->op == CHCR_ENCRYPT_OP) ? 1 : 0,
					temp,
					actx->auth_mode, aeadctx->hmac_ctrl,
					IV >> 1);
	chcr_req->sec_cpl.ivgen_hdrlen =  FILL_SEC_CPL_IVGEN_HDRLEN(0, 0, 1,
					 0, 0, dst_size);

	chcr_req->key_ctx.ctx_hdr = aeadctx->key_ctx_hdr;
	if (reqctx->op == CHCR_ENCRYPT_OP ||
		subtype == CRYPTO_ALG_SUB_TYPE_CTR_SHA ||
		subtype == CRYPTO_ALG_SUB_TYPE_CTR_NULL)
		memcpy(chcr_req->key_ctx.key, aeadctx->key,
		       aeadctx->enckey_len);
	else
		memcpy(chcr_req->key_ctx.key, actx->dec_rrkey,
		       aeadctx->enckey_len);

	memcpy(chcr_req->key_ctx.key + roundup(aeadctx->enckey_len, 16),
	       actx->h_iopad, kctx_len - roundup(aeadctx->enckey_len, 16));
	phys_cpl = (struct cpl_rx_phys_dsgl *)((u8 *)(chcr_req + 1) + kctx_len);
	ivptr = (u8 *)(phys_cpl + 1) + dst_size;
	ulptx = (struct ulptx_sgl *)(ivptr + IV);
	if (subtype == CRYPTO_ALG_SUB_TYPE_CTR_SHA ||
	    subtype == CRYPTO_ALG_SUB_TYPE_CTR_NULL) {
		memcpy(ivptr, aeadctx->nonce, CTR_RFC3686_NONCE_SIZE);
		memcpy(ivptr + CTR_RFC3686_NONCE_SIZE, req->iv,
				CTR_RFC3686_IV_SIZE);
		*(__be32 *)(ivptr + CTR_RFC3686_NONCE_SIZE +
			CTR_RFC3686_IV_SIZE) = cpu_to_be32(1);
	} else {
		memcpy(ivptr, req->iv, IV);
	}
	chcr_add_aead_dst_ent(req, phys_cpl, qid);
	chcr_add_aead_src_ent(req, ulptx);
	atomic_inc(&adap->chcr_stats.cipher_rqst);
	temp = sizeof(struct cpl_rx_phys_dsgl) + dst_size + IV +
		kctx_len + (reqctx->imm ? (req->assoclen + req->cryptlen) : 0);
	create_wreq(a_ctx(tfm), chcr_req, &req->base, reqctx->imm, size,
		   transhdr_len, temp, 0);
	reqctx->skb = skb;

	return skb;
err:
	chcr_aead_common_exit(req);

	return ERR_PTR(error);
}