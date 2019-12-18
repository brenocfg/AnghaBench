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
struct tegra_adma_chan {int /*<<< orphan*/  sconfig; } ;
struct dma_slave_config {int dummy; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct dma_slave_config*,int) ; 
 struct tegra_adma_chan* to_tegra_adma_chan (struct dma_chan*) ; 

__attribute__((used)) static int tegra_adma_slave_config(struct dma_chan *dc,
				   struct dma_slave_config *sconfig)
{
	struct tegra_adma_chan *tdc = to_tegra_adma_chan(dc);

	memcpy(&tdc->sconfig, sconfig, sizeof(*sconfig));

	return 0;
}