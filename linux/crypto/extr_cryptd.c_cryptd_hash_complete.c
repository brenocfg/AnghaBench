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
struct crypto_ahash {int dummy; } ;
struct cryptd_hash_request_ctx {int /*<<< orphan*/  (* complete ) (int /*<<< orphan*/ *,int) ;} ;
struct cryptd_hash_ctx {int /*<<< orphan*/  refcnt; } ;
struct ahash_request {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int EINPROGRESS ; 
 struct cryptd_hash_request_ctx* ahash_request_ctx (struct ahash_request*) ; 
 struct cryptd_hash_ctx* crypto_ahash_ctx (struct crypto_ahash*) ; 
 struct crypto_ahash* crypto_ahash_reqtfm (struct ahash_request*) ; 
 int /*<<< orphan*/  crypto_free_ahash (struct crypto_ahash*) ; 
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 
 int refcount_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void cryptd_hash_complete(struct ahash_request *req, int err)
{
	struct crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	struct cryptd_hash_ctx *ctx = crypto_ahash_ctx(tfm);
	struct cryptd_hash_request_ctx *rctx = ahash_request_ctx(req);
	int refcnt = refcount_read(&ctx->refcnt);

	local_bh_disable();
	rctx->complete(&req->base, err);
	local_bh_enable();

	if (err != -EINPROGRESS && refcnt && refcount_dec_and_test(&ctx->refcnt))
		crypto_free_ahash(tfm);
}