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
struct qat_dh_ctx {int g2; scalar_t__ p_size; int /*<<< orphan*/ * p; int /*<<< orphan*/  dma_p; int /*<<< orphan*/ * xa; int /*<<< orphan*/  dma_xa; int /*<<< orphan*/ * g; int /*<<< orphan*/  dma_g; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (struct device*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qat_dh_clear_ctx(struct device *dev, struct qat_dh_ctx *ctx)
{
	if (ctx->g) {
		dma_free_coherent(dev, ctx->p_size, ctx->g, ctx->dma_g);
		ctx->g = NULL;
	}
	if (ctx->xa) {
		dma_free_coherent(dev, ctx->p_size, ctx->xa, ctx->dma_xa);
		ctx->xa = NULL;
	}
	if (ctx->p) {
		dma_free_coherent(dev, ctx->p_size, ctx->p, ctx->dma_p);
		ctx->p = NULL;
	}
	ctx->p_size = 0;
	ctx->g2 = false;
}