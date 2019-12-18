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
struct crypto_rfc4543_ctx {int /*<<< orphan*/  null; } ;
struct crypto_aead {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;
struct aead_request {unsigned int assoclen; unsigned int cryptlen; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYNC_SKCIPHER_REQUEST_ON_STACK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int crypto_aead_authsize (struct crypto_aead*) ; 
 struct crypto_rfc4543_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 struct crypto_aead* crypto_aead_reqtfm (struct aead_request*) ; 
 int crypto_skcipher_encrypt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nreq ; 
 int /*<<< orphan*/  skcipher_request_set_callback (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skcipher_request_set_crypt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skcipher_request_set_sync_tfm (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int crypto_rfc4543_copy_src_to_dst(struct aead_request *req, bool enc)
{
	struct crypto_aead *aead = crypto_aead_reqtfm(req);
	struct crypto_rfc4543_ctx *ctx = crypto_aead_ctx(aead);
	unsigned int authsize = crypto_aead_authsize(aead);
	unsigned int nbytes = req->assoclen + req->cryptlen -
			      (enc ? 0 : authsize);
	SYNC_SKCIPHER_REQUEST_ON_STACK(nreq, ctx->null);

	skcipher_request_set_sync_tfm(nreq, ctx->null);
	skcipher_request_set_callback(nreq, req->base.flags, NULL, NULL);
	skcipher_request_set_crypt(nreq, req->src, req->dst, nbytes, NULL);

	return crypto_skcipher_encrypt(nreq);
}