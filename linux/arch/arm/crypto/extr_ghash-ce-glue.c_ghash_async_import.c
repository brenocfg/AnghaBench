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
struct shash_desc {int /*<<< orphan*/  tfm; } ;
struct ghash_async_ctx {int /*<<< orphan*/  cryptd_tfm; } ;
struct crypto_ahash {int dummy; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 struct ahash_request* ahash_request_ctx (struct ahash_request*) ; 
 int /*<<< orphan*/  cryptd_ahash_child (int /*<<< orphan*/ ) ; 
 struct shash_desc* cryptd_shash_desc (struct ahash_request*) ; 
 struct ghash_async_ctx* crypto_ahash_ctx (struct crypto_ahash*) ; 
 struct crypto_ahash* crypto_ahash_reqtfm (struct ahash_request*) ; 
 int crypto_shash_import (struct shash_desc*,void const*) ; 

__attribute__((used)) static int ghash_async_import(struct ahash_request *req, const void *in)
{
	struct ahash_request *cryptd_req = ahash_request_ctx(req);
	struct crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	struct ghash_async_ctx *ctx = crypto_ahash_ctx(tfm);
	struct shash_desc *desc = cryptd_shash_desc(cryptd_req);

	desc->tfm = cryptd_ahash_child(ctx->cryptd_tfm);

	return crypto_shash_import(desc, in);
}