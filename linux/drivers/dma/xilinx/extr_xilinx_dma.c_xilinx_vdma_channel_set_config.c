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
struct xilinx_vdma_config {int master; int park_frm; int coalesc; int delay; int ext_fsync; scalar_t__ park; int /*<<< orphan*/  vflip_en; int /*<<< orphan*/  frm_cnt_en; scalar_t__ gen_lock; int /*<<< orphan*/  frm_dly; scalar_t__ reset; } ;
struct TYPE_2__ {int master; int park_frm; int coalesc; int delay; int /*<<< orphan*/  vflip_en; int /*<<< orphan*/  frm_cnt_en; scalar_t__ gen_lock; scalar_t__ park; int /*<<< orphan*/  frm_dly; } ;
struct xilinx_dma_chan {TYPE_1__ config; scalar_t__ genlock; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int XILINX_DMA_DMACR_DELAY_MASK ; 
 int XILINX_DMA_DMACR_DELAY_MAX ; 
 int XILINX_DMA_DMACR_DELAY_SHIFT ; 
 int XILINX_DMA_DMACR_FRAME_COUNT_MASK ; 
 int XILINX_DMA_DMACR_FRAME_COUNT_MAX ; 
 int XILINX_DMA_DMACR_FRAME_COUNT_SHIFT ; 
 int XILINX_DMA_DMACR_FSYNCSRC_MASK ; 
 int XILINX_DMA_DMACR_FSYNCSRC_SHIFT ; 
 int XILINX_DMA_DMACR_GENLOCK_EN ; 
 int XILINX_DMA_DMACR_MASTER_MASK ; 
 int XILINX_DMA_DMACR_MASTER_SHIFT ; 
 int /*<<< orphan*/  XILINX_DMA_REG_DMACR ; 
 int dma_ctrl_read (struct xilinx_dma_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_ctrl_write (struct xilinx_dma_chan*,int /*<<< orphan*/ ,int) ; 
 struct xilinx_dma_chan* to_xilinx_chan (struct dma_chan*) ; 
 int xilinx_dma_chan_reset (struct xilinx_dma_chan*) ; 

int xilinx_vdma_channel_set_config(struct dma_chan *dchan,
					struct xilinx_vdma_config *cfg)
{
	struct xilinx_dma_chan *chan = to_xilinx_chan(dchan);
	u32 dmacr;

	if (cfg->reset)
		return xilinx_dma_chan_reset(chan);

	dmacr = dma_ctrl_read(chan, XILINX_DMA_REG_DMACR);

	chan->config.frm_dly = cfg->frm_dly;
	chan->config.park = cfg->park;

	/* genlock settings */
	chan->config.gen_lock = cfg->gen_lock;
	chan->config.master = cfg->master;

	dmacr &= ~XILINX_DMA_DMACR_GENLOCK_EN;
	if (cfg->gen_lock && chan->genlock) {
		dmacr |= XILINX_DMA_DMACR_GENLOCK_EN;
		dmacr &= ~XILINX_DMA_DMACR_MASTER_MASK;
		dmacr |= cfg->master << XILINX_DMA_DMACR_MASTER_SHIFT;
	}

	chan->config.frm_cnt_en = cfg->frm_cnt_en;
	chan->config.vflip_en = cfg->vflip_en;

	if (cfg->park)
		chan->config.park_frm = cfg->park_frm;
	else
		chan->config.park_frm = -1;

	chan->config.coalesc = cfg->coalesc;
	chan->config.delay = cfg->delay;

	if (cfg->coalesc <= XILINX_DMA_DMACR_FRAME_COUNT_MAX) {
		dmacr &= ~XILINX_DMA_DMACR_FRAME_COUNT_MASK;
		dmacr |= cfg->coalesc << XILINX_DMA_DMACR_FRAME_COUNT_SHIFT;
		chan->config.coalesc = cfg->coalesc;
	}

	if (cfg->delay <= XILINX_DMA_DMACR_DELAY_MAX) {
		dmacr &= ~XILINX_DMA_DMACR_DELAY_MASK;
		dmacr |= cfg->delay << XILINX_DMA_DMACR_DELAY_SHIFT;
		chan->config.delay = cfg->delay;
	}

	/* FSync Source selection */
	dmacr &= ~XILINX_DMA_DMACR_FSYNCSRC_MASK;
	dmacr |= cfg->ext_fsync << XILINX_DMA_DMACR_FSYNCSRC_SHIFT;

	dma_ctrl_write(chan, XILINX_DMA_REG_DMACR, dmacr);

	return 0;
}