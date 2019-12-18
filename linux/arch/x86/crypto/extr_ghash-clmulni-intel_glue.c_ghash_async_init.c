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
struct cryptd_ahash {int dummy; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 struct ahash_request* ahash_request_ctx (struct ahash_request*) ; 
 struct crypto_shash* cryptd_ahash_child (struct cryptd_ahash*) ; 
 struct shash_desc* cryptd_shash_desc (struct ahash_request*) ; 
 struct ghash_async_ctx* crypto_ahash_ctx (struct crypto_ahash*) ; 
 struct crypto_ahash* crypto_ahash_reqtfm (struct ahash_request*) ; 
 int crypto_shash_init (struct shash_desc*) ; 

__attribute__((used)) static int ghash_async_init(struct ahash_request *req)
{
	struct crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	struct ghash_async_ctx *ctx = crypto_ahash_ctx(tfm);
	struct ahash_request *cryptd_req = ahash_request_ctx(req);
	struct cryptd_ahash *cryptd_tfm = ctx->cryptd_tfm;
	struct shash_desc *desc = cryptd_shash_desc(cryptd_req);
	struct crypto_shash *child = cryptd_ahash_child(cryptd_tfm);

	desc->tfm = child;
	return crypto_shash_init(desc);
}