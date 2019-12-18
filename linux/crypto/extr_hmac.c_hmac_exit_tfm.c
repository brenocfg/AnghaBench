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
struct hmac_ctx {int /*<<< orphan*/  hash; } ;
struct crypto_tfm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __crypto_shash_cast (struct crypto_tfm*) ; 
 int /*<<< orphan*/  crypto_free_shash (int /*<<< orphan*/ ) ; 
 struct hmac_ctx* hmac_ctx (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hmac_exit_tfm(struct crypto_tfm *tfm)
{
	struct hmac_ctx *ctx = hmac_ctx(__crypto_shash_cast(tfm));
	crypto_free_shash(ctx->hash);
}