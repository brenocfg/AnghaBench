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
struct skcipher_request {scalar_t__ cryptlen; int /*<<< orphan*/  iv; } ;
struct crypto_skcipher {int dummy; } ;
struct chacha_ctx {int dummy; } ;

/* Variables and functions */
 scalar_t__ CHACHA_BLOCK_SIZE ; 
 int chacha_neon_stream_xor (struct skcipher_request*,struct chacha_ctx*,int /*<<< orphan*/ ) ; 
 int crypto_chacha_crypt (struct skcipher_request*) ; 
 int /*<<< orphan*/  crypto_simd_usable () ; 
 struct chacha_ctx* crypto_skcipher_ctx (struct crypto_skcipher*) ; 
 struct crypto_skcipher* crypto_skcipher_reqtfm (struct skcipher_request*) ; 

__attribute__((used)) static int chacha_neon(struct skcipher_request *req)
{
	struct crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	struct chacha_ctx *ctx = crypto_skcipher_ctx(tfm);

	if (req->cryptlen <= CHACHA_BLOCK_SIZE || !crypto_simd_usable())
		return crypto_chacha_crypt(req);

	return chacha_neon_stream_xor(req, ctx, req->iv);
}