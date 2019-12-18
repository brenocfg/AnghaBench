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
typedef  size_t u32 ;
struct cppi41_desc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct cppi41_dd {int descs_phys; scalar_t__ qmgr_mem; struct cppi41_channel** chan_busy; TYPE_1__ ddev; } ;
struct cppi41_channel {size_t q_comp_num; int /*<<< orphan*/  q_num; int /*<<< orphan*/  desc_phys; scalar_t__ gcr_reg; int /*<<< orphan*/  is_tx; scalar_t__ residue; struct cppi41_dd* cdd; } ;

/* Variables and functions */
 size_t GCR_CHAN_ENABLE ; 
 size_t GCR_DESC_TYPE_HOST ; 
 size_t GCR_STARV_RETRY ; 
 scalar_t__ QMGR_QUEUE_D (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (struct cppi41_channel*) ; 
 int /*<<< orphan*/  __iowmb () ; 
 int /*<<< orphan*/  cppi_writel (size_t,scalar_t__) ; 
 size_t lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void push_desc_queue(struct cppi41_channel *c)
{
	struct cppi41_dd *cdd = c->cdd;
	u32 desc_num;
	u32 desc_phys;
	u32 reg;

	c->residue = 0;

	reg = GCR_CHAN_ENABLE;
	if (!c->is_tx) {
		reg |= GCR_STARV_RETRY;
		reg |= GCR_DESC_TYPE_HOST;
		reg |= c->q_comp_num;
	}

	cppi_writel(reg, c->gcr_reg);

	/*
	 * We don't use writel() but __raw_writel() so we have to make sure
	 * that the DMA descriptor in coherent memory made to the main memory
	 * before starting the dma engine.
	 */
	__iowmb();

	/*
	 * DMA transfers can take at least 200ms to complete with USB mass
	 * storage connected. To prevent autosuspend timeouts, we must use
	 * pm_runtime_get/put() when chan_busy[] is modified. This will get
	 * cleared in desc_to_chan() or cppi41_stop_chan() depending on the
	 * outcome of the transfer.
	 */
	pm_runtime_get(cdd->ddev.dev);

	desc_phys = lower_32_bits(c->desc_phys);
	desc_num = (desc_phys - cdd->descs_phys) / sizeof(struct cppi41_desc);
	WARN_ON(cdd->chan_busy[desc_num]);
	cdd->chan_busy[desc_num] = c;

	reg = (sizeof(struct cppi41_desc) - 24) / 4;
	reg |= desc_phys;
	cppi_writel(reg, cdd->qmgr_mem + QMGR_QUEUE_D(c->q_num));
}