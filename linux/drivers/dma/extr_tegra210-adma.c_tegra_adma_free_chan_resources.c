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
struct TYPE_2__ {int /*<<< orphan*/  task; } ;
struct tegra_adma_chan {int /*<<< orphan*/  sreq_dir; scalar_t__ sreq_index; int /*<<< orphan*/  irq; TYPE_1__ vc; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TRANS_NONE ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct tegra_adma_chan*) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tdc2dev (struct tegra_adma_chan*) ; 
 int /*<<< orphan*/  tegra_adma_terminate_all (struct dma_chan*) ; 
 struct tegra_adma_chan* to_tegra_adma_chan (struct dma_chan*) ; 
 int /*<<< orphan*/  vchan_free_chan_resources (TYPE_1__*) ; 

__attribute__((used)) static void tegra_adma_free_chan_resources(struct dma_chan *dc)
{
	struct tegra_adma_chan *tdc = to_tegra_adma_chan(dc);

	tegra_adma_terminate_all(dc);
	vchan_free_chan_resources(&tdc->vc);
	tasklet_kill(&tdc->vc.task);
	free_irq(tdc->irq, tdc);
	pm_runtime_put(tdc2dev(tdc));

	tdc->sreq_index = 0;
	tdc->sreq_dir = DMA_TRANS_NONE;
}