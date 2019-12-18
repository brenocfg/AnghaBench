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
typedef  int /*<<< orphan*/  u32 ;
struct scatterlist {int dummy; } ;
struct device {int dummy; } ;
struct crypto_ahash {int dummy; } ;
struct cc_hw_desc {int dummy; } ;
struct cc_hash_ctx {int is_hmac; int /*<<< orphan*/  drvdata; int /*<<< orphan*/  hash_len; int /*<<< orphan*/  hw_mode; int /*<<< orphan*/  hash_mode; int /*<<< orphan*/  inter_digestsize; } ;
struct cc_crypto_req {struct ahash_request* user_arg; int /*<<< orphan*/  user_cb; } ;
struct ahash_request {unsigned int nbytes; int /*<<< orphan*/  base; int /*<<< orphan*/ * result; struct scatterlist* src; } ;
struct ahash_req_ctx {int /*<<< orphan*/  digest_buff_dma_addr; int /*<<< orphan*/  digest_bytes_len_dma_addr; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int /*<<< orphan*/  cc_sram_addr_t ;

/* Variables and functions */
 int CC_MAX_HASH_SEQ_LEN ; 
 int /*<<< orphan*/  DIN_HASH ; 
 int /*<<< orphan*/  DMA_DLLI ; 
 int /*<<< orphan*/  DO_PAD ; 
 int EBUSY ; 
 int EINPROGRESS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  HASH_PADDING_ENABLED ; 
 int /*<<< orphan*/  NS_BIT ; 
 int /*<<< orphan*/  SETUP_LOAD_KEY0 ; 
 int /*<<< orphan*/  SETUP_LOAD_STATE0 ; 
 int /*<<< orphan*/  SETUP_WRITE_STATE1 ; 
 int /*<<< orphan*/  S_DIN_to_HASH ; 
 int /*<<< orphan*/  S_HASH_to_DOUT ; 
 struct ahash_req_ctx* ahash_request_ctx (struct ahash_request*) ; 
 int /*<<< orphan*/  cc_digest_complete ; 
 int cc_fin_hmac (struct cc_hw_desc*,struct ahash_request*,int) ; 
 int cc_fin_result (struct cc_hw_desc*,struct ahash_request*,int) ; 
 int /*<<< orphan*/  cc_gfp_flags (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cc_init_req (struct device*,struct ahash_req_ctx*,struct cc_hash_ctx*) ; 
 int /*<<< orphan*/  cc_larval_digest_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cc_map_hash_request_final (int /*<<< orphan*/ ,struct ahash_req_ctx*,struct scatterlist*,unsigned int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ cc_map_req (struct device*,struct ahash_req_ctx*,struct cc_hash_ctx*) ; 
 scalar_t__ cc_map_result (struct device*,struct ahash_req_ctx*,int /*<<< orphan*/ ) ; 
 int cc_send_request (int /*<<< orphan*/ ,struct cc_crypto_req*,struct cc_hw_desc*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cc_set_desc (struct ahash_req_ctx*,struct cc_hash_ctx*,int /*<<< orphan*/ ,struct cc_hw_desc*,int,int*) ; 
 int /*<<< orphan*/  cc_unmap_hash_request (struct device*,struct ahash_req_ctx*,struct scatterlist*,int) ; 
 int /*<<< orphan*/  cc_unmap_req (struct device*,struct ahash_req_ctx*,struct cc_hash_ctx*) ; 
 int /*<<< orphan*/  cc_unmap_result (struct device*,struct ahash_req_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct cc_hash_ctx* crypto_ahash_ctx (struct crypto_ahash*) ; 
 int /*<<< orphan*/  crypto_ahash_digestsize (struct crypto_ahash*) ; 
 struct crypto_ahash* crypto_ahash_reqtfm (struct ahash_request*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,char*,unsigned int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct device* drvdata_to_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_desc_init (struct cc_hw_desc*) ; 
 int /*<<< orphan*/  set_cipher_config1 (struct cc_hw_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_cipher_do (struct cc_hw_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_cipher_mode (struct cc_hw_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_din_const (struct cc_hw_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_din_sram (struct cc_hw_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_din_type (struct cc_hw_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_dout_dlli (struct cc_hw_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_flow_mode (struct cc_hw_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_hash_cipher_mode (struct cc_hw_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_setup_mode (struct cc_hw_desc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cc_hash_digest(struct ahash_request *req)
{
	struct ahash_req_ctx *state = ahash_request_ctx(req);
	struct crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	struct cc_hash_ctx *ctx = crypto_ahash_ctx(tfm);
	u32 digestsize = crypto_ahash_digestsize(tfm);
	struct scatterlist *src = req->src;
	unsigned int nbytes = req->nbytes;
	u8 *result = req->result;
	struct device *dev = drvdata_to_dev(ctx->drvdata);
	bool is_hmac = ctx->is_hmac;
	struct cc_crypto_req cc_req = {};
	struct cc_hw_desc desc[CC_MAX_HASH_SEQ_LEN];
	cc_sram_addr_t larval_digest_addr =
		cc_larval_digest_addr(ctx->drvdata, ctx->hash_mode);
	int idx = 0;
	int rc = 0;
	gfp_t flags = cc_gfp_flags(&req->base);

	dev_dbg(dev, "===== %s-digest (%d) ====\n", is_hmac ? "hmac" : "hash",
		nbytes);

	cc_init_req(dev, state, ctx);

	if (cc_map_req(dev, state, ctx)) {
		dev_err(dev, "map_ahash_source() failed\n");
		return -ENOMEM;
	}

	if (cc_map_result(dev, state, digestsize)) {
		dev_err(dev, "map_ahash_digest() failed\n");
		cc_unmap_req(dev, state, ctx);
		return -ENOMEM;
	}

	if (cc_map_hash_request_final(ctx->drvdata, state, src, nbytes, 1,
				      flags)) {
		dev_err(dev, "map_ahash_request_final() failed\n");
		cc_unmap_result(dev, state, digestsize, result);
		cc_unmap_req(dev, state, ctx);
		return -ENOMEM;
	}

	/* Setup request structure */
	cc_req.user_cb = cc_digest_complete;
	cc_req.user_arg = req;

	/* If HMAC then load hash IPAD xor key, if HASH then load initial
	 * digest
	 */
	hw_desc_init(&desc[idx]);
	set_hash_cipher_mode(&desc[idx], ctx->hw_mode, ctx->hash_mode);
	if (is_hmac) {
		set_din_type(&desc[idx], DMA_DLLI, state->digest_buff_dma_addr,
			     ctx->inter_digestsize, NS_BIT);
	} else {
		set_din_sram(&desc[idx], larval_digest_addr,
			     ctx->inter_digestsize);
	}
	set_flow_mode(&desc[idx], S_DIN_to_HASH);
	set_setup_mode(&desc[idx], SETUP_LOAD_STATE0);
	idx++;

	/* Load the hash current length */
	hw_desc_init(&desc[idx]);
	set_hash_cipher_mode(&desc[idx], ctx->hw_mode, ctx->hash_mode);

	if (is_hmac) {
		set_din_type(&desc[idx], DMA_DLLI,
			     state->digest_bytes_len_dma_addr,
			     ctx->hash_len, NS_BIT);
	} else {
		set_din_const(&desc[idx], 0, ctx->hash_len);
		if (nbytes)
			set_cipher_config1(&desc[idx], HASH_PADDING_ENABLED);
		else
			set_cipher_do(&desc[idx], DO_PAD);
	}
	set_flow_mode(&desc[idx], S_DIN_to_HASH);
	set_setup_mode(&desc[idx], SETUP_LOAD_KEY0);
	idx++;

	cc_set_desc(state, ctx, DIN_HASH, desc, false, &idx);

	if (is_hmac) {
		/* HW last hash block padding (aka. "DO_PAD") */
		hw_desc_init(&desc[idx]);
		set_cipher_mode(&desc[idx], ctx->hw_mode);
		set_dout_dlli(&desc[idx], state->digest_buff_dma_addr,
			      ctx->hash_len, NS_BIT, 0);
		set_flow_mode(&desc[idx], S_HASH_to_DOUT);
		set_setup_mode(&desc[idx], SETUP_WRITE_STATE1);
		set_cipher_do(&desc[idx], DO_PAD);
		idx++;

		idx = cc_fin_hmac(desc, req, idx);
	}

	idx = cc_fin_result(desc, req, idx);

	rc = cc_send_request(ctx->drvdata, &cc_req, desc, idx, &req->base);
	if (rc != -EINPROGRESS && rc != -EBUSY) {
		dev_err(dev, "send_request() failed (rc=%d)\n", rc);
		cc_unmap_hash_request(dev, state, src, true);
		cc_unmap_result(dev, state, digestsize, result);
		cc_unmap_req(dev, state, ctx);
	}
	return rc;
}