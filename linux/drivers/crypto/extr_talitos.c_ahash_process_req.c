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
struct talitos_private {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  hdr; } ;
struct talitos_edesc {TYPE_1__ desc; } ;
struct talitos_ctx {scalar_t__ keylen; int /*<<< orphan*/  desc_hdr_template; struct device* dev; } ;
struct talitos_ahash_req_ctx {size_t buf_idx; unsigned int nbuf; unsigned int to_hash_later; scalar_t__ last; scalar_t__ first; int /*<<< orphan*/  swinit; int /*<<< orphan*/ ** buf; int /*<<< orphan*/  psrc; int /*<<< orphan*/  bufsl; } ;
struct device {int dummy; } ;
struct crypto_ahash {int dummy; } ;
struct ahash_request {int /*<<< orphan*/  src; } ;

/* Variables and functions */
 int /*<<< orphan*/  DESC_HDR_MODE0_MDEU_CONT ; 
 int /*<<< orphan*/  DESC_HDR_MODE0_MDEU_HMAC ; 
 int /*<<< orphan*/  DESC_HDR_MODE0_MDEU_INIT ; 
 int /*<<< orphan*/  DESC_HDR_MODE0_MDEU_PAD ; 
 scalar_t__ IS_ERR (struct talitos_edesc*) ; 
 int PTR_ERR (struct talitos_edesc*) ; 
 int /*<<< orphan*/  ahash_done ; 
 struct talitos_edesc* ahash_edesc_alloc (struct ahash_request*,unsigned int) ; 
 struct talitos_ahash_req_ctx* ahash_request_ctx (struct ahash_request*) ; 
 int common_nonsnoop_hash (struct talitos_edesc*,struct ahash_request*,unsigned int,int /*<<< orphan*/ ) ; 
 struct talitos_ctx* crypto_ahash_ctx (struct crypto_ahash*) ; 
 struct crypto_ahash* crypto_ahash_reqtfm (struct ahash_request*) ; 
 int /*<<< orphan*/  crypto_ahash_tfm (struct crypto_ahash*) ; 
 unsigned int crypto_tfm_alg_blocksize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct talitos_private* dev_get_drvdata (struct device*) ; 
 int has_ftr_sec1 (struct talitos_private*) ; 
 int /*<<< orphan*/  scatterwalk_ffwd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sg_chain (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_copy_to_buffer (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sg_init_table (int /*<<< orphan*/ ,unsigned int) ; 
 int sg_nents_for_len (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  sg_pcopy_to_buffer (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  sg_set_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static int ahash_process_req(struct ahash_request *areq, unsigned int nbytes)
{
	struct crypto_ahash *tfm = crypto_ahash_reqtfm(areq);
	struct talitos_ctx *ctx = crypto_ahash_ctx(tfm);
	struct talitos_ahash_req_ctx *req_ctx = ahash_request_ctx(areq);
	struct talitos_edesc *edesc;
	unsigned int blocksize =
			crypto_tfm_alg_blocksize(crypto_ahash_tfm(tfm));
	unsigned int nbytes_to_hash;
	unsigned int to_hash_later;
	unsigned int nsg;
	int nents;
	struct device *dev = ctx->dev;
	struct talitos_private *priv = dev_get_drvdata(dev);
	bool is_sec1 = has_ftr_sec1(priv);
	u8 *ctx_buf = req_ctx->buf[req_ctx->buf_idx];

	if (!req_ctx->last && (nbytes + req_ctx->nbuf <= blocksize)) {
		/* Buffer up to one whole block */
		nents = sg_nents_for_len(areq->src, nbytes);
		if (nents < 0) {
			dev_err(ctx->dev, "Invalid number of src SG.\n");
			return nents;
		}
		sg_copy_to_buffer(areq->src, nents,
				  ctx_buf + req_ctx->nbuf, nbytes);
		req_ctx->nbuf += nbytes;
		return 0;
	}

	/* At least (blocksize + 1) bytes are available to hash */
	nbytes_to_hash = nbytes + req_ctx->nbuf;
	to_hash_later = nbytes_to_hash & (blocksize - 1);

	if (req_ctx->last)
		to_hash_later = 0;
	else if (to_hash_later)
		/* There is a partial block. Hash the full block(s) now */
		nbytes_to_hash -= to_hash_later;
	else {
		/* Keep one block buffered */
		nbytes_to_hash -= blocksize;
		to_hash_later = blocksize;
	}

	/* Chain in any previously buffered data */
	if (!is_sec1 && req_ctx->nbuf) {
		nsg = (req_ctx->nbuf < nbytes_to_hash) ? 2 : 1;
		sg_init_table(req_ctx->bufsl, nsg);
		sg_set_buf(req_ctx->bufsl, ctx_buf, req_ctx->nbuf);
		if (nsg > 1)
			sg_chain(req_ctx->bufsl, 2, areq->src);
		req_ctx->psrc = req_ctx->bufsl;
	} else if (is_sec1 && req_ctx->nbuf && req_ctx->nbuf < blocksize) {
		int offset;

		if (nbytes_to_hash > blocksize)
			offset = blocksize - req_ctx->nbuf;
		else
			offset = nbytes_to_hash - req_ctx->nbuf;
		nents = sg_nents_for_len(areq->src, offset);
		if (nents < 0) {
			dev_err(ctx->dev, "Invalid number of src SG.\n");
			return nents;
		}
		sg_copy_to_buffer(areq->src, nents,
				  ctx_buf + req_ctx->nbuf, offset);
		req_ctx->nbuf += offset;
		req_ctx->psrc = scatterwalk_ffwd(req_ctx->bufsl, areq->src,
						 offset);
	} else
		req_ctx->psrc = areq->src;

	if (to_hash_later) {
		nents = sg_nents_for_len(areq->src, nbytes);
		if (nents < 0) {
			dev_err(ctx->dev, "Invalid number of src SG.\n");
			return nents;
		}
		sg_pcopy_to_buffer(areq->src, nents,
				   req_ctx->buf[(req_ctx->buf_idx + 1) & 1],
				      to_hash_later,
				      nbytes - to_hash_later);
	}
	req_ctx->to_hash_later = to_hash_later;

	/* Allocate extended descriptor */
	edesc = ahash_edesc_alloc(areq, nbytes_to_hash);
	if (IS_ERR(edesc))
		return PTR_ERR(edesc);

	edesc->desc.hdr = ctx->desc_hdr_template;

	/* On last one, request SEC to pad; otherwise continue */
	if (req_ctx->last)
		edesc->desc.hdr |= DESC_HDR_MODE0_MDEU_PAD;
	else
		edesc->desc.hdr |= DESC_HDR_MODE0_MDEU_CONT;

	/* request SEC to INIT hash. */
	if (req_ctx->first && !req_ctx->swinit)
		edesc->desc.hdr |= DESC_HDR_MODE0_MDEU_INIT;

	/* When the tfm context has a keylen, it's an HMAC.
	 * A first or last (ie. not middle) descriptor must request HMAC.
	 */
	if (ctx->keylen && (req_ctx->first || req_ctx->last))
		edesc->desc.hdr |= DESC_HDR_MODE0_MDEU_HMAC;

	return common_nonsnoop_hash(edesc, areq, nbytes_to_hash, ahash_done);
}