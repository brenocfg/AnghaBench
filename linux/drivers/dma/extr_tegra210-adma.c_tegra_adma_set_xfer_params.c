#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tegra_adma_chan_regs {int ctrl; int tc; int /*<<< orphan*/  fifo_ctrl; int /*<<< orphan*/  config; void* trg_addr; void* src_addr; } ;
struct tegra_adma_desc {scalar_t__ num_periods; int period_len; struct tegra_adma_chan_regs ch_regs; } ;
struct tegra_adma_chip_data {int /*<<< orphan*/  ch_fifo_ctrl; scalar_t__ has_outstanding_reqs; int /*<<< orphan*/  (* adma_get_burst_config ) (unsigned int) ;int /*<<< orphan*/  ch_req_rx_shift; int /*<<< orphan*/  ch_req_mask; int /*<<< orphan*/  ch_req_tx_shift; } ;
struct TYPE_4__ {unsigned int dst_maxburst; unsigned int src_maxburst; } ;
struct tegra_adma_chan {int /*<<< orphan*/  sreq_index; TYPE_2__ sconfig; TYPE_1__* tdma; } ;
typedef  enum dma_transfer_direction { ____Placeholder_dma_transfer_direction } dma_transfer_direction ;
typedef  void* dma_addr_t ;
struct TYPE_3__ {struct tegra_adma_chip_data* cdata; } ;

/* Variables and functions */
 scalar_t__ ADMA_CH_CONFIG_MAX_BUFS ; 
 int /*<<< orphan*/  ADMA_CH_CONFIG_SRC_BUF (scalar_t__) ; 
 int /*<<< orphan*/  ADMA_CH_CONFIG_TRG_BUF (scalar_t__) ; 
 int /*<<< orphan*/  ADMA_CH_CONFIG_WEIGHT_FOR_WRR (int) ; 
 int ADMA_CH_CTRL_DIR (unsigned int) ; 
 unsigned int ADMA_CH_CTRL_DIR_AHUB2MEM ; 
 unsigned int ADMA_CH_CTRL_DIR_MEM2AHUB ; 
 int ADMA_CH_CTRL_FLOWCTRL_EN ; 
 int ADMA_CH_CTRL_MODE_CONTINUOUS ; 
 void* ADMA_CH_REG_FIELD_VAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ADMA_CH_TC_COUNT_MASK ; 
#define  DMA_DEV_TO_MEM 129 
#define  DMA_MEM_TO_DEV 128 
 int EINVAL ; 
 int /*<<< orphan*/  TEGRA186_ADMA_CH_CONFIG_OUTSTANDING_REQS (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (unsigned int) ; 
 int /*<<< orphan*/  tdc2dev (struct tegra_adma_chan*) ; 
 int tegra_adma_request_alloc (struct tegra_adma_chan*,int) ; 

__attribute__((used)) static int tegra_adma_set_xfer_params(struct tegra_adma_chan *tdc,
				      struct tegra_adma_desc *desc,
				      dma_addr_t buf_addr,
				      enum dma_transfer_direction direction)
{
	struct tegra_adma_chan_regs *ch_regs = &desc->ch_regs;
	const struct tegra_adma_chip_data *cdata = tdc->tdma->cdata;
	unsigned int burst_size, adma_dir;

	if (desc->num_periods > ADMA_CH_CONFIG_MAX_BUFS)
		return -EINVAL;

	switch (direction) {
	case DMA_MEM_TO_DEV:
		adma_dir = ADMA_CH_CTRL_DIR_MEM2AHUB;
		burst_size = tdc->sconfig.dst_maxburst;
		ch_regs->config = ADMA_CH_CONFIG_SRC_BUF(desc->num_periods - 1);
		ch_regs->ctrl = ADMA_CH_REG_FIELD_VAL(tdc->sreq_index,
						      cdata->ch_req_mask,
						      cdata->ch_req_tx_shift);
		ch_regs->src_addr = buf_addr;
		break;

	case DMA_DEV_TO_MEM:
		adma_dir = ADMA_CH_CTRL_DIR_AHUB2MEM;
		burst_size = tdc->sconfig.src_maxburst;
		ch_regs->config = ADMA_CH_CONFIG_TRG_BUF(desc->num_periods - 1);
		ch_regs->ctrl = ADMA_CH_REG_FIELD_VAL(tdc->sreq_index,
						      cdata->ch_req_mask,
						      cdata->ch_req_rx_shift);
		ch_regs->trg_addr = buf_addr;
		break;

	default:
		dev_err(tdc2dev(tdc), "DMA direction is not supported\n");
		return -EINVAL;
	}

	ch_regs->ctrl |= ADMA_CH_CTRL_DIR(adma_dir) |
			 ADMA_CH_CTRL_MODE_CONTINUOUS |
			 ADMA_CH_CTRL_FLOWCTRL_EN;
	ch_regs->config |= cdata->adma_get_burst_config(burst_size);
	ch_regs->config |= ADMA_CH_CONFIG_WEIGHT_FOR_WRR(1);
	if (cdata->has_outstanding_reqs)
		ch_regs->config |= TEGRA186_ADMA_CH_CONFIG_OUTSTANDING_REQS(8);
	ch_regs->fifo_ctrl = cdata->ch_fifo_ctrl;
	ch_regs->tc = desc->period_len & ADMA_CH_TC_COUNT_MASK;

	return tegra_adma_request_alloc(tdc, direction);
}