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
struct ccp_device {TYPE_1__* vdata; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {unsigned int dma_chan_attr; } ;

/* Variables and functions */
#define  CCP_DMA_DFLT 130 
#define  CCP_DMA_PRIV 129 
#define  CCP_DMA_PUB 128 
 unsigned int DMA_PRIVATE ; 
 int /*<<< orphan*/  dev_info_once (int /*<<< orphan*/ ,char*,int) ; 
 int dma_chan_attr ; 

__attribute__((used)) static unsigned int ccp_get_dma_chan_attr(struct ccp_device *ccp)
{
	switch (dma_chan_attr) {
	case CCP_DMA_DFLT:
		return ccp->vdata->dma_chan_attr;

	case CCP_DMA_PRIV:
		return DMA_PRIVATE;

	case CCP_DMA_PUB:
		return 0;

	default:
		dev_info_once(ccp->dev, "Invalid value for dma_chan_attr: %d\n",
			      dma_chan_attr);
		return ccp->vdata->dma_chan_attr;
	}
}