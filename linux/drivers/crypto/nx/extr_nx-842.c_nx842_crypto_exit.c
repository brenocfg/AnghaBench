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
struct nx842_crypto_ctx {scalar_t__ dbounce; scalar_t__ sbounce; int /*<<< orphan*/  wmem; } ;
struct crypto_tfm {int dummy; } ;

/* Variables and functions */
 struct nx842_crypto_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

void nx842_crypto_exit(struct crypto_tfm *tfm)
{
	struct nx842_crypto_ctx *ctx = crypto_tfm_ctx(tfm);

	kfree(ctx->wmem);
	free_page((unsigned long)ctx->sbounce);
	free_page((unsigned long)ctx->dbounce);
}