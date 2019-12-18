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
typedef  int /*<<< orphan*/  u32 ;
struct crypto_ahash {int dummy; } ;
struct atmel_sha_reqctx {size_t block_size; } ;
struct atmel_sha_hmac_ctx {int /*<<< orphan*/ * ipad; } ;
struct atmel_sha_dev {struct ahash_request* req; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SHA_REG_DIGEST (size_t) ; 
 struct atmel_sha_reqctx* ahash_request_ctx (struct ahash_request*) ; 
 int atmel_sha_hmac_compute_ipad_hash (struct atmel_sha_dev*) ; 
 int /*<<< orphan*/  atmel_sha_read (struct atmel_sha_dev*,int /*<<< orphan*/ ) ; 
 struct atmel_sha_hmac_ctx* crypto_ahash_ctx (struct crypto_ahash*) ; 
 size_t crypto_ahash_digestsize (struct crypto_ahash*) ; 
 struct crypto_ahash* crypto_ahash_reqtfm (struct ahash_request*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int atmel_sha_hmac_prehash_key_done(struct atmel_sha_dev *dd)
{
	struct ahash_request *req = dd->req;
	struct crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	struct atmel_sha_hmac_ctx *hmac = crypto_ahash_ctx(tfm);
	struct atmel_sha_reqctx *ctx = ahash_request_ctx(req);
	size_t ds = crypto_ahash_digestsize(tfm);
	size_t bs = ctx->block_size;
	size_t i, num_words = ds / sizeof(u32);

	/* Prepare ipad. */
	for (i = 0; i < num_words; ++i)
		hmac->ipad[i] = atmel_sha_read(dd, SHA_REG_DIGEST(i));
	memset((u8 *)hmac->ipad + ds, 0, bs - ds);
	return atmel_sha_hmac_compute_ipad_hash(dd);
}