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
struct TYPE_2__ {int /*<<< orphan*/  complete; } ;
struct skcipher_request {TYPE_1__ base; int /*<<< orphan*/  iv; int /*<<< orphan*/  cryptlen; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
struct crypto_sync_skcipher {int dummy; } ;
struct crypto_skcipher {int dummy; } ;
struct crypto_async_request {int dummy; } ;
struct cryptd_skcipher_request_ctx {int /*<<< orphan*/  complete; } ;
struct cryptd_skcipher_ctx {struct crypto_sync_skcipher* child; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_TFM_REQ_MAY_SLEEP ; 
 int EINPROGRESS ; 
 int /*<<< orphan*/  SYNC_SKCIPHER_REQUEST_ON_STACK (int /*<<< orphan*/ ,struct crypto_sync_skcipher*) ; 
 int /*<<< orphan*/  cryptd_skcipher_complete (struct skcipher_request*,int) ; 
 struct cryptd_skcipher_ctx* crypto_skcipher_ctx (struct crypto_skcipher*) ; 
 int crypto_skcipher_encrypt (int /*<<< orphan*/ ) ; 
 struct crypto_skcipher* crypto_skcipher_reqtfm (struct skcipher_request*) ; 
 struct skcipher_request* skcipher_request_cast (struct crypto_async_request*) ; 
 struct cryptd_skcipher_request_ctx* skcipher_request_ctx (struct skcipher_request*) ; 
 int /*<<< orphan*/  skcipher_request_set_callback (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skcipher_request_set_crypt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skcipher_request_set_sync_tfm (int /*<<< orphan*/ ,struct crypto_sync_skcipher*) ; 
 int /*<<< orphan*/  skcipher_request_zero (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  subreq ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void cryptd_skcipher_encrypt(struct crypto_async_request *base,
				    int err)
{
	struct skcipher_request *req = skcipher_request_cast(base);
	struct cryptd_skcipher_request_ctx *rctx = skcipher_request_ctx(req);
	struct crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	struct cryptd_skcipher_ctx *ctx = crypto_skcipher_ctx(tfm);
	struct crypto_sync_skcipher *child = ctx->child;
	SYNC_SKCIPHER_REQUEST_ON_STACK(subreq, child);

	if (unlikely(err == -EINPROGRESS))
		goto out;

	skcipher_request_set_sync_tfm(subreq, child);
	skcipher_request_set_callback(subreq, CRYPTO_TFM_REQ_MAY_SLEEP,
				      NULL, NULL);
	skcipher_request_set_crypt(subreq, req->src, req->dst, req->cryptlen,
				   req->iv);

	err = crypto_skcipher_encrypt(subreq);
	skcipher_request_zero(subreq);

	req->base.complete = rctx->complete;

out:
	cryptd_skcipher_complete(req, err);
}