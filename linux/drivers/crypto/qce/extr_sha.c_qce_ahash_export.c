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
struct sha256_state {int /*<<< orphan*/  buf; scalar_t__ state; int /*<<< orphan*/  count; } ;
struct sha1_state {int /*<<< orphan*/  buffer; scalar_t__ state; int /*<<< orphan*/  count; } ;
struct qce_sha_reqctx {unsigned long flags; int /*<<< orphan*/  buf; int /*<<< orphan*/  digest; int /*<<< orphan*/  count; } ;
struct crypto_ahash {int dummy; } ;
struct ahash_request {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_SHA1 (unsigned long) ; 
 scalar_t__ IS_SHA1_HMAC (unsigned long) ; 
 scalar_t__ IS_SHA256 (unsigned long) ; 
 scalar_t__ IS_SHA256_HMAC (unsigned long) ; 
 struct qce_sha_reqctx* ahash_request_ctx (struct ahash_request*) ; 
 unsigned int crypto_ahash_digestsize (struct crypto_ahash*) ; 
 struct crypto_ahash* crypto_ahash_reqtfm (struct ahash_request*) ; 
 int /*<<< orphan*/  crypto_ahash_tfm (struct crypto_ahash*) ; 
 unsigned int crypto_tfm_alg_blocksize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  qce_cpu_to_be32p_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int qce_ahash_export(struct ahash_request *req, void *out)
{
	struct crypto_ahash *ahash = crypto_ahash_reqtfm(req);
	struct qce_sha_reqctx *rctx = ahash_request_ctx(req);
	unsigned long flags = rctx->flags;
	unsigned int digestsize = crypto_ahash_digestsize(ahash);
	unsigned int blocksize =
			crypto_tfm_alg_blocksize(crypto_ahash_tfm(ahash));

	if (IS_SHA1(flags) || IS_SHA1_HMAC(flags)) {
		struct sha1_state *out_state = out;

		out_state->count = rctx->count;
		qce_cpu_to_be32p_array((__be32 *)out_state->state,
				       rctx->digest, digestsize);
		memcpy(out_state->buffer, rctx->buf, blocksize);
	} else if (IS_SHA256(flags) || IS_SHA256_HMAC(flags)) {
		struct sha256_state *out_state = out;

		out_state->count = rctx->count;
		qce_cpu_to_be32p_array((__be32 *)out_state->state,
				       rctx->digest, digestsize);
		memcpy(out_state->buf, rctx->buf, blocksize);
	} else {
		return -EINVAL;
	}

	return 0;
}