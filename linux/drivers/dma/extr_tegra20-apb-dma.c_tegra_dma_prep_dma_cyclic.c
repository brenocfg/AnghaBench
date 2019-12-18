#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_6__ {unsigned long apb_ptr; int ahb_ptr; unsigned long csr; unsigned long apb_seq; unsigned long ahb_seq; } ;
struct tegra_dma_sg_req {int configured; int last_sg; int req_len; int /*<<< orphan*/  node; struct tegra_dma_desc* dma_desc; TYPE_3__ ch_regs; } ;
struct dma_async_tx_descriptor {unsigned long flags; } ;
struct tegra_dma_desc {size_t bytes_requested; struct dma_async_tx_descriptor txd; int /*<<< orphan*/  tx_list; scalar_t__ bytes_transferred; scalar_t__ cb_count; int /*<<< orphan*/  cb_node; } ;
struct tegra_dma_channel {unsigned long slave_id; int cyclic; scalar_t__ isr_handler; TYPE_2__* tdma; scalar_t__ busy; int /*<<< orphan*/  config_init; } ;
struct dma_chan {int dummy; } ;
typedef  enum dma_transfer_direction { ____Placeholder_dma_transfer_direction } dma_transfer_direction ;
typedef  enum dma_slave_buswidth { ____Placeholder_dma_slave_buswidth } dma_slave_buswidth ;
typedef  int dma_addr_t ;
struct TYPE_5__ {TYPE_1__* chip_data; } ;
struct TYPE_4__ {int max_dma_count; } ;

/* Variables and functions */
 unsigned long DMA_CTRL_ACK ; 
 unsigned long DMA_PREP_INTERRUPT ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 unsigned long TEGRA_APBDMA_AHBSEQ_BUS_WIDTH_32 ; 
 unsigned long TEGRA_APBDMA_AHBSEQ_INTR_ENB ; 
 unsigned long TEGRA_APBDMA_AHBSEQ_WRAP_NONE ; 
 unsigned long TEGRA_APBDMA_AHBSEQ_WRAP_SHIFT ; 
 unsigned long TEGRA_APBDMA_APBSEQ_WRAP_WORD_1 ; 
 unsigned long TEGRA_APBDMA_CSR_FLOW ; 
 unsigned long TEGRA_APBDMA_CSR_IE_EOC ; 
 unsigned long TEGRA_APBDMA_CSR_REQ_SEL_SHIFT ; 
 unsigned long TEGRA_APBDMA_SLAVE_ID_INVALID ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 unsigned long get_burst_size (struct tegra_dma_channel*,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ get_transfer_param (struct tegra_dma_channel*,int,unsigned long*,unsigned long*,unsigned long*,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ handle_cont_sngl_cycle_dma_done ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tdc2dev (struct tegra_dma_channel*) ; 
 struct tegra_dma_desc* tegra_dma_desc_get (struct tegra_dma_channel*) ; 
 int /*<<< orphan*/  tegra_dma_desc_put (struct tegra_dma_channel*,struct tegra_dma_desc*) ; 
 int /*<<< orphan*/  tegra_dma_prep_wcount (struct tegra_dma_channel*,TYPE_3__*,int) ; 
 struct tegra_dma_sg_req* tegra_dma_sg_req_get (struct tegra_dma_channel*) ; 
 struct tegra_dma_channel* to_tegra_dma_chan (struct dma_chan*) ; 

__attribute__((used)) static struct dma_async_tx_descriptor *tegra_dma_prep_dma_cyclic(
	struct dma_chan *dc, dma_addr_t buf_addr, size_t buf_len,
	size_t period_len, enum dma_transfer_direction direction,
	unsigned long flags)
{
	struct tegra_dma_channel *tdc = to_tegra_dma_chan(dc);
	struct tegra_dma_desc *dma_desc = NULL;
	struct tegra_dma_sg_req *sg_req = NULL;
	unsigned long csr, ahb_seq, apb_ptr, apb_seq;
	int len;
	size_t remain_len;
	dma_addr_t mem = buf_addr;
	u32 burst_size;
	enum dma_slave_buswidth slave_bw;

	if (!buf_len || !period_len) {
		dev_err(tdc2dev(tdc), "Invalid buffer/period len\n");
		return NULL;
	}

	if (!tdc->config_init) {
		dev_err(tdc2dev(tdc), "DMA slave is not configured\n");
		return NULL;
	}

	/*
	 * We allow to take more number of requests till DMA is
	 * not started. The driver will loop over all requests.
	 * Once DMA is started then new requests can be queued only after
	 * terminating the DMA.
	 */
	if (tdc->busy) {
		dev_err(tdc2dev(tdc), "Request not allowed when DMA running\n");
		return NULL;
	}

	/*
	 * We only support cycle transfer when buf_len is multiple of
	 * period_len.
	 */
	if (buf_len % period_len) {
		dev_err(tdc2dev(tdc), "buf_len is not multiple of period_len\n");
		return NULL;
	}

	len = period_len;
	if ((len & 3) || (buf_addr & 3) ||
			(len > tdc->tdma->chip_data->max_dma_count)) {
		dev_err(tdc2dev(tdc), "Req len/mem address is not correct\n");
		return NULL;
	}

	if (get_transfer_param(tdc, direction, &apb_ptr, &apb_seq, &csr,
				&burst_size, &slave_bw) < 0)
		return NULL;

	ahb_seq = TEGRA_APBDMA_AHBSEQ_INTR_ENB;
	ahb_seq |= TEGRA_APBDMA_AHBSEQ_WRAP_NONE <<
					TEGRA_APBDMA_AHBSEQ_WRAP_SHIFT;
	ahb_seq |= TEGRA_APBDMA_AHBSEQ_BUS_WIDTH_32;

	if (tdc->slave_id != TEGRA_APBDMA_SLAVE_ID_INVALID) {
		csr |= TEGRA_APBDMA_CSR_FLOW;
		csr |= tdc->slave_id << TEGRA_APBDMA_CSR_REQ_SEL_SHIFT;
	}

	if (flags & DMA_PREP_INTERRUPT) {
		csr |= TEGRA_APBDMA_CSR_IE_EOC;
	} else {
		WARN_ON_ONCE(1);
		return NULL;
	}

	apb_seq |= TEGRA_APBDMA_APBSEQ_WRAP_WORD_1;

	dma_desc = tegra_dma_desc_get(tdc);
	if (!dma_desc) {
		dev_err(tdc2dev(tdc), "not enough descriptors available\n");
		return NULL;
	}

	INIT_LIST_HEAD(&dma_desc->tx_list);
	INIT_LIST_HEAD(&dma_desc->cb_node);
	dma_desc->cb_count = 0;

	dma_desc->bytes_transferred = 0;
	dma_desc->bytes_requested = buf_len;
	remain_len = buf_len;

	/* Split transfer equal to period size */
	while (remain_len) {
		sg_req = tegra_dma_sg_req_get(tdc);
		if (!sg_req) {
			dev_err(tdc2dev(tdc), "DMA sg-req not available\n");
			tegra_dma_desc_put(tdc, dma_desc);
			return NULL;
		}

		ahb_seq |= get_burst_size(tdc, burst_size, slave_bw, len);
		sg_req->ch_regs.apb_ptr = apb_ptr;
		sg_req->ch_regs.ahb_ptr = mem;
		sg_req->ch_regs.csr = csr;
		tegra_dma_prep_wcount(tdc, &sg_req->ch_regs, len);
		sg_req->ch_regs.apb_seq = apb_seq;
		sg_req->ch_regs.ahb_seq = ahb_seq;
		sg_req->configured = false;
		sg_req->last_sg = false;
		sg_req->dma_desc = dma_desc;
		sg_req->req_len = len;

		list_add_tail(&sg_req->node, &dma_desc->tx_list);
		remain_len -= len;
		mem += len;
	}
	sg_req->last_sg = true;
	if (flags & DMA_CTRL_ACK)
		dma_desc->txd.flags = DMA_CTRL_ACK;

	/*
	 * Make sure that mode should not be conflicting with currently
	 * configured mode.
	 */
	if (!tdc->isr_handler) {
		tdc->isr_handler = handle_cont_sngl_cycle_dma_done;
		tdc->cyclic = true;
	} else {
		if (!tdc->cyclic) {
			dev_err(tdc2dev(tdc), "DMA configuration conflict\n");
			tegra_dma_desc_put(tdc, dma_desc);
			return NULL;
		}
	}

	return &dma_desc->txd;
}