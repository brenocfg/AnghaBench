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
struct ep93xx_dma_chan {TYPE_1__* edma; } ;
struct dma_chan {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* hw_synchronize ) (struct ep93xx_dma_chan*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct ep93xx_dma_chan*) ; 
 struct ep93xx_dma_chan* to_ep93xx_dma_chan (struct dma_chan*) ; 

__attribute__((used)) static void ep93xx_dma_synchronize(struct dma_chan *chan)
{
	struct ep93xx_dma_chan *edmac = to_ep93xx_dma_chan(chan);

	if (edmac->edma->hw_synchronize)
		edmac->edma->hw_synchronize(edmac);
}