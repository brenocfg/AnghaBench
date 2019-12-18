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
struct skcipher_request {int /*<<< orphan*/  base; } ;
struct crypto_skcipher {int dummy; } ;
struct cryptd_skcipher_request_ctx {int /*<<< orphan*/  (* complete ) (int /*<<< orphan*/ *,int) ;} ;
struct cryptd_skcipher_ctx {int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int EINPROGRESS ; 
 int /*<<< orphan*/  crypto_free_skcipher (struct crypto_skcipher*) ; 
 struct cryptd_skcipher_ctx* crypto_skcipher_ctx (struct crypto_skcipher*) ; 
 struct crypto_skcipher* crypto_skcipher_reqtfm (struct skcipher_request*) ; 
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 
 int refcount_read (int /*<<< orphan*/ *) ; 
 struct cryptd_skcipher_request_ctx* skcipher_request_ctx (struct skcipher_request*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void cryptd_skcipher_complete(struct skcipher_request *req, int err)
{
	struct crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	struct cryptd_skcipher_ctx *ctx = crypto_skcipher_ctx(tfm);
	struct cryptd_skcipher_request_ctx *rctx = skcipher_request_ctx(req);
	int refcnt = refcount_read(&ctx->refcnt);

	local_bh_disable();
	rctx->complete(&req->base, err);
	local_bh_enable();

	if (err != -EINPROGRESS && refcnt && refcount_dec_and_test(&ctx->refcnt))
		crypto_free_skcipher(tfm);
}