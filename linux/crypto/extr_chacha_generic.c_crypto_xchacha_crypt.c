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
struct skcipher_request {scalar_t__ iv; } ;
struct crypto_skcipher {int dummy; } ;
struct chacha_ctx {int /*<<< orphan*/  nrounds; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int chacha_stream_xor (struct skcipher_request*,struct chacha_ctx*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_chacha_init (int /*<<< orphan*/ *,struct chacha_ctx*,scalar_t__) ; 
 struct chacha_ctx* crypto_skcipher_ctx (struct crypto_skcipher*) ; 
 struct crypto_skcipher* crypto_skcipher_reqtfm (struct skcipher_request*) ; 
 int /*<<< orphan*/  hchacha_block (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__,int) ; 

int crypto_xchacha_crypt(struct skcipher_request *req)
{
	struct crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	struct chacha_ctx *ctx = crypto_skcipher_ctx(tfm);
	struct chacha_ctx subctx;
	u32 state[16];
	u8 real_iv[16];

	/* Compute the subkey given the original key and first 128 nonce bits */
	crypto_chacha_init(state, ctx, req->iv);
	hchacha_block(state, subctx.key, ctx->nrounds);
	subctx.nrounds = ctx->nrounds;

	/* Build the real IV */
	memcpy(&real_iv[0], req->iv + 24, 8); /* stream position */
	memcpy(&real_iv[8], req->iv + 16, 8); /* remaining 64 nonce bits */

	/* Generate the stream and XOR it with the data */
	return chacha_stream_xor(req, &subctx, real_iv);
}