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
struct mmp_tdma_chan {scalar_t__ irq; int /*<<< orphan*/  dev; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  devm_free_irq (int /*<<< orphan*/ ,scalar_t__,struct mmp_tdma_chan*) ; 
 int /*<<< orphan*/  mmp_tdma_free_descriptor (struct mmp_tdma_chan*) ; 
 struct mmp_tdma_chan* to_mmp_tdma_chan (struct dma_chan*) ; 

__attribute__((used)) static void mmp_tdma_free_chan_resources(struct dma_chan *chan)
{
	struct mmp_tdma_chan *tdmac = to_mmp_tdma_chan(chan);

	if (tdmac->irq)
		devm_free_irq(tdmac->dev, tdmac->irq, tdmac);
	mmp_tdma_free_descriptor(tdmac);
	return;
}