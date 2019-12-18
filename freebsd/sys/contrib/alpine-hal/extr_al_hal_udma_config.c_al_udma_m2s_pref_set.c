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
typedef  int uint32_t ;
struct al_udma_m2s_desc_pref_conf {int desc_fifo_depth; scalar_t__ sch_mode; int max_desc_per_packet; int min_burst_below_thr; int min_burst_above_thr; int pref_thr; int data_fifo_depth; int max_pkt_limit; } ;
struct al_udma {TYPE_3__* udma_regs; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int /*<<< orphan*/  data_cfg; int /*<<< orphan*/  desc_pref_cfg_3; int /*<<< orphan*/  desc_pref_cfg_2; int /*<<< orphan*/  desc_pref_cfg_1; } ;
struct TYPE_5__ {TYPE_1__ m2s_rd; } ;
struct TYPE_6__ {TYPE_2__ m2s; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ SRR ; 
 scalar_t__ STRICT ; 
 int UDMA_M2S_RD_DATA_CFG_DATA_FIFO_DEPTH_MASK ; 
 int UDMA_M2S_RD_DATA_CFG_MAX_PKT_LIMIT_MASK ; 
 int UDMA_M2S_RD_DATA_CFG_MAX_PKT_LIMIT_SHIFT ; 
 int UDMA_M2S_RD_DESC_PREF_CFG_1_FIFO_DEPTH_MASK ; 
 int UDMA_M2S_RD_DESC_PREF_CFG_2_MAX_DESC_PER_PKT_MASK ; 
 int UDMA_M2S_RD_DESC_PREF_CFG_2_PREF_FORCE_RR ; 
 int UDMA_M2S_RD_DESC_PREF_CFG_3_MIN_BURST_ABOVE_THR_MASK ; 
 int UDMA_M2S_RD_DESC_PREF_CFG_3_MIN_BURST_ABOVE_THR_SHIFT ; 
 int UDMA_M2S_RD_DESC_PREF_CFG_3_MIN_BURST_BELOW_THR_MASK ; 
 int UDMA_M2S_RD_DESC_PREF_CFG_3_PREF_THR_MASK ; 
 int UDMA_M2S_RD_DESC_PREF_CFG_3_PREF_THR_SHIFT ; 
 int /*<<< orphan*/  al_err (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int al_reg_read32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  al_reg_write32 (int /*<<< orphan*/ *,int) ; 

int al_udma_m2s_pref_set(struct al_udma *udma,
				struct al_udma_m2s_desc_pref_conf *conf)
{
	uint32_t reg;

	reg = al_reg_read32(&udma->udma_regs->m2s.m2s_rd.desc_pref_cfg_1);
	reg &= ~UDMA_M2S_RD_DESC_PREF_CFG_1_FIFO_DEPTH_MASK;
	reg |= conf->desc_fifo_depth;
	al_reg_write32(&udma->udma_regs->m2s.m2s_rd.desc_pref_cfg_1, reg);

	reg = al_reg_read32(&udma->udma_regs->m2s.m2s_rd.desc_pref_cfg_2);

	if (conf->sch_mode == SRR)
		reg |= UDMA_M2S_RD_DESC_PREF_CFG_2_PREF_FORCE_RR;
	else if (conf->sch_mode == STRICT)
		reg &= ~UDMA_M2S_RD_DESC_PREF_CFG_2_PREF_FORCE_RR;
	else {
		al_err("udma [%s]: requested descriptor preferch arbiter "
			"mode (%d) is invalid\n", udma->name, conf->sch_mode);
		return -EINVAL;
	}
	reg &= ~UDMA_M2S_RD_DESC_PREF_CFG_2_MAX_DESC_PER_PKT_MASK;
	reg |= conf->max_desc_per_packet &
		UDMA_M2S_RD_DESC_PREF_CFG_2_MAX_DESC_PER_PKT_MASK;
	al_reg_write32(&udma->udma_regs->m2s.m2s_rd.desc_pref_cfg_2, reg);

	reg = al_reg_read32(&udma->udma_regs->m2s.m2s_rd.desc_pref_cfg_3);
	reg &= ~UDMA_M2S_RD_DESC_PREF_CFG_3_MIN_BURST_BELOW_THR_MASK;
	reg |= conf->min_burst_below_thr &
		UDMA_M2S_RD_DESC_PREF_CFG_3_MIN_BURST_BELOW_THR_MASK;

	reg &= ~UDMA_M2S_RD_DESC_PREF_CFG_3_MIN_BURST_ABOVE_THR_MASK;
	reg |=(conf->min_burst_above_thr <<
	       UDMA_M2S_RD_DESC_PREF_CFG_3_MIN_BURST_ABOVE_THR_SHIFT) &
		UDMA_M2S_RD_DESC_PREF_CFG_3_MIN_BURST_ABOVE_THR_MASK;

	reg &= ~UDMA_M2S_RD_DESC_PREF_CFG_3_PREF_THR_MASK;
	reg |= (conf->pref_thr <<
			UDMA_M2S_RD_DESC_PREF_CFG_3_PREF_THR_SHIFT) &
		UDMA_M2S_RD_DESC_PREF_CFG_3_PREF_THR_MASK;

	al_reg_write32(&udma->udma_regs->m2s.m2s_rd.desc_pref_cfg_3, reg);

	reg = al_reg_read32(&udma->udma_regs->m2s.m2s_rd.data_cfg);
	reg &= ~UDMA_M2S_RD_DATA_CFG_DATA_FIFO_DEPTH_MASK;
	reg |= conf->data_fifo_depth &
			UDMA_M2S_RD_DATA_CFG_DATA_FIFO_DEPTH_MASK;

	reg &= ~UDMA_M2S_RD_DATA_CFG_MAX_PKT_LIMIT_MASK;
	reg |= (conf->max_pkt_limit
			<< UDMA_M2S_RD_DATA_CFG_MAX_PKT_LIMIT_SHIFT) &
		UDMA_M2S_RD_DATA_CFG_MAX_PKT_LIMIT_MASK;
	al_reg_write32(&udma->udma_regs->m2s.m2s_rd.data_cfg, reg);

	return 0;
}