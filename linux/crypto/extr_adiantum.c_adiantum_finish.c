#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct skcipher_request {unsigned int cryptlen; int /*<<< orphan*/  dst; } ;
struct crypto_skcipher {int dummy; } ;
struct adiantum_tfm_ctx {int /*<<< orphan*/  blockcipher; } ;
struct TYPE_2__ {int /*<<< orphan*/  bignum; int /*<<< orphan*/  bytes; } ;
struct adiantum_request_ctx {TYPE_1__ rbuf; int /*<<< orphan*/  header_hash; int /*<<< orphan*/  enc; } ;
typedef  int /*<<< orphan*/  le128 ;

/* Variables and functions */
 unsigned int BLOCKCIPHER_BLOCK_SIZE ; 
 int adiantum_hash_message (struct skcipher_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_cipher_decrypt_one (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct adiantum_tfm_ctx* crypto_skcipher_ctx (struct crypto_skcipher*) ; 
 struct crypto_skcipher* crypto_skcipher_reqtfm (struct skcipher_request*) ; 
 int /*<<< orphan*/  le128_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  le128_sub (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scatterwalk_map_and_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int const,unsigned int,int) ; 
 struct adiantum_request_ctx* skcipher_request_ctx (struct skcipher_request*) ; 

__attribute__((used)) static int adiantum_finish(struct skcipher_request *req)
{
	struct crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	const struct adiantum_tfm_ctx *tctx = crypto_skcipher_ctx(tfm);
	struct adiantum_request_ctx *rctx = skcipher_request_ctx(req);
	const unsigned int bulk_len = req->cryptlen - BLOCKCIPHER_BLOCK_SIZE;
	le128 digest;
	int err;

	/* If decrypting, decrypt C_M with the block cipher to get P_M */
	if (!rctx->enc)
		crypto_cipher_decrypt_one(tctx->blockcipher, rctx->rbuf.bytes,
					  rctx->rbuf.bytes);

	/*
	 * Second hash step
	 *	enc: C_R = C_M - H_{K_H}(T, C_L)
	 *	dec: P_R = P_M - H_{K_H}(T, P_L)
	 */
	err = adiantum_hash_message(req, req->dst, &digest);
	if (err)
		return err;
	le128_add(&digest, &digest, &rctx->header_hash);
	le128_sub(&rctx->rbuf.bignum, &rctx->rbuf.bignum, &digest);
	scatterwalk_map_and_copy(&rctx->rbuf.bignum, req->dst,
				 bulk_len, BLOCKCIPHER_BLOCK_SIZE, 1);
	return 0;
}