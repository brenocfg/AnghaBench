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
struct skcipher_ctx_simple {int /*<<< orphan*/  cipher; } ;
struct crypto_skcipher {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_free_cipher (int /*<<< orphan*/ ) ; 
 struct skcipher_ctx_simple* crypto_skcipher_ctx (struct crypto_skcipher*) ; 

__attribute__((used)) static void skcipher_exit_tfm_simple(struct crypto_skcipher *tfm)
{
	struct skcipher_ctx_simple *ctx = crypto_skcipher_ctx(tfm);

	crypto_free_cipher(ctx->cipher);
}