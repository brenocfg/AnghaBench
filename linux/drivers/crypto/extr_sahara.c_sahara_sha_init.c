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
struct sahara_sha_reqctx {int digest_size; int context_size; scalar_t__ active; int /*<<< orphan*/  mode; } ;
struct crypto_ahash {int dummy; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SAHARA_HDR_MDHA_ALG_SHA1 ; 
 int /*<<< orphan*/  SAHARA_HDR_MDHA_ALG_SHA256 ; 
#define  SHA1_DIGEST_SIZE 129 
#define  SHA256_DIGEST_SIZE 128 
 struct sahara_sha_reqctx* ahash_request_ctx (struct ahash_request*) ; 
 int crypto_ahash_digestsize (struct crypto_ahash*) ; 
 struct crypto_ahash* crypto_ahash_reqtfm (struct ahash_request*) ; 
 int /*<<< orphan*/  memset (struct sahara_sha_reqctx*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sahara_sha_init(struct ahash_request *req)
{
	struct crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	struct sahara_sha_reqctx *rctx = ahash_request_ctx(req);

	memset(rctx, 0, sizeof(*rctx));

	switch (crypto_ahash_digestsize(tfm)) {
	case SHA1_DIGEST_SIZE:
		rctx->mode |= SAHARA_HDR_MDHA_ALG_SHA1;
		rctx->digest_size = SHA1_DIGEST_SIZE;
		break;
	case SHA256_DIGEST_SIZE:
		rctx->mode |= SAHARA_HDR_MDHA_ALG_SHA256;
		rctx->digest_size = SHA256_DIGEST_SIZE;
		break;
	default:
		return -EINVAL;
	}

	rctx->context_size = rctx->digest_size + 4;
	rctx->active = 0;

	return 0;
}