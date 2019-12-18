#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct skcipher_request {unsigned int cryptlen; int /*<<< orphan*/  base; void* iv; struct scatterlist* src; struct scatterlist* dst; } ;
struct scatterlist {int dummy; } ;
struct device {int dummy; } ;
struct crypto_tfm {int dummy; } ;
struct crypto_skcipher {int dummy; } ;
struct TYPE_6__ {int op_type; } ;
struct cipher_req_ctx {int /*<<< orphan*/  iv; TYPE_3__ gen_ctx; } ;
struct cc_hw_desc {int dummy; } ;
struct TYPE_4__ {int is_cpp; int /*<<< orphan*/  slot; int /*<<< orphan*/  alg; } ;
struct cc_crypto_req {TYPE_1__ cpp; void* user_arg; void* user_cb; } ;
struct TYPE_5__ {int /*<<< orphan*/  slot; int /*<<< orphan*/  alg; } ;
struct cc_cipher_ctx {scalar_t__ key_type; int /*<<< orphan*/  drvdata; TYPE_2__ cpp; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  enum drv_crypto_direction { ____Placeholder_drv_crypto_direction } drv_crypto_direction ;

/* Variables and functions */
 scalar_t__ CC_POLICY_PROTECTED_KEY ; 
 int /*<<< orphan*/  CRYPTO_TFM_RES_BAD_BLOCK_LEN ; 
 int DRV_CRYPTO_DIRECTION_ENCRYPT ; 
 int EBUSY ; 
 int EINPROGRESS ; 
 int EINVAL ; 
 int ENOMEM ; 
 int MAX_ABLKCIPHER_SEQ_LEN ; 
 scalar_t__ cc_cipher_complete ; 
 int /*<<< orphan*/  cc_gfp_flags (int /*<<< orphan*/ *) ; 
 int cc_map_cipher_request (int /*<<< orphan*/ ,struct cipher_req_ctx*,unsigned int,unsigned int,int /*<<< orphan*/ ,struct scatterlist*,struct scatterlist*,int /*<<< orphan*/ ) ; 
 int cc_send_request (int /*<<< orphan*/ ,struct cc_crypto_req*,struct cc_hw_desc*,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cc_setup_flow_desc (struct crypto_tfm*,struct cipher_req_ctx*,struct scatterlist*,struct scatterlist*,unsigned int,struct cc_hw_desc*,unsigned int*) ; 
 int /*<<< orphan*/  cc_setup_key_desc (struct crypto_tfm*,struct cipher_req_ctx*,unsigned int,struct cc_hw_desc*,unsigned int*) ; 
 int /*<<< orphan*/  cc_setup_mlli_desc (struct crypto_tfm*,struct cipher_req_ctx*,struct scatterlist*,struct scatterlist*,unsigned int,struct skcipher_request*,struct cc_hw_desc*,unsigned int*) ; 
 int /*<<< orphan*/  cc_setup_readiv_desc (struct crypto_tfm*,struct cipher_req_ctx*,unsigned int,struct cc_hw_desc*,unsigned int*) ; 
 int /*<<< orphan*/  cc_setup_state_desc (struct crypto_tfm*,struct cipher_req_ctx*,unsigned int,unsigned int,struct cc_hw_desc*,unsigned int*) ; 
 int /*<<< orphan*/  cc_unmap_cipher_request (struct device*,struct cipher_req_ctx*,unsigned int,struct scatterlist*,struct scatterlist*) ; 
 unsigned int crypto_skcipher_ivsize (struct crypto_skcipher*) ; 
 struct crypto_skcipher* crypto_skcipher_reqtfm (struct skcipher_request*) ; 
 struct crypto_tfm* crypto_skcipher_tfm (struct crypto_skcipher*) ; 
 struct cc_cipher_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  crypto_tfm_set_flags (struct crypto_tfm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,char*,struct skcipher_request*,void*,unsigned int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct device* drvdata_to_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmemdup (void*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kzfree (int /*<<< orphan*/ ) ; 
 struct cipher_req_ctx* skcipher_request_ctx (struct skcipher_request*) ; 
 scalar_t__ validate_data_size (struct cc_cipher_ctx*,unsigned int) ; 

__attribute__((used)) static int cc_cipher_process(struct skcipher_request *req,
			     enum drv_crypto_direction direction)
{
	struct crypto_skcipher *sk_tfm = crypto_skcipher_reqtfm(req);
	struct crypto_tfm *tfm = crypto_skcipher_tfm(sk_tfm);
	struct cipher_req_ctx *req_ctx = skcipher_request_ctx(req);
	unsigned int ivsize = crypto_skcipher_ivsize(sk_tfm);
	struct scatterlist *dst = req->dst;
	struct scatterlist *src = req->src;
	unsigned int nbytes = req->cryptlen;
	void *iv = req->iv;
	struct cc_cipher_ctx *ctx_p = crypto_tfm_ctx(tfm);
	struct device *dev = drvdata_to_dev(ctx_p->drvdata);
	struct cc_hw_desc desc[MAX_ABLKCIPHER_SEQ_LEN];
	struct cc_crypto_req cc_req = {};
	int rc;
	unsigned int seq_len = 0;
	gfp_t flags = cc_gfp_flags(&req->base);

	dev_dbg(dev, "%s req=%p iv=%p nbytes=%d\n",
		((direction == DRV_CRYPTO_DIRECTION_ENCRYPT) ?
		"Encrypt" : "Decrypt"), req, iv, nbytes);

	/* STAT_PHASE_0: Init and sanity checks */

	/* TODO: check data length according to mode */
	if (validate_data_size(ctx_p, nbytes)) {
		dev_err(dev, "Unsupported data size %d.\n", nbytes);
		crypto_tfm_set_flags(tfm, CRYPTO_TFM_RES_BAD_BLOCK_LEN);
		rc = -EINVAL;
		goto exit_process;
	}
	if (nbytes == 0) {
		/* No data to process is valid */
		rc = 0;
		goto exit_process;
	}

	/* The IV we are handed may be allocted from the stack so
	 * we must copy it to a DMAable buffer before use.
	 */
	req_ctx->iv = kmemdup(iv, ivsize, flags);
	if (!req_ctx->iv) {
		rc = -ENOMEM;
		goto exit_process;
	}

	/* Setup request structure */
	cc_req.user_cb = (void *)cc_cipher_complete;
	cc_req.user_arg = (void *)req;

	/* Setup CPP operation details */
	if (ctx_p->key_type == CC_POLICY_PROTECTED_KEY) {
		cc_req.cpp.is_cpp = true;
		cc_req.cpp.alg = ctx_p->cpp.alg;
		cc_req.cpp.slot = ctx_p->cpp.slot;
	}

	/* Setup request context */
	req_ctx->gen_ctx.op_type = direction;

	/* STAT_PHASE_1: Map buffers */

	rc = cc_map_cipher_request(ctx_p->drvdata, req_ctx, ivsize, nbytes,
				      req_ctx->iv, src, dst, flags);
	if (rc) {
		dev_err(dev, "map_request() failed\n");
		goto exit_process;
	}

	/* STAT_PHASE_2: Create sequence */

	/* Setup IV and XEX key used */
	cc_setup_state_desc(tfm, req_ctx, ivsize, nbytes, desc, &seq_len);
	/* Setup MLLI line, if needed */
	cc_setup_mlli_desc(tfm, req_ctx, dst, src, nbytes, req, desc, &seq_len);
	/* Setup key */
	cc_setup_key_desc(tfm, req_ctx, nbytes, desc, &seq_len);
	/* Data processing */
	cc_setup_flow_desc(tfm, req_ctx, dst, src, nbytes, desc, &seq_len);
	/* Read next IV */
	cc_setup_readiv_desc(tfm, req_ctx, ivsize, desc, &seq_len);

	/* STAT_PHASE_3: Lock HW and push sequence */

	rc = cc_send_request(ctx_p->drvdata, &cc_req, desc, seq_len,
			     &req->base);
	if (rc != -EINPROGRESS && rc != -EBUSY) {
		/* Failed to send the request or request completed
		 * synchronously
		 */
		cc_unmap_cipher_request(dev, req_ctx, ivsize, src, dst);
	}

exit_process:
	if (rc != -EINPROGRESS && rc != -EBUSY) {
		kzfree(req_ctx->iv);
	}

	return rc;
}