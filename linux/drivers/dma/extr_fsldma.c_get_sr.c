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
typedef  int /*<<< orphan*/  u32 ;
struct fsldma_chan {TYPE_1__* regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  sr; } ;

/* Variables and functions */
 int /*<<< orphan*/  FSL_DMA_IN (struct fsldma_chan*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static u32 get_sr(struct fsldma_chan *chan)
{
	return FSL_DMA_IN(chan, &chan->regs->sr, 32);
}