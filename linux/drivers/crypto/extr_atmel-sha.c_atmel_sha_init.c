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
struct atmel_sha_reqctx {int /*<<< orphan*/  buflen; scalar_t__* digcnt; scalar_t__ bufcnt; int /*<<< orphan*/  block_size; scalar_t__ flags; struct atmel_sha_dev* dd; } ;
struct atmel_sha_dev {int /*<<< orphan*/  dev; } ;
struct atmel_sha_ctx {int dummy; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SHA1_BLOCK_SIZE ; 
#define  SHA1_DIGEST_SIZE 132 
 int /*<<< orphan*/  SHA224_BLOCK_SIZE ; 
#define  SHA224_DIGEST_SIZE 131 
 int /*<<< orphan*/  SHA256_BLOCK_SIZE ; 
#define  SHA256_DIGEST_SIZE 130 
 int /*<<< orphan*/  SHA384_BLOCK_SIZE ; 
#define  SHA384_DIGEST_SIZE 129 
 int /*<<< orphan*/  SHA512_BLOCK_SIZE ; 
#define  SHA512_DIGEST_SIZE 128 
 int /*<<< orphan*/  SHA_BUFFER_LEN ; 
 scalar_t__ SHA_FLAGS_SHA1 ; 
 scalar_t__ SHA_FLAGS_SHA224 ; 
 scalar_t__ SHA_FLAGS_SHA256 ; 
 scalar_t__ SHA_FLAGS_SHA384 ; 
 scalar_t__ SHA_FLAGS_SHA512 ; 
 struct atmel_sha_reqctx* ahash_request_ctx (struct ahash_request*) ; 
 struct atmel_sha_dev* atmel_sha_find_dev (struct atmel_sha_ctx*) ; 
 struct atmel_sha_ctx* crypto_ahash_ctx (struct crypto_ahash*) ; 
 int crypto_ahash_digestsize (struct crypto_ahash*) ; 
 struct crypto_ahash* crypto_ahash_reqtfm (struct ahash_request*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int atmel_sha_init(struct ahash_request *req)
{
	struct crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	struct atmel_sha_ctx *tctx = crypto_ahash_ctx(tfm);
	struct atmel_sha_reqctx *ctx = ahash_request_ctx(req);
	struct atmel_sha_dev *dd = atmel_sha_find_dev(tctx);

	ctx->dd = dd;

	ctx->flags = 0;

	dev_dbg(dd->dev, "init: digest size: %d\n",
		crypto_ahash_digestsize(tfm));

	switch (crypto_ahash_digestsize(tfm)) {
	case SHA1_DIGEST_SIZE:
		ctx->flags |= SHA_FLAGS_SHA1;
		ctx->block_size = SHA1_BLOCK_SIZE;
		break;
	case SHA224_DIGEST_SIZE:
		ctx->flags |= SHA_FLAGS_SHA224;
		ctx->block_size = SHA224_BLOCK_SIZE;
		break;
	case SHA256_DIGEST_SIZE:
		ctx->flags |= SHA_FLAGS_SHA256;
		ctx->block_size = SHA256_BLOCK_SIZE;
		break;
	case SHA384_DIGEST_SIZE:
		ctx->flags |= SHA_FLAGS_SHA384;
		ctx->block_size = SHA384_BLOCK_SIZE;
		break;
	case SHA512_DIGEST_SIZE:
		ctx->flags |= SHA_FLAGS_SHA512;
		ctx->block_size = SHA512_BLOCK_SIZE;
		break;
	default:
		return -EINVAL;
		break;
	}

	ctx->bufcnt = 0;
	ctx->digcnt[0] = 0;
	ctx->digcnt[1] = 0;
	ctx->buflen = SHA_BUFFER_LEN;

	return 0;
}