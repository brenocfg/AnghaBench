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
typedef  int uint32_t ;
struct fman_port_rx_bmi_regs {int /*<<< orphan*/  fmbm_rpc; int /*<<< orphan*/  fmbm_rstc; int /*<<< orphan*/  fmbm_rfsem; int /*<<< orphan*/  fmbm_rfsdm; int /*<<< orphan*/  fmbm_refqid; int /*<<< orphan*/  fmbm_rfqid; int /*<<< orphan*/  fmbm_rfene; int /*<<< orphan*/  fmbm_rfne; int /*<<< orphan*/  fmbm_rfca; int /*<<< orphan*/  fmbm_rebm; int /*<<< orphan*/  fmbm_rim; int /*<<< orphan*/  fmbm_ricp; int /*<<< orphan*/  fmbm_rfed; int /*<<< orphan*/  fmbm_reth; int /*<<< orphan*/  fmbm_rfp; int /*<<< orphan*/  fmbm_rda; int /*<<< orphan*/  fmbm_rcfg; } ;
struct fman_port_params {int dflt_fqid; int err_fqid; int discard_mask; int err_mask; } ;
struct fman_port_cfg {int rx_pri_elevation; int rx_fifo_thr; int ic_size; scalar_t__ perf_counters_enable; int /*<<< orphan*/  perf_cnt_params; scalar_t__ stats_counters_enable; scalar_t__ rx_fd_bits; scalar_t__ sync_req; scalar_t__ color; scalar_t__ no_scatter_gather; scalar_t__ fmbm_rebm_has_sgd; scalar_t__ ext_buf_end_margin; scalar_t__ ext_buf_start_margin; scalar_t__ int_buf_start_margin; scalar_t__ ic_int_offset; scalar_t__ ic_ext_offset; scalar_t__ errata_A006320; scalar_t__ rx_cut_end_bytes; scalar_t__ checksum_bytes_ignore; scalar_t__ excessive_threshold_register; scalar_t__ dma_write_optimize; scalar_t__ dma_sg_stash_on; scalar_t__ dma_header_stash_on; scalar_t__ dma_ic_stash_on; scalar_t__ dma_swap_data; scalar_t__ discard_override; } ;
struct fman_port {scalar_t__ im_en; TYPE_1__* bmi_regs; } ;
struct TYPE_2__ {struct fman_port_rx_bmi_regs rx; } ;

/* Variables and functions */
 int BMI_CMD_ATTR_COLOR_SHIFT ; 
 int BMI_CMD_ATTR_ORDER ; 
 int BMI_CMD_ATTR_SYNC ; 
 int BMI_CMD_RX_MR_DEF ; 
 int BMI_COUNTERS_EN ; 
 int BMI_DMA_ATTR_HDR_STASH_ON ; 
 int BMI_DMA_ATTR_IC_STASH_ON ; 
 int BMI_DMA_ATTR_SG_STASH_ON ; 
 int BMI_DMA_ATTR_SWP_SHIFT ; 
 int BMI_DMA_ATTR_WRITE_OPTIMIZE ; 
 int BMI_EXT_BUF_MARG_START_SHIFT ; 
 int BMI_IC_FROM_INT_SHIFT ; 
 int BMI_IC_TO_EXT_SHIFT ; 
 int BMI_INT_BUF_MARG_SHIFT ; 
 int BMI_NEXT_ENG_FD_BITS_SHIFT ; 
 int BMI_PORT_CFG_FDOVR ; 
 int BMI_PORT_CFG_IM ; 
 int BMI_RX_FIFO_PRI_ELEVATION_SHIFT ; 
 int BMI_RX_FIFO_THRESHOLD_ETHE ; 
 int BMI_RX_FRAME_END_CS_IGNORE_SHIFT ; 
 int BMI_RX_FRAME_END_CUT_SHIFT ; 
 int BMI_SG_DISABLE ; 
 int FMAN_PORT_BMI_FIFO_UNITS ; 
 int FMAN_PORT_IC_OFFSET_UNITS ; 
 int NIA_ENG_FM_CTL ; 
 int NIA_ENG_QMI_ENQ ; 
 int NIA_FM_CTL_AC_IND_MODE_RX ; 
 int NIA_ORDER_RESTOR ; 
 int /*<<< orphan*/  fman_port_set_perf_cnt_params (struct fman_port*,int /*<<< orphan*/ *) ; 
 int get_no_pcd_nia_bmi_ac_enc_frame (struct fman_port_cfg*) ; 
 int /*<<< orphan*/  iowrite32be (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int init_bmi_rx(struct fman_port *port,
        struct fman_port_cfg *cfg,
        struct fman_port_params *params)
{
    struct fman_port_rx_bmi_regs *regs = &port->bmi_regs->rx;
    uint32_t tmp;

    /* Rx Configuration register */
    tmp = 0;
    if (port->im_en)
        tmp |= BMI_PORT_CFG_IM;
    else if (cfg->discard_override)
        tmp |= BMI_PORT_CFG_FDOVR;
    iowrite32be(tmp, &regs->fmbm_rcfg);

    /* DMA attributes */
    tmp = (uint32_t)cfg->dma_swap_data << BMI_DMA_ATTR_SWP_SHIFT;
    if (cfg->dma_ic_stash_on)
        tmp |= BMI_DMA_ATTR_IC_STASH_ON;
    if (cfg->dma_header_stash_on)
        tmp |= BMI_DMA_ATTR_HDR_STASH_ON;
    if (cfg->dma_sg_stash_on)
        tmp |= BMI_DMA_ATTR_SG_STASH_ON;
    if (cfg->dma_write_optimize)
        tmp |= BMI_DMA_ATTR_WRITE_OPTIMIZE;
    iowrite32be(tmp, &regs->fmbm_rda);

    /* Rx FIFO parameters */
    tmp = (cfg->rx_pri_elevation / FMAN_PORT_BMI_FIFO_UNITS - 1) <<
            BMI_RX_FIFO_PRI_ELEVATION_SHIFT;
    tmp |= cfg->rx_fifo_thr / FMAN_PORT_BMI_FIFO_UNITS - 1;
    iowrite32be(tmp, &regs->fmbm_rfp);

    if (cfg->excessive_threshold_register)
        /* always allow access to the extra resources */
        iowrite32be(BMI_RX_FIFO_THRESHOLD_ETHE, &regs->fmbm_reth);

    /* Frame end data */
    tmp = (uint32_t)cfg->checksum_bytes_ignore <<
            BMI_RX_FRAME_END_CS_IGNORE_SHIFT;
    tmp |= (uint32_t)cfg->rx_cut_end_bytes <<
            BMI_RX_FRAME_END_CUT_SHIFT;
    if (cfg->errata_A006320)
        tmp &= 0xffe0ffff;
    iowrite32be(tmp, &regs->fmbm_rfed);

    /* Internal context parameters */
    tmp = ((uint32_t)cfg->ic_ext_offset / FMAN_PORT_IC_OFFSET_UNITS) <<
            BMI_IC_TO_EXT_SHIFT;
    tmp |= ((uint32_t)cfg->ic_int_offset / FMAN_PORT_IC_OFFSET_UNITS) <<
            BMI_IC_FROM_INT_SHIFT;
    tmp |= cfg->ic_size / FMAN_PORT_IC_OFFSET_UNITS;
    iowrite32be(tmp, &regs->fmbm_ricp);

    /* Internal buffer offset */
    tmp = ((uint32_t)cfg->int_buf_start_margin / FMAN_PORT_IC_OFFSET_UNITS)
            << BMI_INT_BUF_MARG_SHIFT;
    iowrite32be(tmp, &regs->fmbm_rim);

    /* External buffer margins */
    if (!port->im_en)
    {
        tmp = (uint32_t)cfg->ext_buf_start_margin <<
                BMI_EXT_BUF_MARG_START_SHIFT;
        tmp |= (uint32_t)cfg->ext_buf_end_margin;
        if (cfg->fmbm_rebm_has_sgd && cfg->no_scatter_gather)
            tmp |= BMI_SG_DISABLE;
        iowrite32be(tmp, &regs->fmbm_rebm);
    }

    /* Frame attributes */
    tmp = BMI_CMD_RX_MR_DEF;
    if (!port->im_en)
    {
        tmp |= BMI_CMD_ATTR_ORDER;
        tmp |= (uint32_t)cfg->color << BMI_CMD_ATTR_COLOR_SHIFT;
        if (cfg->sync_req)
            tmp |= BMI_CMD_ATTR_SYNC;
    }
    iowrite32be(tmp, &regs->fmbm_rfca);

    /* NIA */
    if (port->im_en)
        tmp = NIA_ENG_FM_CTL | NIA_FM_CTL_AC_IND_MODE_RX;
    else
    {
        tmp = (uint32_t)cfg->rx_fd_bits << BMI_NEXT_ENG_FD_BITS_SHIFT;
        tmp |= get_no_pcd_nia_bmi_ac_enc_frame(cfg);
    }
    iowrite32be(tmp, &regs->fmbm_rfne);

    /* Enqueue NIA */
    iowrite32be(NIA_ENG_QMI_ENQ | NIA_ORDER_RESTOR, &regs->fmbm_rfene);

    /* Default/error queues */
    if (!port->im_en)
    {
        iowrite32be((params->dflt_fqid & 0x00FFFFFF), &regs->fmbm_rfqid);
        iowrite32be((params->err_fqid & 0x00FFFFFF), &regs->fmbm_refqid);
    }

    /* Discard/error masks */
    iowrite32be(params->discard_mask, &regs->fmbm_rfsdm);
    iowrite32be(params->err_mask, &regs->fmbm_rfsem);

    /* Statistics counters */
    tmp = 0;
    if (cfg->stats_counters_enable)
        tmp = BMI_COUNTERS_EN;
    iowrite32be(tmp, &regs->fmbm_rstc);

    /* Performance counters */
    fman_port_set_perf_cnt_params(port, &cfg->perf_cnt_params);
    tmp = 0;
    if (cfg->perf_counters_enable)
        tmp = BMI_COUNTERS_EN;
    iowrite32be(tmp, &regs->fmbm_rpc);

    return 0;
}