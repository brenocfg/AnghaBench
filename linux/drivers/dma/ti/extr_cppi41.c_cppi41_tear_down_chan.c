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
typedef  int u32 ;
struct dmaengine_result {int /*<<< orphan*/  result; } ;
struct cppi41_desc {int pd0; } ;
struct TYPE_2__ {int complete; int /*<<< orphan*/  submit; } ;
struct cppi41_dd {int first_td_desc; int descs_phys; TYPE_1__ td_queue; scalar_t__ qmgr_mem; struct cppi41_desc* cd; } ;
struct cppi41_channel {int td_queued; int td_retry; int td_seen; int td_desc_seen; int q_comp_num; int desc_phys; int port_num; int q_num; int /*<<< orphan*/  txd; scalar_t__ gcr_reg; scalar_t__ is_tx; struct cppi41_dd* cdd; } ;

/* Variables and functions */
 int DESC_TYPE ; 
 int DESC_TYPE_TEARD ; 
 int /*<<< orphan*/  DMA_TRANS_ABORTED ; 
 int EAGAIN ; 
 int GCR_CHAN_ENABLE ; 
 int GCR_DESC_TYPE_HOST ; 
 int GCR_STARV_RETRY ; 
 int GCR_TEARDOWN ; 
 scalar_t__ QMGR_QUEUE_D (int /*<<< orphan*/ ) ; 
 int TD_DESC_IS_RX ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  __iormb () ; 
 int /*<<< orphan*/  __iowmb () ; 
 int /*<<< orphan*/  cppi41_compute_td_desc (struct cppi41_desc*) ; 
 int cppi41_pop_desc (struct cppi41_dd*,int) ; 
 int /*<<< orphan*/  cppi_writel (int,scalar_t__) ; 
 int /*<<< orphan*/  dma_cookie_complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmaengine_desc_get_callback_invoke (int /*<<< orphan*/ *,struct dmaengine_result*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int cppi41_tear_down_chan(struct cppi41_channel *c)
{
	struct dmaengine_result abort_result;
	struct cppi41_dd *cdd = c->cdd;
	struct cppi41_desc *td;
	u32 reg;
	u32 desc_phys;
	u32 td_desc_phys;

	td = cdd->cd;
	td += cdd->first_td_desc;

	td_desc_phys = cdd->descs_phys;
	td_desc_phys += cdd->first_td_desc * sizeof(struct cppi41_desc);

	if (!c->td_queued) {
		cppi41_compute_td_desc(td);
		__iowmb();

		reg = (sizeof(struct cppi41_desc) - 24) / 4;
		reg |= td_desc_phys;
		cppi_writel(reg, cdd->qmgr_mem +
				QMGR_QUEUE_D(cdd->td_queue.submit));

		reg = GCR_CHAN_ENABLE;
		if (!c->is_tx) {
			reg |= GCR_STARV_RETRY;
			reg |= GCR_DESC_TYPE_HOST;
			reg |= cdd->td_queue.complete;
		}
		reg |= GCR_TEARDOWN;
		cppi_writel(reg, c->gcr_reg);
		c->td_queued = 1;
		c->td_retry = 500;
	}

	if (!c->td_seen || !c->td_desc_seen) {

		desc_phys = cppi41_pop_desc(cdd, cdd->td_queue.complete);
		if (!desc_phys && c->is_tx)
			desc_phys = cppi41_pop_desc(cdd, c->q_comp_num);

		if (desc_phys == c->desc_phys) {
			c->td_desc_seen = 1;

		} else if (desc_phys == td_desc_phys) {
			u32 pd0;

			__iormb();
			pd0 = td->pd0;
			WARN_ON((pd0 >> DESC_TYPE) != DESC_TYPE_TEARD);
			WARN_ON(!c->is_tx && !(pd0 & TD_DESC_IS_RX));
			WARN_ON((pd0 & 0x1f) != c->port_num);
			c->td_seen = 1;
		} else if (desc_phys) {
			WARN_ON_ONCE(1);
		}
	}
	c->td_retry--;
	/*
	 * If the TX descriptor / channel is in use, the caller needs to poke
	 * his TD bit multiple times. After that he hardware releases the
	 * transfer descriptor followed by TD descriptor. Waiting seems not to
	 * cause any difference.
	 * RX seems to be thrown out right away. However once the TearDown
	 * descriptor gets through we are done. If we have seens the transfer
	 * descriptor before the TD we fetch it from enqueue, it has to be
	 * there waiting for us.
	 */
	if (!c->td_seen && c->td_retry) {
		udelay(1);
		return -EAGAIN;
	}
	WARN_ON(!c->td_retry);

	if (!c->td_desc_seen) {
		desc_phys = cppi41_pop_desc(cdd, c->q_num);
		if (!desc_phys)
			desc_phys = cppi41_pop_desc(cdd, c->q_comp_num);
		WARN_ON(!desc_phys);
	}

	c->td_queued = 0;
	c->td_seen = 0;
	c->td_desc_seen = 0;
	cppi_writel(0, c->gcr_reg);

	/* Invoke the callback to do the necessary clean-up */
	abort_result.result = DMA_TRANS_ABORTED;
	dma_cookie_complete(&c->txd);
	dmaengine_desc_get_callback_invoke(&c->txd, &abort_result);

	return 0;
}