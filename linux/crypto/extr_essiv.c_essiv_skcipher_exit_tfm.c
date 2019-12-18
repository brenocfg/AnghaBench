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
struct TYPE_2__ {int /*<<< orphan*/  skcipher; } ;
struct essiv_tfm_ctx {int /*<<< orphan*/  hash; int /*<<< orphan*/  essiv_cipher; TYPE_1__ u; } ;
struct crypto_skcipher {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_free_cipher (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_free_shash (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_free_skcipher (int /*<<< orphan*/ ) ; 
 struct essiv_tfm_ctx* crypto_skcipher_ctx (struct crypto_skcipher*) ; 

__attribute__((used)) static void essiv_skcipher_exit_tfm(struct crypto_skcipher *tfm)
{
	struct essiv_tfm_ctx *tctx = crypto_skcipher_ctx(tfm);

	crypto_free_skcipher(tctx->u.skcipher);
	crypto_free_cipher(tctx->essiv_cipher);
	crypto_free_shash(tctx->hash);
}