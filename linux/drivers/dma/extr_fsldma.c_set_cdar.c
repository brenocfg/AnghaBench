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
 int /*<<< orphan*/  FSL_DMA_OUT (struct fsldma_chan*,int /*<<< orphan*/ *,int,int) ; 
 int FSL_DMA_SNEN ; 

__attribute__((used)) static void set_cdar(struct fsldma_chan *chan, dma_addr_t addr)
{
	FSL_DMA_OUT(chan, &chan->regs->cdar, addr | FSL_DMA_SNEN, 64);
}