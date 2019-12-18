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
struct crypto_shash {int dummy; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 struct shash_desc* ahash_request_ctx (struct ahash_request*) ; 
 struct crypto_shash** crypto_ahash_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_ahash_reqtfm (struct ahash_request*) ; 
 int shash_ahash_digest (struct ahash_request*,struct shash_desc*) ; 

__attribute__((used)) static int shash_async_digest(struct ahash_request *req)
{
	struct crypto_shash **ctx = crypto_ahash_ctx(crypto_ahash_reqtfm(req));
	struct shash_desc *desc = ahash_request_ctx(req);

	desc->tfm = *ctx;

	return shash_ahash_digest(req, desc);
}