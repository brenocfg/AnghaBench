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
struct crypto_authenc_esn_ctx {int /*<<< orphan*/  null; } ;
struct crypto_aead {int dummy; } ;
struct aead_request {int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYNC_SKCIPHER_REQUEST_ON_STACK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aead_request_flags (struct aead_request*) ; 
 struct crypto_authenc_esn_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 struct crypto_aead* crypto_aead_reqtfm (struct aead_request*) ; 
 int crypto_skcipher_encrypt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skcipher_request_set_callback (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skcipher_request_set_crypt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skcipher_request_set_sync_tfm (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skreq ; 

__attribute__((used)) static int crypto_authenc_esn_copy(struct aead_request *req, unsigned int len)
{
	struct crypto_aead *authenc_esn = crypto_aead_reqtfm(req);
	struct crypto_authenc_esn_ctx *ctx = crypto_aead_ctx(authenc_esn);
	SYNC_SKCIPHER_REQUEST_ON_STACK(skreq, ctx->null);

	skcipher_request_set_sync_tfm(skreq, ctx->null);
	skcipher_request_set_callback(skreq, aead_request_flags(req),
				      NULL, NULL);
	skcipher_request_set_crypt(skreq, req->src, req->dst, len, NULL);

	return crypto_skcipher_encrypt(skreq);
}