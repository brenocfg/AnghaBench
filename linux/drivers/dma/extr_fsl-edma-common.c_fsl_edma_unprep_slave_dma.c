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
struct TYPE_5__ {TYPE_1__* device; } ;
struct TYPE_6__ {TYPE_2__ chan; } ;
struct fsl_edma_chan {scalar_t__ dma_dir; int /*<<< orphan*/  dma_dev_size; int /*<<< orphan*/  dma_dev_addr; TYPE_3__ vchan; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ DMA_NONE ; 
 int /*<<< orphan*/  dma_unmap_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fsl_edma_unprep_slave_dma(struct fsl_edma_chan *fsl_chan)
{
	if (fsl_chan->dma_dir != DMA_NONE)
		dma_unmap_resource(fsl_chan->vchan.chan.device->dev,
				   fsl_chan->dma_dev_addr,
				   fsl_chan->dma_dev_size,
				   fsl_chan->dma_dir, 0);
	fsl_chan->dma_dir = DMA_NONE;
}