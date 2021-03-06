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
struct lzorle_ctx {int /*<<< orphan*/  lzorle_comp_mem; } ;
struct crypto_tfm {int dummy; } ;

/* Variables and functions */
 struct lzorle_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  lzorle_free_ctx (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lzorle_exit(struct crypto_tfm *tfm)
{
	struct lzorle_ctx *ctx = crypto_tfm_ctx(tfm);

	lzorle_free_ctx(NULL, ctx->lzorle_comp_mem);
}