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
struct tegra_dma_channel {int /*<<< orphan*/  slave_id; } ;
struct tegra_dma {int /*<<< orphan*/  dma_dev; int /*<<< orphan*/  dev; } ;
struct of_phandle_args {int /*<<< orphan*/ * args; } ;
struct of_dma {struct tegra_dma* of_dma_data; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TEGRA_APBDMA_CSR_REQ_SEL_MASK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct dma_chan* dma_get_any_slave_channel (int /*<<< orphan*/ *) ; 
 struct tegra_dma_channel* to_tegra_dma_chan (struct dma_chan*) ; 

__attribute__((used)) static struct dma_chan *tegra_dma_of_xlate(struct of_phandle_args *dma_spec,
					   struct of_dma *ofdma)
{
	struct tegra_dma *tdma = ofdma->of_dma_data;
	struct dma_chan *chan;
	struct tegra_dma_channel *tdc;

	if (dma_spec->args[0] > TEGRA_APBDMA_CSR_REQ_SEL_MASK) {
		dev_err(tdma->dev, "Invalid slave id: %d\n", dma_spec->args[0]);
		return NULL;
	}

	chan = dma_get_any_slave_channel(&tdma->dma_dev);
	if (!chan)
		return NULL;

	tdc = to_tegra_dma_chan(chan);
	tdc->slave_id = dma_spec->args[0];

	return chan;
}