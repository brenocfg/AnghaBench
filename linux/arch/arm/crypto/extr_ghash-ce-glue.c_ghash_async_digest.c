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
struct shash_desc {struct crypto_shash* tfm; } ;
struct ghash_async_ctx {struct cryptd_ahash* cryptd_tfm; } ;
struct crypto_shash {int dummy; } ;
struct crypto_ahash {int dummy; } ;
struct cryptd_ahash {int /*<<< orphan*/  base; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 struct ahash_request* ahash_request_ctx (struct ahash_request*) ; 
 int /*<<< orphan*/  ahash_request_set_tfm (struct ahash_request*,int /*<<< orphan*/ *) ; 
 struct crypto_shash* cryptd_ahash_child (struct cryptd_ahash*) ; 
 scalar_t__ cryptd_ahash_queued (struct cryptd_ahash*) ; 
 struct shash_desc* cryptd_shash_desc (struct ahash_request*) ; 
 struct ghash_async_ctx* crypto_ahash_ctx (struct crypto_ahash*) ; 
 int crypto_ahash_digest (struct ahash_request*) ; 
 struct crypto_ahash* crypto_ahash_reqtfm (struct ahash_request*) ; 
 int /*<<< orphan*/  crypto_simd_usable () ; 
 scalar_t__ in_atomic () ; 
 int /*<<< orphan*/  memcpy (struct ahash_request*,struct ahash_request*,int) ; 
 int shash_ahash_digest (struct ahash_request*,struct shash_desc*) ; 

__attribute__((used)) static int ghash_async_digest(struct ahash_request *req)
{
	struct crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	struct ghash_async_ctx *ctx = crypto_ahash_ctx(tfm);
	struct ahash_request *cryptd_req = ahash_request_ctx(req);
	struct cryptd_ahash *cryptd_tfm = ctx->cryptd_tfm;

	if (!crypto_simd_usable() ||
	    (in_atomic() && cryptd_ahash_queued(cryptd_tfm))) {
		memcpy(cryptd_req, req, sizeof(*req));
		ahash_request_set_tfm(cryptd_req, &cryptd_tfm->base);
		return crypto_ahash_digest(cryptd_req);
	} else {
		struct shash_desc *desc = cryptd_shash_desc(cryptd_req);
		struct crypto_shash *child = cryptd_ahash_child(cryptd_tfm);

		desc->tfm = child;
		return shash_ahash_digest(req, desc);
	}
}