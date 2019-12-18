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
typedef  size_t u32 ;
struct scatterlist {int dummy; } ;
struct device {int dummy; } ;
struct crypto_ahash {int /*<<< orphan*/  base; } ;
struct cc_hw_desc {int dummy; } ;
struct cc_hash_ctx {int /*<<< orphan*/  drvdata; int /*<<< orphan*/  hash_len; int /*<<< orphan*/  hash_mode; int /*<<< orphan*/  hw_mode; int /*<<< orphan*/  inter_digestsize; scalar_t__ is_hmac; } ;
struct cc_crypto_req {struct ahash_request* user_arg; int /*<<< orphan*/  user_cb; } ;
struct ahash_request {unsigned int nbytes; int /*<<< orphan*/  base; struct scatterlist* src; } ;
struct ahash_req_ctx {int /*<<< orphan*/  digest_bytes_len_dma_addr; int /*<<< orphan*/  digest_buff_dma_addr; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int CC_MAX_HASH_SEQ_LEN ; 
 int EBUSY ; 
 int EINPROGRESS ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  NS_BIT ; 
 int /*<<< orphan*/  SETUP_WRITE_STATE0 ; 
 int /*<<< orphan*/  SETUP_WRITE_STATE1 ; 
 int /*<<< orphan*/  S_HASH_to_DOUT ; 
 struct ahash_req_ctx* ahash_request_ctx (struct ahash_request*) ; 
 int /*<<< orphan*/  cc_gfp_flags (int /*<<< orphan*/ *) ; 
 int cc_map_hash_request_update (int /*<<< orphan*/ ,struct ahash_req_ctx*,struct scatterlist*,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ cc_map_req (struct device*,struct ahash_req_ctx*,struct cc_hash_ctx*) ; 
 size_t cc_restore_hash (struct cc_hw_desc*,struct cc_hash_ctx*,struct ahash_req_ctx*,size_t) ; 
 int cc_send_request (int /*<<< orphan*/ ,struct cc_crypto_req*,struct cc_hw_desc*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cc_unmap_hash_request (struct device*,struct ahash_req_ctx*,struct scatterlist*,int) ; 
 int /*<<< orphan*/  cc_unmap_req (struct device*,struct ahash_req_ctx*,struct cc_hash_ctx*) ; 
 int /*<<< orphan*/  cc_update_complete ; 
 struct cc_hash_ctx* crypto_ahash_ctx (struct crypto_ahash*) ; 
 struct crypto_ahash* crypto_ahash_reqtfm (struct ahash_request*) ; 
 unsigned int crypto_tfm_alg_blocksize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct device* drvdata_to_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_desc_init (struct cc_hw_desc*) ; 
 int /*<<< orphan*/  set_dout_dlli (struct cc_hw_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_flow_mode (struct cc_hw_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_hash_cipher_mode (struct cc_hw_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_queue_last_ind (int /*<<< orphan*/ ,struct cc_hw_desc*) ; 
 int /*<<< orphan*/  set_setup_mode (struct cc_hw_desc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cc_hash_update(struct ahash_request *req)
{
	struct ahash_req_ctx *state = ahash_request_ctx(req);
	struct crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	struct cc_hash_ctx *ctx = crypto_ahash_ctx(tfm);
	unsigned int block_size = crypto_tfm_alg_blocksize(&tfm->base);
	struct scatterlist *src = req->src;
	unsigned int nbytes = req->nbytes;
	struct device *dev = drvdata_to_dev(ctx->drvdata);
	struct cc_crypto_req cc_req = {};
	struct cc_hw_desc desc[CC_MAX_HASH_SEQ_LEN];
	u32 idx = 0;
	int rc;
	gfp_t flags = cc_gfp_flags(&req->base);

	dev_dbg(dev, "===== %s-update (%d) ====\n", ctx->is_hmac ?
		"hmac" : "hash", nbytes);

	if (nbytes == 0) {
		/* no real updates required */
		return 0;
	}

	rc = cc_map_hash_request_update(ctx->drvdata, state, src, nbytes,
					block_size, flags);
	if (rc) {
		if (rc == 1) {
			dev_dbg(dev, " data size not require HW update %x\n",
				nbytes);
			/* No hardware updates are required */
			return 0;
		}
		dev_err(dev, "map_ahash_request_update() failed\n");
		return -ENOMEM;
	}

	if (cc_map_req(dev, state, ctx)) {
		dev_err(dev, "map_ahash_source() failed\n");
		cc_unmap_hash_request(dev, state, src, true);
		return -EINVAL;
	}

	/* Setup request structure */
	cc_req.user_cb = cc_update_complete;
	cc_req.user_arg = req;

	idx = cc_restore_hash(desc, ctx, state, idx);

	/* store the hash digest result in context */
	hw_desc_init(&desc[idx]);
	set_hash_cipher_mode(&desc[idx], ctx->hw_mode, ctx->hash_mode);
	set_dout_dlli(&desc[idx], state->digest_buff_dma_addr,
		      ctx->inter_digestsize, NS_BIT, 0);
	set_flow_mode(&desc[idx], S_HASH_to_DOUT);
	set_setup_mode(&desc[idx], SETUP_WRITE_STATE0);
	idx++;

	/* store current hash length in context */
	hw_desc_init(&desc[idx]);
	set_hash_cipher_mode(&desc[idx], ctx->hw_mode, ctx->hash_mode);
	set_dout_dlli(&desc[idx], state->digest_bytes_len_dma_addr,
		      ctx->hash_len, NS_BIT, 1);
	set_queue_last_ind(ctx->drvdata, &desc[idx]);
	set_flow_mode(&desc[idx], S_HASH_to_DOUT);
	set_setup_mode(&desc[idx], SETUP_WRITE_STATE1);
	idx++;

	rc = cc_send_request(ctx->drvdata, &cc_req, desc, idx, &req->base);
	if (rc != -EINPROGRESS && rc != -EBUSY) {
		dev_err(dev, "send_request() failed (rc=%d)\n", rc);
		cc_unmap_hash_request(dev, state, src, true);
		cc_unmap_req(dev, state, ctx);
	}
	return rc;
}