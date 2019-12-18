#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct iproc_ctx_s {TYPE_1__* shash; } ;
struct crypto_ahash {int dummy; } ;
struct ahash_request {int /*<<< orphan*/  result; } ;
struct TYPE_3__ {int /*<<< orphan*/  tfm; } ;

/* Variables and functions */
 int __ahash_final (struct ahash_request*) ; 
 struct iproc_ctx_s* crypto_ahash_ctx (struct crypto_ahash*) ; 
 struct crypto_ahash* crypto_ahash_reqtfm (struct ahash_request*) ; 
 int /*<<< orphan*/  crypto_free_shash (int /*<<< orphan*/ ) ; 
 int crypto_shash_final (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 scalar_t__ spu_no_incr_hash (struct iproc_ctx_s*) ; 

__attribute__((used)) static int ahash_final(struct ahash_request *req)
{
	struct crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	struct iproc_ctx_s *ctx = crypto_ahash_ctx(tfm);
	int ret;

	if (spu_no_incr_hash(ctx)) {
		/*
		 * If we get an incremental hashing request and it's not
		 * supported by the hardware, we need to handle it in software
		 * by calling synchronous hash functions.
		 */
		ret = crypto_shash_final(ctx->shash, req->result);

		/* Done with hash, can deallocate it now */
		crypto_free_shash(ctx->shash->tfm);
		kfree(ctx->shash);

	} else {
		/* Otherwise call the internal function which uses SPU hw */
		ret = __ahash_final(req);
	}

	return ret;
}