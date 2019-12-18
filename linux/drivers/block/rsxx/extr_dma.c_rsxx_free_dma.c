#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rsxx_dma_ctrl {TYPE_2__* card; } ;
struct rsxx_dma {scalar_t__ cmd; int /*<<< orphan*/  dma_addr; } ;
struct TYPE_4__ {TYPE_1__* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 scalar_t__ HW_CMD_BLK_DISCARD ; 
 scalar_t__ HW_CMD_BLK_WRITE ; 
 int /*<<< orphan*/  dma_mapping_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_dma_size (struct rsxx_dma*) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct rsxx_dma*) ; 
 int /*<<< orphan*/  rsxx_dma_pool ; 

__attribute__((used)) static void rsxx_free_dma(struct rsxx_dma_ctrl *ctrl, struct rsxx_dma *dma)
{
	if (dma->cmd != HW_CMD_BLK_DISCARD) {
		if (!dma_mapping_error(&ctrl->card->dev->dev, dma->dma_addr)) {
			dma_unmap_page(&ctrl->card->dev->dev, dma->dma_addr,
				       get_dma_size(dma),
				       dma->cmd == HW_CMD_BLK_WRITE ?
						   DMA_TO_DEVICE :
						   DMA_FROM_DEVICE);
		}
	}

	kmem_cache_free(rsxx_dma_pool, dma);
}