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
struct dma_chan {int dummy; } ;
struct axi_dma_chan {TYPE_1__* chip; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ axi_chan_is_hw_enable (struct axi_dma_chan*) ; 
 int /*<<< orphan*/  axi_chan_name (struct axi_dma_chan*) ; 
 int /*<<< orphan*/  chan2dev (struct axi_dma_chan*) ; 
 int /*<<< orphan*/  dchan2dev (struct dma_chan*) ; 
 struct axi_dma_chan* dchan_to_axi_dma_chan (struct dma_chan*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dma_chan_alloc_chan_resources(struct dma_chan *dchan)
{
	struct axi_dma_chan *chan = dchan_to_axi_dma_chan(dchan);

	/* ASSERT: channel is idle */
	if (axi_chan_is_hw_enable(chan)) {
		dev_err(chan2dev(chan), "%s is non-idle!\n",
			axi_chan_name(chan));
		return -EBUSY;
	}

	dev_vdbg(dchan2dev(dchan), "%s: allocating\n", axi_chan_name(chan));

	pm_runtime_get(chan->chip->dev);

	return 0;
}