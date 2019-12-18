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
struct safexcel_ahash_req {int finish; int len; int block_sz; int* cache; int hmac_zlen; void* digest; scalar_t__ hmac; scalar_t__ len_is_le; } ;
struct safexcel_ahash_ctx {scalar_t__ alg; } ;
struct ahash_request {int /*<<< orphan*/  nbytes; int /*<<< orphan*/  result; } ;

/* Variables and functions */
 scalar_t__ CONTEXT_CONTROL_CRYPTO_ALG_MD5 ; 
 scalar_t__ CONTEXT_CONTROL_CRYPTO_ALG_SHA1 ; 
 scalar_t__ CONTEXT_CONTROL_CRYPTO_ALG_SHA224 ; 
 scalar_t__ CONTEXT_CONTROL_CRYPTO_ALG_SHA256 ; 
 scalar_t__ CONTEXT_CONTROL_CRYPTO_ALG_SHA384 ; 
 scalar_t__ CONTEXT_CONTROL_CRYPTO_ALG_SHA512 ; 
 void* CONTEXT_CONTROL_DIGEST_HMAC ; 
 int /*<<< orphan*/  MD5_DIGEST_SIZE ; 
 int /*<<< orphan*/  SHA1_DIGEST_SIZE ; 
 int /*<<< orphan*/  SHA224_DIGEST_SIZE ; 
 int /*<<< orphan*/  SHA256_DIGEST_SIZE ; 
 int /*<<< orphan*/  SHA384_DIGEST_SIZE ; 
 int /*<<< orphan*/  SHA512_DIGEST_SIZE ; 
 struct safexcel_ahash_req* ahash_request_ctx (struct ahash_request*) ; 
 struct safexcel_ahash_ctx* crypto_ahash_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_ahash_reqtfm (struct ahash_request*) ; 
 int /*<<< orphan*/  md5_zero_message_hash ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int safexcel_ahash_enqueue (struct ahash_request*) ; 
 int /*<<< orphan*/  sha1_zero_message_hash ; 
 int /*<<< orphan*/  sha224_zero_message_hash ; 
 int /*<<< orphan*/  sha256_zero_message_hash ; 
 int /*<<< orphan*/  sha384_zero_message_hash ; 
 int /*<<< orphan*/  sha512_zero_message_hash ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int safexcel_ahash_final(struct ahash_request *areq)
{
	struct safexcel_ahash_req *req = ahash_request_ctx(areq);
	struct safexcel_ahash_ctx *ctx = crypto_ahash_ctx(crypto_ahash_reqtfm(areq));

	req->finish = true;

	if (unlikely(!req->len && !areq->nbytes)) {
		/*
		 * If we have an overall 0 length *hash* request:
		 * The HW cannot do 0 length hash, so we provide the correct
		 * result directly here.
		 */
		if (ctx->alg == CONTEXT_CONTROL_CRYPTO_ALG_MD5)
			memcpy(areq->result, md5_zero_message_hash,
			       MD5_DIGEST_SIZE);
		else if (ctx->alg == CONTEXT_CONTROL_CRYPTO_ALG_SHA1)
			memcpy(areq->result, sha1_zero_message_hash,
			       SHA1_DIGEST_SIZE);
		else if (ctx->alg == CONTEXT_CONTROL_CRYPTO_ALG_SHA224)
			memcpy(areq->result, sha224_zero_message_hash,
			       SHA224_DIGEST_SIZE);
		else if (ctx->alg == CONTEXT_CONTROL_CRYPTO_ALG_SHA256)
			memcpy(areq->result, sha256_zero_message_hash,
			       SHA256_DIGEST_SIZE);
		else if (ctx->alg == CONTEXT_CONTROL_CRYPTO_ALG_SHA384)
			memcpy(areq->result, sha384_zero_message_hash,
			       SHA384_DIGEST_SIZE);
		else if (ctx->alg == CONTEXT_CONTROL_CRYPTO_ALG_SHA512)
			memcpy(areq->result, sha512_zero_message_hash,
			       SHA512_DIGEST_SIZE);

		return 0;
	} else if (unlikely(req->hmac &&
			    (req->len == req->block_sz) &&
			    !areq->nbytes)) {
		/*
		 * If we have an overall 0 length *HMAC* request:
		 * For HMAC, we need to finalize the inner digest
		 * and then perform the outer hash.
		 */

		/* generate pad block in the cache */
		/* start with a hash block of all zeroes */
		memset(req->cache, 0, req->block_sz);
		/* set the first byte to 0x80 to 'append a 1 bit' */
		req->cache[0] = 0x80;
		/* add the length in bits in the last 2 bytes */
		if (req->len_is_le) {
			/* Little endian length word (e.g. MD5) */
			req->cache[req->block_sz-8] = (req->block_sz << 3) &
						      255;
			req->cache[req->block_sz-7] = (req->block_sz >> 5);
		} else {
			/* Big endian length word (e.g. any SHA) */
			req->cache[req->block_sz-2] = (req->block_sz >> 5);
			req->cache[req->block_sz-1] = (req->block_sz << 3) &
						      255;
		}

		req->len += req->block_sz; /* plus 1 hash block */

		/* Set special zero-length HMAC flag */
		req->hmac_zlen = true;

		/* Finalize HMAC */
		req->digest = CONTEXT_CONTROL_DIGEST_HMAC;
	} else if (req->hmac) {
		/* Finalize HMAC */
		req->digest = CONTEXT_CONTROL_DIGEST_HMAC;
	}

	return safexcel_ahash_enqueue(areq);
}