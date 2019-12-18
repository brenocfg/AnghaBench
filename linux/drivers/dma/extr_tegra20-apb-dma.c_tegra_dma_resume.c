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
struct tegra_dma_channel {struct tegra_dma* tdma; } ;
struct tegra_dma {TYPE_1__* chip_data; } ;
struct TYPE_2__ {scalar_t__ support_channel_pause; } ;

/* Variables and functions */
 int /*<<< orphan*/  TEGRA_APBDMA_CHAN_CSRE ; 
 int /*<<< orphan*/  tdc_write (struct tegra_dma_channel*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_dma_global_resume (struct tegra_dma_channel*) ; 

__attribute__((used)) static void tegra_dma_resume(struct tegra_dma_channel *tdc)
{
	struct tegra_dma *tdma = tdc->tdma;

	if (tdma->chip_data->support_channel_pause) {
		tdc_write(tdc, TEGRA_APBDMA_CHAN_CSRE, 0);
	} else {
		tegra_dma_global_resume(tdc);
	}
}