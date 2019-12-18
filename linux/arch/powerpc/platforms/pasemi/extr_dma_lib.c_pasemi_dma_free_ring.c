#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct pasemi_dmachan {int ring_size; scalar_t__ ring_dma; int /*<<< orphan*/ * ring_virt; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_1__* dma_pdev ; 

void pasemi_dma_free_ring(struct pasemi_dmachan *chan)
{
	BUG_ON(!chan->ring_virt);

	dma_free_coherent(&dma_pdev->dev, chan->ring_size * sizeof(u64),
			  chan->ring_virt, chan->ring_dma);
	chan->ring_virt = NULL;
	chan->ring_size = 0;
	chan->ring_dma = 0;
}