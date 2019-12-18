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
struct nx_gcm_rctx {char* iv; } ;
struct TYPE_3__ {char* nonce; } ;
struct TYPE_4__ {TYPE_1__ gcm; } ;
struct nx_crypto_ctx {TYPE_2__ priv; } ;
struct aead_request {char* iv; int assoclen; } ;

/* Variables and functions */
 int EINVAL ; 
 int NX_GCM4106_NONCE_LEN ; 
 struct nx_gcm_rctx* aead_request_ctx (struct aead_request*) ; 
 struct nx_crypto_ctx* crypto_aead_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_aead_reqtfm (struct aead_request*) ; 
 int gcm_aes_nx_crypt (struct aead_request*,int,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 

__attribute__((used)) static int gcm4106_aes_nx_encrypt(struct aead_request *req)
{
	struct nx_crypto_ctx *nx_ctx =
		crypto_aead_ctx(crypto_aead_reqtfm(req));
	struct nx_gcm_rctx *rctx = aead_request_ctx(req);
	char *iv = rctx->iv;
	char *nonce = nx_ctx->priv.gcm.nonce;

	memcpy(iv, nonce, NX_GCM4106_NONCE_LEN);
	memcpy(iv + NX_GCM4106_NONCE_LEN, req->iv, 8);

	if (req->assoclen < 8)
		return -EINVAL;

	return gcm_aes_nx_crypt(req, 1, req->assoclen - 8);
}