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
struct sahara_ctx {scalar_t__ keylen; int /*<<< orphan*/  fallback; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;
struct ablkcipher_request {int /*<<< orphan*/  info; int /*<<< orphan*/  nbytes; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; TYPE_1__ base; } ;

/* Variables and functions */
 scalar_t__ AES_KEYSIZE_128 ; 
 int /*<<< orphan*/  FLAGS_ENCRYPT ; 
 int /*<<< orphan*/  SYNC_SKCIPHER_REQUEST_ON_STACK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sahara_ctx* crypto_ablkcipher_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_ablkcipher_reqtfm (struct ablkcipher_request*) ; 
 int crypto_skcipher_encrypt (int /*<<< orphan*/ ) ; 
 int sahara_aes_crypt (struct ablkcipher_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skcipher_request_set_callback (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skcipher_request_set_crypt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skcipher_request_set_sync_tfm (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skcipher_request_zero (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  subreq ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int sahara_aes_ecb_encrypt(struct ablkcipher_request *req)
{
	struct sahara_ctx *ctx = crypto_ablkcipher_ctx(
		crypto_ablkcipher_reqtfm(req));
	int err;

	if (unlikely(ctx->keylen != AES_KEYSIZE_128)) {
		SYNC_SKCIPHER_REQUEST_ON_STACK(subreq, ctx->fallback);

		skcipher_request_set_sync_tfm(subreq, ctx->fallback);
		skcipher_request_set_callback(subreq, req->base.flags,
					      NULL, NULL);
		skcipher_request_set_crypt(subreq, req->src, req->dst,
					   req->nbytes, req->info);
		err = crypto_skcipher_encrypt(subreq);
		skcipher_request_zero(subreq);
		return err;
	}

	return sahara_aes_crypt(req, FLAGS_ENCRYPT);
}