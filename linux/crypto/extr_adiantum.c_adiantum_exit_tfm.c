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
struct adiantum_tfm_ctx {int /*<<< orphan*/  hash; int /*<<< orphan*/  blockcipher; int /*<<< orphan*/  streamcipher; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_free_cipher (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_free_shash (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_free_skcipher (int /*<<< orphan*/ ) ; 
 struct adiantum_tfm_ctx* crypto_skcipher_ctx (struct crypto_skcipher*) ; 

__attribute__((used)) static void adiantum_exit_tfm(struct crypto_skcipher *tfm)
{
	struct adiantum_tfm_ctx *tctx = crypto_skcipher_ctx(tfm);

	crypto_free_skcipher(tctx->streamcipher);
	crypto_free_cipher(tctx->blockcipher);
	crypto_free_shash(tctx->hash);
}