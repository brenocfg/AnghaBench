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
struct TYPE_2__ {int /*<<< orphan*/  aead; } ;
struct essiv_tfm_ctx {int /*<<< orphan*/  hash; int /*<<< orphan*/  essiv_cipher; TYPE_1__ u; } ;
struct crypto_aead {int dummy; } ;

/* Variables and functions */
 struct essiv_tfm_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 int /*<<< orphan*/  crypto_free_aead (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_free_cipher (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_free_shash (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void essiv_aead_exit_tfm(struct crypto_aead *tfm)
{
	struct essiv_tfm_ctx *tctx = crypto_aead_ctx(tfm);

	crypto_free_aead(tctx->u.aead);
	crypto_free_cipher(tctx->essiv_cipher);
	crypto_free_shash(tctx->hash);
}