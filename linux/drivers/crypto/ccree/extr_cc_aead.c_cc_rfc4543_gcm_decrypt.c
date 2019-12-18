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
struct device {int dummy; } ;
struct crypto_aead {int dummy; } ;
struct cc_aead_ctx {int /*<<< orphan*/  drvdata; } ;
struct aead_request {int /*<<< orphan*/  iv; int /*<<< orphan*/  assoclen; } ;
struct aead_req_ctx {int plaintext_authenticate_only; int is_gcm4543; int /*<<< orphan*/  backup_iv; int /*<<< orphan*/  assoclen; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_CRYPTO_DIRECTION_DECRYPT ; 
 int EBUSY ; 
 int EINPROGRESS ; 
 int EINVAL ; 
 struct aead_req_ctx* aead_request_ctx (struct aead_request*) ; 
 int cc_proc_aead (struct aead_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cc_proc_rfc4_gcm (struct aead_request*) ; 
 struct cc_aead_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 struct crypto_aead* crypto_aead_reqtfm (struct aead_request*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct device* drvdata_to_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct aead_req_ctx*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  valid_assoclen (struct aead_request*) ; 

__attribute__((used)) static int cc_rfc4543_gcm_decrypt(struct aead_request *req)
{
	/* Very similar to cc_aead_decrypt() above. */
	struct crypto_aead *tfm = crypto_aead_reqtfm(req);
	struct cc_aead_ctx *ctx = crypto_aead_ctx(tfm);
	struct device *dev = drvdata_to_dev(ctx->drvdata);
	struct aead_req_ctx *areq_ctx = aead_request_ctx(req);
	int rc = -EINVAL;

	if (!valid_assoclen(req)) {
		dev_err(dev, "invalid Assoclen:%u\n", req->assoclen);
		goto out;
	}

	memset(areq_ctx, 0, sizeof(*areq_ctx));

	//plaintext is not decryped with rfc4543
	areq_ctx->plaintext_authenticate_only = true;

	/* No generated IV required */
	areq_ctx->backup_iv = req->iv;
	areq_ctx->assoclen = req->assoclen;

	cc_proc_rfc4_gcm(req);
	areq_ctx->is_gcm4543 = true;

	rc = cc_proc_aead(req, DRV_CRYPTO_DIRECTION_DECRYPT);
	if (rc != -EINPROGRESS && rc != -EBUSY)
		req->iv = areq_ctx->backup_iv;
out:
	return rc;
}