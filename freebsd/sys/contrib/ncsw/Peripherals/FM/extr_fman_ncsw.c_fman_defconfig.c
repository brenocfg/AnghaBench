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
struct fman_cfg {void* qmi_deq_option_support; void* dma_stop_on_bus_error; int /*<<< orphan*/  tnum_aging_period; void* pedantic_dma; int /*<<< orphan*/  fm_ctl2_disp_tsh; int /*<<< orphan*/  fm_ctl1_disp_tsh; int /*<<< orphan*/  qmi_deq_disp_tsh; int /*<<< orphan*/  qmi_enq_disp_tsh; int /*<<< orphan*/  bmi_disp_tsh; int /*<<< orphan*/  kg_disp_tsh; int /*<<< orphan*/  plcr_disp_tsh; int /*<<< orphan*/  prs_disp_tsh; int /*<<< orphan*/  disp_limit_tsh; int /*<<< orphan*/  dma_emergency_switch_counter; int /*<<< orphan*/  dma_en_emergency_smoother; int /*<<< orphan*/  dma_watchdog; int /*<<< orphan*/  dma_sos_emergency; int /*<<< orphan*/  dma_en_emergency; int /*<<< orphan*/  dma_dbg_cnt_mode; int /*<<< orphan*/  dma_cam_num_of_entries; int /*<<< orphan*/  dma_cache_override; int /*<<< orphan*/  dma_comm_qtsh_asrt_emer; int /*<<< orphan*/  dma_comm_qtsh_clr_emer; int /*<<< orphan*/  dma_aid_mode; int /*<<< orphan*/  dma_aid_override; int /*<<< orphan*/  external_ecc_rams_enable; void* en_muram_test_mode; void* en_iram_test_mode; int /*<<< orphan*/  halt_on_unrecov_ecc_err; int /*<<< orphan*/  halt_on_external_activ; int /*<<< orphan*/  dma_err; int /*<<< orphan*/  catastrophic_err; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_AID_MODE ; 
 int /*<<< orphan*/  DEFAULT_AID_OVERRIDE ; 
 int /*<<< orphan*/  DEFAULT_BMI_DISP_TH ; 
 int /*<<< orphan*/  DEFAULT_CACHE_OVERRIDE ; 
 int /*<<< orphan*/  DEFAULT_CATASTROPHIC_ERR ; 
 int /*<<< orphan*/  DEFAULT_DISP_LIMIT ; 
 int /*<<< orphan*/  DEFAULT_DMA_CAM_NUM_OF_ENTRIES ; 
 int /*<<< orphan*/  DEFAULT_DMA_COMM_Q_HIGH ; 
 int /*<<< orphan*/  DEFAULT_DMA_COMM_Q_LOW ; 
 int /*<<< orphan*/  DEFAULT_DMA_DBG_CNT_MODE ; 
 int /*<<< orphan*/  DEFAULT_DMA_EMERGENCY_SWITCH_COUNTER ; 
 int /*<<< orphan*/  DEFAULT_DMA_EN_EMERGENCY ; 
 int /*<<< orphan*/  DEFAULT_DMA_EN_EMERGENCY_SMOOTHER ; 
 int /*<<< orphan*/  DEFAULT_DMA_ERR ; 
 int /*<<< orphan*/  DEFAULT_DMA_SOS_EMERGENCY ; 
 int /*<<< orphan*/  DEFAULT_DMA_WATCHDOG ; 
 int /*<<< orphan*/  DEFAULT_EXTERNAL_ECC_RAMS_ENABLE ; 
 int /*<<< orphan*/  DEFAULT_FM_CTL1_DISP_TH ; 
 int /*<<< orphan*/  DEFAULT_FM_CTL2_DISP_TH ; 
 int /*<<< orphan*/  DEFAULT_HALT_ON_EXTERNAL_ACTIVATION ; 
 int /*<<< orphan*/  DEFAULT_HALT_ON_UNRECOVERABLE_ECC_ERROR ; 
 int /*<<< orphan*/  DEFAULT_KG_DISP_TH ; 
 int /*<<< orphan*/  DEFAULT_PLCR_DISP_TH ; 
 int /*<<< orphan*/  DEFAULT_PRS_DISP_TH ; 
 int /*<<< orphan*/  DEFAULT_QMI_DEQ_DISP_TH ; 
 int /*<<< orphan*/  DEFAULT_QMI_ENQ_DISP_TH ; 
 int /*<<< orphan*/  DEFAULT_TNUM_AGING_PERIOD ; 
 void* FALSE ; 
 int /*<<< orphan*/  memset (struct fman_cfg*,int /*<<< orphan*/ ,int) ; 

void fman_defconfig(struct fman_cfg *cfg, bool is_master)
{
    memset(cfg, 0, sizeof(struct fman_cfg));

    cfg->catastrophic_err               = DEFAULT_CATASTROPHIC_ERR;
    cfg->dma_err                        = DEFAULT_DMA_ERR;
    cfg->halt_on_external_activ         = DEFAULT_HALT_ON_EXTERNAL_ACTIVATION;
    cfg->halt_on_unrecov_ecc_err        = DEFAULT_HALT_ON_UNRECOVERABLE_ECC_ERROR;
    cfg->en_iram_test_mode              = FALSE;
    cfg->en_muram_test_mode             = FALSE;
    cfg->external_ecc_rams_enable       = DEFAULT_EXTERNAL_ECC_RAMS_ENABLE;

	if (!is_master)
	    return;

    cfg->dma_aid_override               = DEFAULT_AID_OVERRIDE;
    cfg->dma_aid_mode                   = DEFAULT_AID_MODE;
    cfg->dma_comm_qtsh_clr_emer         = DEFAULT_DMA_COMM_Q_LOW;
    cfg->dma_comm_qtsh_asrt_emer        = DEFAULT_DMA_COMM_Q_HIGH;
    cfg->dma_cache_override             = DEFAULT_CACHE_OVERRIDE;
    cfg->dma_cam_num_of_entries         = DEFAULT_DMA_CAM_NUM_OF_ENTRIES;
    cfg->dma_dbg_cnt_mode               = DEFAULT_DMA_DBG_CNT_MODE;
    cfg->dma_en_emergency               = DEFAULT_DMA_EN_EMERGENCY;
    cfg->dma_sos_emergency              = DEFAULT_DMA_SOS_EMERGENCY;
    cfg->dma_watchdog                   = DEFAULT_DMA_WATCHDOG;
    cfg->dma_en_emergency_smoother      = DEFAULT_DMA_EN_EMERGENCY_SMOOTHER;
    cfg->dma_emergency_switch_counter   = DEFAULT_DMA_EMERGENCY_SWITCH_COUNTER;
    cfg->disp_limit_tsh                 = DEFAULT_DISP_LIMIT;
    cfg->prs_disp_tsh                   = DEFAULT_PRS_DISP_TH;
    cfg->plcr_disp_tsh                  = DEFAULT_PLCR_DISP_TH;
    cfg->kg_disp_tsh                    = DEFAULT_KG_DISP_TH;
    cfg->bmi_disp_tsh                   = DEFAULT_BMI_DISP_TH;
    cfg->qmi_enq_disp_tsh               = DEFAULT_QMI_ENQ_DISP_TH;
    cfg->qmi_deq_disp_tsh               = DEFAULT_QMI_DEQ_DISP_TH;
    cfg->fm_ctl1_disp_tsh               = DEFAULT_FM_CTL1_DISP_TH;
    cfg->fm_ctl2_disp_tsh               = DEFAULT_FM_CTL2_DISP_TH;
 
	cfg->pedantic_dma                   = FALSE;
	cfg->tnum_aging_period              = DEFAULT_TNUM_AGING_PERIOD;
	cfg->dma_stop_on_bus_error          = FALSE;
	cfg->qmi_deq_option_support         = FALSE;
}