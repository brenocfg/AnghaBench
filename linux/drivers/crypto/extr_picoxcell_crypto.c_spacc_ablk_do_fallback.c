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
struct spacc_ablk_ctx {int /*<<< orphan*/  sw_cipher; } ;
struct crypto_tfm {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;
struct ablkcipher_request {int /*<<< orphan*/  info; int /*<<< orphan*/  nbytes; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYNC_SKCIPHER_REQUEST_ON_STACK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_ablkcipher_reqtfm (struct ablkcipher_request*) ; 
 struct crypto_tfm* crypto_ablkcipher_tfm (int /*<<< orphan*/ ) ; 
 int crypto_skcipher_decrypt (int /*<<< orphan*/ ) ; 
 int crypto_skcipher_encrypt (int /*<<< orphan*/ ) ; 
 struct spacc_ablk_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  skcipher_request_set_callback (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skcipher_request_set_crypt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skcipher_request_set_sync_tfm (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skcipher_request_zero (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  subreq ; 

__attribute__((used)) static int spacc_ablk_do_fallback(struct ablkcipher_request *req,
				  unsigned alg_type, bool is_encrypt)
{
	struct crypto_tfm *old_tfm =
	    crypto_ablkcipher_tfm(crypto_ablkcipher_reqtfm(req));
	struct spacc_ablk_ctx *ctx = crypto_tfm_ctx(old_tfm);
	SYNC_SKCIPHER_REQUEST_ON_STACK(subreq, ctx->sw_cipher);
	int err;

	/*
	 * Change the request to use the software fallback transform, and once
	 * the ciphering has completed, put the old transform back into the
	 * request.
	 */
	skcipher_request_set_sync_tfm(subreq, ctx->sw_cipher);
	skcipher_request_set_callback(subreq, req->base.flags, NULL, NULL);
	skcipher_request_set_crypt(subreq, req->src, req->dst,
				   req->nbytes, req->info);
	err = is_encrypt ? crypto_skcipher_encrypt(subreq) :
			   crypto_skcipher_decrypt(subreq);
	skcipher_request_zero(subreq);

	return err;
}