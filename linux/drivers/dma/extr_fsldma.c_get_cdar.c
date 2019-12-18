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
struct fsldma_chan {TYPE_1__* regs; } ;
typedef  int dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  cdar; } ;

/* Variables and functions */
 int FSL_DMA_IN (struct fsldma_chan*,int /*<<< orphan*/ *,int) ; 
 int FSL_DMA_SNEN ; 

__attribute__((used)) static dma_addr_t get_cdar(struct fsldma_chan *chan)
{
	return FSL_DMA_IN(chan, &chan->regs->cdar, 64) & ~FSL_DMA_SNEN;
}