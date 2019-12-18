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
typedef  int u32 ;
struct TYPE_2__ {int chan_id; int /*<<< orphan*/  device; } ;
struct pch_dma_chan {TYPE_1__ chan; } ;
struct pch_dma {int dummy; } ;

/* Variables and functions */
 int DMA_STATUS_BITS_PER_CH ; 
 int DMA_STATUS_MASK_BITS ; 
 int DMA_STATUS_SHIFT_BITS ; 
 int /*<<< orphan*/  STS2 ; 
 int dma_readl (struct pch_dma*,int /*<<< orphan*/ ) ; 
 struct pch_dma* to_pd (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 pdc_get_status2(struct pch_dma_chan *pd_chan)
{
	struct pch_dma *pd = to_pd(pd_chan->chan.device);
	u32 val;

	val = dma_readl(pd, STS2);
	return DMA_STATUS_MASK_BITS & (val >> (DMA_STATUS_SHIFT_BITS +
			DMA_STATUS_BITS_PER_CH * (pd_chan->chan.chan_id - 8)));
}