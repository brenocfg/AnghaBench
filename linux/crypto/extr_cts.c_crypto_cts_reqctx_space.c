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
typedef  int /*<<< orphan*/  u8 ;
struct skcipher_request {int dummy; } ;
struct crypto_skcipher {int dummy; } ;
struct crypto_cts_reqctx {int dummy; } ;
struct crypto_cts_ctx {struct crypto_skcipher* child; } ;

/* Variables and functions */
 int /*<<< orphan*/ * PTR_ALIGN (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ crypto_skcipher_alignmask (struct crypto_skcipher*) ; 
 struct crypto_cts_ctx* crypto_skcipher_ctx (struct crypto_skcipher*) ; 
 int crypto_skcipher_reqsize (struct crypto_skcipher*) ; 
 struct crypto_skcipher* crypto_skcipher_reqtfm (struct skcipher_request*) ; 
 struct crypto_cts_reqctx* skcipher_request_ctx (struct skcipher_request*) ; 

__attribute__((used)) static inline u8 *crypto_cts_reqctx_space(struct skcipher_request *req)
{
	struct crypto_cts_reqctx *rctx = skcipher_request_ctx(req);
	struct crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	struct crypto_cts_ctx *ctx = crypto_skcipher_ctx(tfm);
	struct crypto_skcipher *child = ctx->child;

	return PTR_ALIGN((u8 *)(rctx + 1) + crypto_skcipher_reqsize(child),
			 crypto_skcipher_alignmask(tfm) + 1);
}