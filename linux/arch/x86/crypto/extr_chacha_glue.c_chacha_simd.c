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
struct skcipher_walk {int dummy; } ;
struct skcipher_request {scalar_t__ cryptlen; int /*<<< orphan*/  iv; } ;
struct crypto_skcipher {int dummy; } ;
struct chacha_ctx {int dummy; } ;

/* Variables and functions */
 scalar_t__ CHACHA_BLOCK_SIZE ; 
 int chacha_simd_stream_xor (struct skcipher_walk*,struct chacha_ctx*,int /*<<< orphan*/ ) ; 
 int crypto_chacha_crypt (struct skcipher_request*) ; 
 int /*<<< orphan*/  crypto_simd_usable () ; 
 struct chacha_ctx* crypto_skcipher_ctx (struct crypto_skcipher*) ; 
 struct crypto_skcipher* crypto_skcipher_reqtfm (struct skcipher_request*) ; 
 int /*<<< orphan*/  kernel_fpu_begin () ; 
 int /*<<< orphan*/  kernel_fpu_end () ; 
 int skcipher_walk_virt (struct skcipher_walk*,struct skcipher_request*,int) ; 

__attribute__((used)) static int chacha_simd(struct skcipher_request *req)
{
	struct crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	struct chacha_ctx *ctx = crypto_skcipher_ctx(tfm);
	struct skcipher_walk walk;
	int err;

	if (req->cryptlen <= CHACHA_BLOCK_SIZE || !crypto_simd_usable())
		return crypto_chacha_crypt(req);

	err = skcipher_walk_virt(&walk, req, true);
	if (err)
		return err;

	kernel_fpu_begin();
	err = chacha_simd_stream_xor(&walk, ctx, req->iv);
	kernel_fpu_end();
	return err;
}