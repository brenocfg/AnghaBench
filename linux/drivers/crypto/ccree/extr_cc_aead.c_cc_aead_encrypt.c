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
struct aead_request {int /*<<< orphan*/  iv; int /*<<< orphan*/  assoclen; } ;
struct aead_req_ctx {int is_gcm4543; int plaintext_authenticate_only; int /*<<< orphan*/  backup_iv; int /*<<< orphan*/  assoclen; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_CRYPTO_DIRECTION_ENCRYPT ; 
 int EBUSY ; 
 int EINPROGRESS ; 
 struct aead_req_ctx* aead_request_ctx (struct aead_request*) ; 
 int cc_proc_aead (struct aead_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct aead_req_ctx*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int cc_aead_encrypt(struct aead_request *req)
{
	struct aead_req_ctx *areq_ctx = aead_request_ctx(req);
	int rc;

	memset(areq_ctx, 0, sizeof(*areq_ctx));

	/* No generated IV required */
	areq_ctx->backup_iv = req->iv;
	areq_ctx->assoclen = req->assoclen;
	areq_ctx->is_gcm4543 = false;

	areq_ctx->plaintext_authenticate_only = false;

	rc = cc_proc_aead(req, DRV_CRYPTO_DIRECTION_ENCRYPT);
	if (rc != -EINPROGRESS && rc != -EBUSY)
		req->iv = areq_ctx->backup_iv;

	return rc;
}