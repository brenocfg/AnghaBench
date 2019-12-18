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
struct crypto4xx_ctx {scalar_t__ sa_len; int /*<<< orphan*/ * sa_out; int /*<<< orphan*/ * sa_in; int /*<<< orphan*/  dev; } ;
struct crypto4xx_alg {int /*<<< orphan*/  dev; } ;

/* Variables and functions */

__attribute__((used)) static void crypto4xx_ctx_init(struct crypto4xx_alg *amcc_alg,
			       struct crypto4xx_ctx *ctx)
{
	ctx->dev = amcc_alg->dev;
	ctx->sa_in = NULL;
	ctx->sa_out = NULL;
	ctx->sa_len = 0;
}