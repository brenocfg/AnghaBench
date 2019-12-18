#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct hash_ctx {TYPE_3__* device; } ;
struct dma_chan {TYPE_1__* device; } ;
struct TYPE_5__ {int /*<<< orphan*/  sg_len; int /*<<< orphan*/  sg; struct dma_chan* chan_mem2hash; } ;
struct TYPE_6__ {TYPE_2__ dma; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmaengine_terminate_all (struct dma_chan*) ; 

__attribute__((used)) static void hash_dma_done(struct hash_ctx *ctx)
{
	struct dma_chan *chan;

	chan = ctx->device->dma.chan_mem2hash;
	dmaengine_terminate_all(chan);
	dma_unmap_sg(chan->device->dev, ctx->device->dma.sg,
		     ctx->device->dma.sg_len, DMA_TO_DEVICE);
}