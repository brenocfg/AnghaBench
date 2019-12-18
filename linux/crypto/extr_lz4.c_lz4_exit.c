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
struct lz4_ctx {int /*<<< orphan*/  lz4_comp_mem; } ;
struct crypto_tfm {int dummy; } ;

/* Variables and functions */
 struct lz4_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  lz4_free_ctx (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lz4_exit(struct crypto_tfm *tfm)
{
	struct lz4_ctx *ctx = crypto_tfm_ctx(tfm);

	lz4_free_ctx(NULL, ctx->lz4_comp_mem);
}