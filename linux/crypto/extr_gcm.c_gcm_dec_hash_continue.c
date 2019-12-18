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
typedef  int /*<<< orphan*/  u32 ;
struct skcipher_request {int dummy; } ;
struct crypto_gcm_ghash_ctx {int /*<<< orphan*/  cryptlen; } ;
struct TYPE_2__ {struct skcipher_request skreq; } ;
struct crypto_gcm_req_priv_ctx {struct crypto_gcm_ghash_ctx ghash_ctx; TYPE_1__ u; } ;
struct aead_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_gcm_init_crypt (struct aead_request*,int /*<<< orphan*/ ) ; 
 struct crypto_gcm_req_priv_ctx* crypto_gcm_reqctx (struct aead_request*) ; 
 int crypto_gcm_verify (struct aead_request*) ; 
 scalar_t__ crypto_skcipher_decrypt (struct skcipher_request*) ; 
 int /*<<< orphan*/  gcm_decrypt_done ; 
 int /*<<< orphan*/  skcipher_request_set_callback (struct skcipher_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct aead_request*) ; 

__attribute__((used)) static int gcm_dec_hash_continue(struct aead_request *req, u32 flags)
{
	struct crypto_gcm_req_priv_ctx *pctx = crypto_gcm_reqctx(req);
	struct skcipher_request *skreq = &pctx->u.skreq;
	struct crypto_gcm_ghash_ctx *gctx = &pctx->ghash_ctx;

	crypto_gcm_init_crypt(req, gctx->cryptlen);
	skcipher_request_set_callback(skreq, flags, gcm_decrypt_done, req);
	return crypto_skcipher_decrypt(skreq) ?: crypto_gcm_verify(req);
}