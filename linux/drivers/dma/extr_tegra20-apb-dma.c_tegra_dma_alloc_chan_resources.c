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
struct tegra_dma_channel {int config_init; int /*<<< orphan*/  dma_chan; struct tegra_dma* tdma; } ;
struct tegra_dma {int /*<<< orphan*/  dev; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_cookie_init (int /*<<< orphan*/ *) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 struct tegra_dma_channel* to_tegra_dma_chan (struct dma_chan*) ; 

__attribute__((used)) static int tegra_dma_alloc_chan_resources(struct dma_chan *dc)
{
	struct tegra_dma_channel *tdc = to_tegra_dma_chan(dc);
	struct tegra_dma *tdma = tdc->tdma;
	int ret;

	dma_cookie_init(&tdc->dma_chan);
	tdc->config_init = false;

	ret = pm_runtime_get_sync(tdma->dev);
	if (ret < 0)
		return ret;

	return 0;
}