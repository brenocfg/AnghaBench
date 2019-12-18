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
typedef  int uint32_t ;
struct fman_dma_regs {int /*<<< orphan*/  fmdmebcr; int /*<<< orphan*/  fmdmwcr; int /*<<< orphan*/  fmdmsetr; int /*<<< orphan*/  fmdmhy; int /*<<< orphan*/  fmdmtr; int /*<<< orphan*/  fmdmmr; int /*<<< orphan*/  fmdmemsr; int /*<<< orphan*/  fmdmsr; } ;
struct fman_cfg {int dma_cache_override; int exceptions; int dma_axi_dbg_num_of_beats; int dma_emergency_bus_select; int dma_emergency_level; int dma_emergency_switch_counter; int dma_cam_num_of_entries; int dma_dbg_cnt_mode; int dma_aid_mode; int dma_sos_emergency; int dma_watchdog; int clk_freq; int cam_base_addr; scalar_t__ dma_write_buf_tsh_clr_emer; scalar_t__ dma_read_buf_tsh_clr_emer; scalar_t__ dma_comm_qtsh_clr_emer; scalar_t__ dma_write_buf_tsh_asrt_emer; scalar_t__ dma_read_buf_tsh_asrt_emer; scalar_t__ dma_comm_qtsh_asrt_emer; scalar_t__ pedantic_dma; scalar_t__ dma_en_emergency_smoother; scalar_t__ dma_en_emergency; scalar_t__ dma_stop_on_bus_error; scalar_t__ dma_aid_override; } ;

/* Variables and functions */
 int DMA_CAM_UNITS ; 
 int DMA_MODE_AID_MODE_SHIFT ; 
 int DMA_MODE_AID_OR ; 
 int DMA_MODE_AXI_DBG_MASK ; 
 int DMA_MODE_AXI_DBG_SHIFT ; 
 int DMA_MODE_BER ; 
 int DMA_MODE_CACHE_OR_SHIFT ; 
 int DMA_MODE_CEN_SHIFT ; 
 int DMA_MODE_DBG_SHIFT ; 
 int DMA_MODE_ECC ; 
 int DMA_MODE_EMER_LVL_SHIFT ; 
 int DMA_MODE_EMER_READ ; 
 int DMA_MODE_SBER ; 
 int DMA_MODE_SECURE_PROT ; 
 int DMA_STATUS_BUS_ERR ; 
 int DMA_STATUS_FM_WRITE_ECC ; 
 int DMA_STATUS_READ_ECC ; 
 int DMA_STATUS_SYSTEM_WRITE_ECC ; 
 int DMA_THRESH_COMMQ_SHIFT ; 
 int DMA_THRESH_READ_INT_BUF_SHIFT ; 
 int FMAN_EX_DMA_BUS_ERROR ; 
 int FMAN_EX_DMA_FM_WRITE_ECC ; 
 int FMAN_EX_DMA_READ_ECC ; 
 int FMAN_EX_DMA_SYSTEM_WRITE_ECC ; 
 int ioread32be (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite32be (int,int /*<<< orphan*/ *) ; 

int fman_dma_init(struct fman_dma_regs *dma_rg, struct fman_cfg *cfg)
{
	uint32_t    tmp_reg;

	/**********************/
	/* Init DMA Registers */
	/**********************/
	/* clear status reg events */
	/* oren - check!!!  */
	tmp_reg = (DMA_STATUS_BUS_ERR | DMA_STATUS_READ_ECC |
			DMA_STATUS_SYSTEM_WRITE_ECC | DMA_STATUS_FM_WRITE_ECC);
	iowrite32be(ioread32be(&dma_rg->fmdmsr) | tmp_reg,
			&dma_rg->fmdmsr);

	/* configure mode register */
	tmp_reg = 0;
	tmp_reg |= cfg->dma_cache_override << DMA_MODE_CACHE_OR_SHIFT;
	if (cfg->dma_aid_override)
		tmp_reg |= DMA_MODE_AID_OR;
	if (cfg->exceptions & FMAN_EX_DMA_BUS_ERROR)
		tmp_reg |= DMA_MODE_BER;
	if ((cfg->exceptions & FMAN_EX_DMA_SYSTEM_WRITE_ECC) |
		(cfg->exceptions & FMAN_EX_DMA_READ_ECC) |
		(cfg->exceptions & FMAN_EX_DMA_FM_WRITE_ECC))
		tmp_reg |= DMA_MODE_ECC;
	if (cfg->dma_stop_on_bus_error)
		tmp_reg |= DMA_MODE_SBER;
	if(cfg->dma_axi_dbg_num_of_beats)
	    tmp_reg |= (uint32_t)(DMA_MODE_AXI_DBG_MASK &
		           ((cfg->dma_axi_dbg_num_of_beats - 1) << DMA_MODE_AXI_DBG_SHIFT));

	if (cfg->dma_en_emergency) {
		tmp_reg |= cfg->dma_emergency_bus_select;
		tmp_reg |= cfg->dma_emergency_level << DMA_MODE_EMER_LVL_SHIFT;
	if (cfg->dma_en_emergency_smoother)
		iowrite32be(cfg->dma_emergency_switch_counter,
				&dma_rg->fmdmemsr);
	}
	tmp_reg |= ((cfg->dma_cam_num_of_entries / DMA_CAM_UNITS) - 1) <<
			DMA_MODE_CEN_SHIFT;
	tmp_reg |= DMA_MODE_SECURE_PROT;
	tmp_reg |= cfg->dma_dbg_cnt_mode << DMA_MODE_DBG_SHIFT;
	tmp_reg |= cfg->dma_aid_mode << DMA_MODE_AID_MODE_SHIFT;

	if (cfg->pedantic_dma)
		tmp_reg |= DMA_MODE_EMER_READ;

	iowrite32be(tmp_reg, &dma_rg->fmdmmr);

	/* configure thresholds register */
	tmp_reg = ((uint32_t)cfg->dma_comm_qtsh_asrt_emer <<
			DMA_THRESH_COMMQ_SHIFT) |
			((uint32_t)cfg->dma_read_buf_tsh_asrt_emer <<
			DMA_THRESH_READ_INT_BUF_SHIFT) |
			((uint32_t)cfg->dma_write_buf_tsh_asrt_emer);

	iowrite32be(tmp_reg, &dma_rg->fmdmtr);

	/* configure hysteresis register */
	tmp_reg = ((uint32_t)cfg->dma_comm_qtsh_clr_emer <<
		DMA_THRESH_COMMQ_SHIFT) |
		((uint32_t)cfg->dma_read_buf_tsh_clr_emer <<
		DMA_THRESH_READ_INT_BUF_SHIFT) |
		((uint32_t)cfg->dma_write_buf_tsh_clr_emer);

	iowrite32be(tmp_reg, &dma_rg->fmdmhy);

	/* configure emergency threshold */
	iowrite32be(cfg->dma_sos_emergency, &dma_rg->fmdmsetr);

	/* configure Watchdog */
	iowrite32be((cfg->dma_watchdog * cfg->clk_freq),
			&dma_rg->fmdmwcr);

	iowrite32be(cfg->cam_base_addr, &dma_rg->fmdmebcr);

	return 0;
}