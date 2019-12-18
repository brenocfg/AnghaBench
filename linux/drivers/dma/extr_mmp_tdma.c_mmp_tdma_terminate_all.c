#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mmp_tdma_chan {int dummy; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mmp_tdma_disable_chan (struct dma_chan*) ; 
 int /*<<< orphan*/  mmp_tdma_enable_irq (struct mmp_tdma_chan*,int) ; 
 struct mmp_tdma_chan* to_mmp_tdma_chan (struct dma_chan*) ; 

__attribute__((used)) static int mmp_tdma_terminate_all(struct dma_chan *chan)
{
	struct mmp_tdma_chan *tdmac = to_mmp_tdma_chan(chan);

	mmp_tdma_disable_chan(chan);
	/* disable interrupt */
	mmp_tdma_enable_irq(tdmac, false);

	return 0;
}