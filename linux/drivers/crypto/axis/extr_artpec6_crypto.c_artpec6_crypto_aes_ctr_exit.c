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
struct crypto_skcipher {int dummy; } ;
struct artpec6_cryptotfm_context {int /*<<< orphan*/  fallback; } ;

/* Variables and functions */
 int /*<<< orphan*/  artpec6_crypto_aes_exit (struct crypto_skcipher*) ; 
 int /*<<< orphan*/  crypto_free_sync_skcipher (int /*<<< orphan*/ ) ; 
 struct artpec6_cryptotfm_context* crypto_skcipher_ctx (struct crypto_skcipher*) ; 

__attribute__((used)) static void artpec6_crypto_aes_ctr_exit(struct crypto_skcipher *tfm)
{
	struct artpec6_cryptotfm_context *ctx = crypto_skcipher_ctx(tfm);

	crypto_free_sync_skcipher(ctx->fallback);
	artpec6_crypto_aes_exit(tfm);
}