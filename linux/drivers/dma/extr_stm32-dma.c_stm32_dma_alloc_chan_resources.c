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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct stm32_dma_device {TYPE_1__ ddev; } ;
struct stm32_dma_chan {int config_init; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 int stm32_dma_disable_chan (struct stm32_dma_chan*) ; 
 struct stm32_dma_device* stm32_dma_get_dev (struct stm32_dma_chan*) ; 
 struct stm32_dma_chan* to_stm32_dma_chan (struct dma_chan*) ; 

__attribute__((used)) static int stm32_dma_alloc_chan_resources(struct dma_chan *c)
{
	struct stm32_dma_chan *chan = to_stm32_dma_chan(c);
	struct stm32_dma_device *dmadev = stm32_dma_get_dev(chan);
	int ret;

	chan->config_init = false;

	ret = pm_runtime_get_sync(dmadev->ddev.dev);
	if (ret < 0)
		return ret;

	ret = stm32_dma_disable_chan(chan);
	if (ret < 0)
		pm_runtime_put(dmadev->ddev.dev);

	return ret;
}