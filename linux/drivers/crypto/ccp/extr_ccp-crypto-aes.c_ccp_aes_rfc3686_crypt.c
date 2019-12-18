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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_4__ {int /*<<< orphan*/ * nonce; } ;
struct TYPE_5__ {TYPE_1__ aes; } ;
struct ccp_ctx {TYPE_2__ u; } ;
struct ccp_aes_req_ctx {int /*<<< orphan*/ * rfc3686_iv; int /*<<< orphan*/ * rfc3686_info; } ;
struct TYPE_6__ {int /*<<< orphan*/  tfm; } ;
struct ablkcipher_request {int /*<<< orphan*/ * info; TYPE_3__ base; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  CTR_RFC3686_IV_SIZE ; 
 int /*<<< orphan*/  CTR_RFC3686_NONCE_SIZE ; 
 struct ccp_aes_req_ctx* ablkcipher_request_ctx (struct ablkcipher_request*) ; 
 int ccp_aes_crypt (struct ablkcipher_request*,int) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 struct ccp_ctx* crypto_tfm_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ccp_aes_rfc3686_crypt(struct ablkcipher_request *req, bool encrypt)
{
	struct ccp_ctx *ctx = crypto_tfm_ctx(req->base.tfm);
	struct ccp_aes_req_ctx *rctx = ablkcipher_request_ctx(req);
	u8 *iv;

	/* Initialize the CTR block */
	iv = rctx->rfc3686_iv;
	memcpy(iv, ctx->u.aes.nonce, CTR_RFC3686_NONCE_SIZE);

	iv += CTR_RFC3686_NONCE_SIZE;
	memcpy(iv, req->info, CTR_RFC3686_IV_SIZE);

	iv += CTR_RFC3686_IV_SIZE;
	*(__be32 *)iv = cpu_to_be32(1);

	/* Point to the new IV */
	rctx->rfc3686_info = req->info;
	req->info = rctx->rfc3686_iv;

	return ccp_aes_crypt(req, encrypt);
}