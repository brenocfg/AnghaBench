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
 int ENOMEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 struct lzorle_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  lzorle_alloc_ctx (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lzorle_init(struct crypto_tfm *tfm)
{
	struct lzorle_ctx *ctx = crypto_tfm_ctx(tfm);

	ctx->lzorle_comp_mem = lzorle_alloc_ctx(NULL);
	if (IS_ERR(ctx->lzorle_comp_mem))
		return -ENOMEM;

	return 0;
}