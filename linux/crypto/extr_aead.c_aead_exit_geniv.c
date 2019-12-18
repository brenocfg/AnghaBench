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
struct crypto_aead {int dummy; } ;
struct aead_geniv_ctx {int /*<<< orphan*/  child; } ;

/* Variables and functions */
 struct aead_geniv_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 int /*<<< orphan*/  crypto_free_aead (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_put_default_null_skcipher () ; 

void aead_exit_geniv(struct crypto_aead *tfm)
{
	struct aead_geniv_ctx *ctx = crypto_aead_ctx(tfm);

	crypto_free_aead(ctx->child);
	crypto_put_default_null_skcipher();
}