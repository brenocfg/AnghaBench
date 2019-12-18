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
struct p8_aes_cbc_ctx {int /*<<< orphan*/  fallback; } ;
struct crypto_skcipher {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_free_skcipher (int /*<<< orphan*/ ) ; 
 struct p8_aes_cbc_ctx* crypto_skcipher_ctx (struct crypto_skcipher*) ; 

__attribute__((used)) static void p8_aes_cbc_exit(struct crypto_skcipher *tfm)
{
	struct p8_aes_cbc_ctx *ctx = crypto_skcipher_ctx(tfm);

	crypto_free_skcipher(ctx->fallback);
}