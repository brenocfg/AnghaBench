#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct crypto_aead {int dummy; } ;
struct cc_hw_desc {int dummy; } ;
struct cc_crypto_req {void* user_arg; void* user_cb; } ;
struct cc_aead_ctx {scalar_t__ cipher_mode; scalar_t__ ctr_nonce; int auth_mode; int /*<<< orphan*/  drvdata; int /*<<< orphan*/  authsize; } ;
struct aead_request {scalar_t__ iv; int /*<<< orphan*/  base; int /*<<< orphan*/  cryptlen; TYPE_2__* dst; TYPE_2__* src; } ;
struct TYPE_3__ {int op_type; } ;
struct aead_req_ctx {scalar_t__ cipher_mode; scalar_t__ ctr_iv; scalar_t__ hw_iv_size; int /*<<< orphan*/  ccm_hdr_size; int /*<<< orphan*/  req_authsize; TYPE_1__ gen_ctx; int /*<<< orphan*/  assoclen; } ;
typedef  enum drv_crypto_direction { ____Placeholder_drv_crypto_direction } drv_crypto_direction ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_4__ {int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 scalar_t__ AES_BLOCK_SIZE ; 
 int /*<<< orphan*/  CRYPTO_TFM_RES_BAD_BLOCK_LEN ; 
 scalar_t__ CTR_RFC3686_BLOCK_SIZE ; 
 scalar_t__ CTR_RFC3686_IV_SIZE ; 
 scalar_t__ CTR_RFC3686_NONCE_SIZE ; 
 scalar_t__ DRV_CIPHER_CCM ; 
 scalar_t__ DRV_CIPHER_CTR ; 
 scalar_t__ DRV_CIPHER_GCTR ; 
 int DRV_CRYPTO_DIRECTION_ENCRYPT ; 
#define  DRV_HASH_NULL 131 
#define  DRV_HASH_SHA1 130 
#define  DRV_HASH_SHA256 129 
#define  DRV_HASH_XCBC_MAC 128 
 int EBUSY ; 
 int EINPROGRESS ; 
 int EINVAL ; 
 int ENOTSUPP ; 
 int MAX_AEAD_PROCESS_SEQ ; 
 struct aead_req_ctx* aead_request_ctx (struct aead_request*) ; 
 scalar_t__ cc_aead_complete ; 
 int /*<<< orphan*/  cc_ccm (struct aead_request*,struct cc_hw_desc*,int*) ; 
 int /*<<< orphan*/  cc_gcm (struct aead_request*,struct cc_hw_desc*,int*) ; 
 int /*<<< orphan*/  cc_hmac_authenc (struct aead_request*,struct cc_hw_desc*,int*) ; 
 int cc_map_aead_request (int /*<<< orphan*/ ,struct aead_request*) ; 
 int /*<<< orphan*/  cc_mlli_to_sram (struct aead_request*,struct cc_hw_desc*,int*) ; 
 int cc_send_request (int /*<<< orphan*/ ,struct cc_crypto_req*,struct cc_hw_desc*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cc_unmap_aead_request (struct device*,struct aead_request*) ; 
 int /*<<< orphan*/  cc_xcbc_authenc (struct aead_request*,struct cc_hw_desc*,int*) ; 
 int /*<<< orphan*/  ccm_header_size_null ; 
 int config_ccm_adata (struct aead_request*) ; 
 int config_gcm_context (struct aead_request*) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 struct cc_aead_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 scalar_t__ crypto_aead_ivsize (struct crypto_aead*) ; 
 struct crypto_aead* crypto_aead_reqtfm (struct aead_request*) ; 
 int /*<<< orphan*/  crypto_aead_set_flags (struct crypto_aead*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct device* drvdata_to_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  sg_virt (TYPE_2__*) ; 
 scalar_t__ validate_data_size (struct cc_aead_ctx*,int,struct aead_request*) ; 

__attribute__((used)) static int cc_proc_aead(struct aead_request *req,
			enum drv_crypto_direction direct)
{
	int rc = 0;
	int seq_len = 0;
	struct cc_hw_desc desc[MAX_AEAD_PROCESS_SEQ];
	struct crypto_aead *tfm = crypto_aead_reqtfm(req);
	struct cc_aead_ctx *ctx = crypto_aead_ctx(tfm);
	struct aead_req_ctx *areq_ctx = aead_request_ctx(req);
	struct device *dev = drvdata_to_dev(ctx->drvdata);
	struct cc_crypto_req cc_req = {};

	dev_dbg(dev, "%s context=%p req=%p iv=%p src=%p src_ofs=%d dst=%p dst_ofs=%d cryptolen=%d\n",
		((direct == DRV_CRYPTO_DIRECTION_ENCRYPT) ? "Enc" : "Dec"),
		ctx, req, req->iv, sg_virt(req->src), req->src->offset,
		sg_virt(req->dst), req->dst->offset, req->cryptlen);

	/* STAT_PHASE_0: Init and sanity checks */

	/* Check data length according to mode */
	if (validate_data_size(ctx, direct, req)) {
		dev_err(dev, "Unsupported crypt/assoc len %d/%d.\n",
			req->cryptlen, areq_ctx->assoclen);
		crypto_aead_set_flags(tfm, CRYPTO_TFM_RES_BAD_BLOCK_LEN);
		return -EINVAL;
	}

	/* Setup request structure */
	cc_req.user_cb = (void *)cc_aead_complete;
	cc_req.user_arg = (void *)req;

	/* Setup request context */
	areq_ctx->gen_ctx.op_type = direct;
	areq_ctx->req_authsize = ctx->authsize;
	areq_ctx->cipher_mode = ctx->cipher_mode;

	/* STAT_PHASE_1: Map buffers */

	if (ctx->cipher_mode == DRV_CIPHER_CTR) {
		/* Build CTR IV - Copy nonce from last 4 bytes in
		 * CTR key to first 4 bytes in CTR IV
		 */
		memcpy(areq_ctx->ctr_iv, ctx->ctr_nonce,
		       CTR_RFC3686_NONCE_SIZE);
		memcpy(areq_ctx->ctr_iv + CTR_RFC3686_NONCE_SIZE, req->iv,
		       CTR_RFC3686_IV_SIZE);
		/* Initialize counter portion of counter block */
		*(__be32 *)(areq_ctx->ctr_iv + CTR_RFC3686_NONCE_SIZE +
			    CTR_RFC3686_IV_SIZE) = cpu_to_be32(1);

		/* Replace with counter iv */
		req->iv = areq_ctx->ctr_iv;
		areq_ctx->hw_iv_size = CTR_RFC3686_BLOCK_SIZE;
	} else if ((ctx->cipher_mode == DRV_CIPHER_CCM) ||
		   (ctx->cipher_mode == DRV_CIPHER_GCTR)) {
		areq_ctx->hw_iv_size = AES_BLOCK_SIZE;
		if (areq_ctx->ctr_iv != req->iv) {
			memcpy(areq_ctx->ctr_iv, req->iv,
			       crypto_aead_ivsize(tfm));
			req->iv = areq_ctx->ctr_iv;
		}
	}  else {
		areq_ctx->hw_iv_size = crypto_aead_ivsize(tfm);
	}

	if (ctx->cipher_mode == DRV_CIPHER_CCM) {
		rc = config_ccm_adata(req);
		if (rc) {
			dev_dbg(dev, "config_ccm_adata() returned with a failure %d!",
				rc);
			goto exit;
		}
	} else {
		areq_ctx->ccm_hdr_size = ccm_header_size_null;
	}

	if (ctx->cipher_mode == DRV_CIPHER_GCTR) {
		rc = config_gcm_context(req);
		if (rc) {
			dev_dbg(dev, "config_gcm_context() returned with a failure %d!",
				rc);
			goto exit;
		}
	}

	rc = cc_map_aead_request(ctx->drvdata, req);
	if (rc) {
		dev_err(dev, "map_request() failed\n");
		goto exit;
	}

	/* STAT_PHASE_2: Create sequence */

	/* Load MLLI tables to SRAM if necessary */
	cc_mlli_to_sram(req, desc, &seq_len);

	/*TODO: move seq len by reference */
	switch (ctx->auth_mode) {
	case DRV_HASH_SHA1:
	case DRV_HASH_SHA256:
		cc_hmac_authenc(req, desc, &seq_len);
		break;
	case DRV_HASH_XCBC_MAC:
		cc_xcbc_authenc(req, desc, &seq_len);
		break;
	case DRV_HASH_NULL:
		if (ctx->cipher_mode == DRV_CIPHER_CCM)
			cc_ccm(req, desc, &seq_len);
		if (ctx->cipher_mode == DRV_CIPHER_GCTR)
			cc_gcm(req, desc, &seq_len);
		break;
	default:
		dev_err(dev, "Unsupported authenc (%d)\n", ctx->auth_mode);
		cc_unmap_aead_request(dev, req);
		rc = -ENOTSUPP;
		goto exit;
	}

	/* STAT_PHASE_3: Lock HW and push sequence */

	rc = cc_send_request(ctx->drvdata, &cc_req, desc, seq_len, &req->base);

	if (rc != -EINPROGRESS && rc != -EBUSY) {
		dev_err(dev, "send_request() failed (rc=%d)\n", rc);
		cc_unmap_aead_request(dev, req);
	}

exit:
	return rc;
}