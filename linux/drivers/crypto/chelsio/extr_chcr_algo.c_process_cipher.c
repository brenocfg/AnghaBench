#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct crypto_ablkcipher {int dummy; } ;
struct cpl_rx_phys_dsgl {int dummy; } ;
struct cipher_wr_param {unsigned short qid; int bytes; struct ablkcipher_request* req; } ;
struct chcr_wr {int dummy; } ;
struct chcr_blkcipher_req_ctx {int processed; int imm; unsigned int iv; unsigned short op; int last_req_len; scalar_t__ dst_ofst; scalar_t__ src_ofst; int /*<<< orphan*/  dstsg; int /*<<< orphan*/  srcsg; } ;
struct TYPE_5__ {int /*<<< orphan*/  flags; } ;
struct ablkcipher_request {int nbytes; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; TYPE_1__ base; int /*<<< orphan*/  info; } ;
struct ablk_ctx {scalar_t__ enckey_len; int /*<<< orphan*/  sw_cipher; int /*<<< orphan*/  nonce; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_7__ {TYPE_2__* pdev; } ;
struct TYPE_8__ {TYPE_3__ lldi; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct ablk_ctx* ABLK_CTX (int /*<<< orphan*/ ) ; 
 unsigned int AES_BLOCK_SIZE ; 
 unsigned int AES_MIN_KEY_SIZE ; 
 int /*<<< orphan*/  CHCR_DST_SG_SIZE ; 
 unsigned int CIPHER_TRANSHDR_SIZE (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  CIP_SPACE_LEFT (scalar_t__) ; 
 scalar_t__ CRYPTO_ALG_SUB_TYPE_CTR ; 
 scalar_t__ CRYPTO_ALG_SUB_TYPE_CTR_RFC3686 ; 
 unsigned int CTR_RFC3686_IV_SIZE ; 
 unsigned int CTR_RFC3686_NONCE_SIZE ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 unsigned int IV ; 
 int PTR_ERR (struct sk_buff*) ; 
 unsigned int SGE_MAX_WR_LEN ; 
 TYPE_4__* ULD_CTX (int /*<<< orphan*/ ) ; 
 struct chcr_blkcipher_req_ctx* ablkcipher_request_ctx (struct ablkcipher_request*) ; 
 int adjust_ctr_overflow (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  c_ctx (struct crypto_ablkcipher*) ; 
 int chcr_cipher_dma_map (int /*<<< orphan*/ *,struct ablkcipher_request*) ; 
 int /*<<< orphan*/  chcr_cipher_dma_unmap (int /*<<< orphan*/ *,struct ablkcipher_request*) ; 
 int chcr_cipher_fallback (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned int,unsigned short) ; 
 int chcr_sg_ent_in_wr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 struct sk_buff* create_cipher_wr (struct cipher_wr_param*) ; 
 int crypto_ablkcipher_blocksize (struct crypto_ablkcipher*) ; 
 unsigned int crypto_ablkcipher_ivsize (struct crypto_ablkcipher*) ; 
 struct crypto_ablkcipher* crypto_ablkcipher_reqtfm (struct ablkcipher_request*) ; 
 int /*<<< orphan*/  crypto_ablkcipher_tfm (struct crypto_ablkcipher*) ; 
 scalar_t__ get_cryptoalg_subtype (int /*<<< orphan*/ ) ; 
 unsigned int get_space_for_phys_dsgl (unsigned int) ; 
 int /*<<< orphan*/  memcpy (unsigned int,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  pr_err (char*,scalar_t__,int,unsigned int) ; 
 int rounddown (int,int) ; 
 unsigned int roundup (scalar_t__,int) ; 
 unsigned int sg_nents_xlen (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int process_cipher(struct ablkcipher_request *req,
				  unsigned short qid,
				  struct sk_buff **skb,
				  unsigned short op_type)
{
	struct crypto_ablkcipher *tfm = crypto_ablkcipher_reqtfm(req);
	unsigned int ivsize = crypto_ablkcipher_ivsize(tfm);
	struct chcr_blkcipher_req_ctx *reqctx = ablkcipher_request_ctx(req);
	struct ablk_ctx *ablkctx = ABLK_CTX(c_ctx(tfm));
	struct	cipher_wr_param wrparam;
	int bytes, err = -EINVAL;

	reqctx->processed = 0;
	if (!req->info)
		goto error;
	if ((ablkctx->enckey_len == 0) || (ivsize > AES_BLOCK_SIZE) ||
	    (req->nbytes == 0) ||
	    (req->nbytes % crypto_ablkcipher_blocksize(tfm))) {
		pr_err("AES: Invalid value of Key Len %d nbytes %d IV Len %d\n",
		       ablkctx->enckey_len, req->nbytes, ivsize);
		goto error;
	}

	err = chcr_cipher_dma_map(&ULD_CTX(c_ctx(tfm))->lldi.pdev->dev, req);
	if (err)
		goto error;
	if (req->nbytes < (SGE_MAX_WR_LEN - (sizeof(struct chcr_wr) +
					    AES_MIN_KEY_SIZE +
					    sizeof(struct cpl_rx_phys_dsgl) +
					/*Min dsgl size*/
					    32))) {
		/* Can be sent as Imm*/
		unsigned int dnents = 0, transhdr_len, phys_dsgl, kctx_len;

		dnents = sg_nents_xlen(req->dst, req->nbytes,
				       CHCR_DST_SG_SIZE, 0);
		phys_dsgl = get_space_for_phys_dsgl(dnents);
		kctx_len = roundup(ablkctx->enckey_len, 16);
		transhdr_len = CIPHER_TRANSHDR_SIZE(kctx_len, phys_dsgl);
		reqctx->imm = (transhdr_len + IV + req->nbytes) <=
			SGE_MAX_WR_LEN;
		bytes = IV + req->nbytes;

	} else {
		reqctx->imm = 0;
	}

	if (!reqctx->imm) {
		bytes = chcr_sg_ent_in_wr(req->src, req->dst, 0,
					  CIP_SPACE_LEFT(ablkctx->enckey_len),
					  0, 0);
		if ((bytes + reqctx->processed) >= req->nbytes)
			bytes  = req->nbytes - reqctx->processed;
		else
			bytes = rounddown(bytes, 16);
	} else {
		bytes = req->nbytes;
	}
	if (get_cryptoalg_subtype(crypto_ablkcipher_tfm(tfm)) ==
	    CRYPTO_ALG_SUB_TYPE_CTR) {
		bytes = adjust_ctr_overflow(req->info, bytes);
	}
	if (get_cryptoalg_subtype(crypto_ablkcipher_tfm(tfm)) ==
	    CRYPTO_ALG_SUB_TYPE_CTR_RFC3686) {
		memcpy(reqctx->iv, ablkctx->nonce, CTR_RFC3686_NONCE_SIZE);
		memcpy(reqctx->iv + CTR_RFC3686_NONCE_SIZE, req->info,
				CTR_RFC3686_IV_SIZE);

		/* initialize counter portion of counter block */
		*(__be32 *)(reqctx->iv + CTR_RFC3686_NONCE_SIZE +
			CTR_RFC3686_IV_SIZE) = cpu_to_be32(1);

	} else {

		memcpy(reqctx->iv, req->info, IV);
	}
	if (unlikely(bytes == 0)) {
		chcr_cipher_dma_unmap(&ULD_CTX(c_ctx(tfm))->lldi.pdev->dev,
				      req);
		err = chcr_cipher_fallback(ablkctx->sw_cipher,
					   req->base.flags,
					   req->src,
					   req->dst,
					   req->nbytes,
					   reqctx->iv,
					   op_type);
		goto error;
	}
	reqctx->op = op_type;
	reqctx->srcsg = req->src;
	reqctx->dstsg = req->dst;
	reqctx->src_ofst = 0;
	reqctx->dst_ofst = 0;
	wrparam.qid = qid;
	wrparam.req = req;
	wrparam.bytes = bytes;
	*skb = create_cipher_wr(&wrparam);
	if (IS_ERR(*skb)) {
		err = PTR_ERR(*skb);
		goto unmap;
	}
	reqctx->processed = bytes;
	reqctx->last_req_len = bytes;

	return 0;
unmap:
	chcr_cipher_dma_unmap(&ULD_CTX(c_ctx(tfm))->lldi.pdev->dev, req);
error:
	return err;
}