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
struct crypto_aead {int dummy; } ;
struct cc_aead_ctx {int* ctr_nonce; } ;
struct aead_request {int* iv; } ;
struct aead_req_ctx {int* ctr_iv; int /*<<< orphan*/  assoclen; } ;

/* Variables and functions */
 int /*<<< orphan*/  AES_BLOCK_SIZE ; 
 int CCM_BLOCK_IV_OFFSET ; 
 scalar_t__ CCM_BLOCK_IV_SIZE ; 
 int CCM_BLOCK_NONCE_OFFSET ; 
 scalar_t__ CCM_BLOCK_NONCE_SIZE ; 
 struct aead_req_ctx* aead_request_ctx (struct aead_request*) ; 
 struct cc_aead_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 struct crypto_aead* crypto_aead_reqtfm (struct aead_request*) ; 
 int /*<<< orphan*/  memcpy (int*,int*,scalar_t__) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cc_proc_rfc4309_ccm(struct aead_request *req)
{
	struct crypto_aead *tfm = crypto_aead_reqtfm(req);
	struct cc_aead_ctx *ctx = crypto_aead_ctx(tfm);
	struct aead_req_ctx *areq_ctx = aead_request_ctx(req);

	/* L' */
	memset(areq_ctx->ctr_iv, 0, AES_BLOCK_SIZE);
	/* For RFC 4309, always use 4 bytes for message length
	 * (at most 2^32-1 bytes).
	 */
	areq_ctx->ctr_iv[0] = 3;

	/* In RFC 4309 there is an 11-bytes nonce+IV part,
	 * that we build here.
	 */
	memcpy(areq_ctx->ctr_iv + CCM_BLOCK_NONCE_OFFSET, ctx->ctr_nonce,
	       CCM_BLOCK_NONCE_SIZE);
	memcpy(areq_ctx->ctr_iv + CCM_BLOCK_IV_OFFSET, req->iv,
	       CCM_BLOCK_IV_SIZE);
	req->iv = areq_ctx->ctr_iv;
	areq_ctx->assoclen -= CCM_BLOCK_IV_SIZE;
}