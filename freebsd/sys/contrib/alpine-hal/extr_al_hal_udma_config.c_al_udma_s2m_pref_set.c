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
struct al_udma_s2m_desc_pref_conf {int desc_fifo_depth; scalar_t__ sch_mode; scalar_t__ q_promotion; scalar_t__ force_promotion; scalar_t__ en_pref_prediction; int promotion_th; int pref_thr; int min_burst_below_thr; int min_burst_above_thr; int a_full_thr; } ;
struct al_udma {TYPE_3__* udma_regs; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int /*<<< orphan*/  desc_pref_cfg_4; int /*<<< orphan*/  desc_pref_cfg_3; int /*<<< orphan*/  desc_pref_cfg_2; int /*<<< orphan*/  desc_pref_cfg_1; } ;
struct TYPE_5__ {TYPE_1__ s2m_rd; } ;
struct TYPE_6__ {TYPE_2__ s2m; } ;

/* Variables and functions */
 scalar_t__ AL_TRUE ; 
 int EINVAL ; 
 scalar_t__ SRR ; 
 scalar_t__ STRICT ; 
 int UDMA_S2M_RD_DESC_PREF_CFG_1_FIFO_DEPTH_MASK ; 
 int UDMA_S2M_RD_DESC_PREF_CFG_2_EN_PREF_PREDICTION ; 
 int UDMA_S2M_RD_DESC_PREF_CFG_2_FORCE_PROMOTION ; 
 int UDMA_S2M_RD_DESC_PREF_CFG_2_PREF_FORCE_RR ; 
 int UDMA_S2M_RD_DESC_PREF_CFG_2_PROMOTION_TH_MASK ; 
 int UDMA_S2M_RD_DESC_PREF_CFG_2_PROMOTION_TH_SHIFT ; 
 int UDMA_S2M_RD_DESC_PREF_CFG_2_Q_PROMOTION ; 
 int UDMA_S2M_RD_DESC_PREF_CFG_3_MIN_BURST_ABOVE_THR_MASK ; 
 int UDMA_S2M_RD_DESC_PREF_CFG_3_MIN_BURST_ABOVE_THR_SHIFT ; 
 int UDMA_S2M_RD_DESC_PREF_CFG_3_MIN_BURST_BELOW_THR_MASK ; 
 int UDMA_S2M_RD_DESC_PREF_CFG_3_PREF_THR_MASK ; 
 int UDMA_S2M_RD_DESC_PREF_CFG_3_PREF_THR_SHIFT ; 
 int UDMA_S2M_RD_DESC_PREF_CFG_4_A_FULL_THR_MASK ; 
 int /*<<< orphan*/  al_err (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int al_reg_read32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  al_reg_write32 (int /*<<< orphan*/ *,int) ; 

int al_udma_s2m_pref_set(struct al_udma *udma,
				struct al_udma_s2m_desc_pref_conf *conf)
{
	uint32_t reg;

	reg = al_reg_read32(&udma->udma_regs->s2m.s2m_rd.desc_pref_cfg_1);
	reg &= ~UDMA_S2M_RD_DESC_PREF_CFG_1_FIFO_DEPTH_MASK;
	reg |= conf->desc_fifo_depth;
	al_reg_write32(&udma->udma_regs->s2m.s2m_rd.desc_pref_cfg_1, reg);

	reg = al_reg_read32(&udma->udma_regs->s2m.s2m_rd.desc_pref_cfg_2);

	if (conf->sch_mode == SRR)
		reg |= UDMA_S2M_RD_DESC_PREF_CFG_2_PREF_FORCE_RR;
	else if (conf->sch_mode == STRICT)
		reg &= ~UDMA_S2M_RD_DESC_PREF_CFG_2_PREF_FORCE_RR;
	else {
		al_err("udma [%s]: requested descriptor preferch arbiter "
			"mode (%d) is invalid\n", udma->name, conf->sch_mode);
		return -EINVAL;
	}
	if (conf->q_promotion == AL_TRUE)
		reg |= UDMA_S2M_RD_DESC_PREF_CFG_2_Q_PROMOTION;
	else
		reg &= ~UDMA_S2M_RD_DESC_PREF_CFG_2_Q_PROMOTION;

	if (conf->force_promotion == AL_TRUE)
		reg |= UDMA_S2M_RD_DESC_PREF_CFG_2_FORCE_PROMOTION;
	else
		reg &= ~UDMA_S2M_RD_DESC_PREF_CFG_2_FORCE_PROMOTION;

	if (conf->en_pref_prediction == AL_TRUE)
		reg |= UDMA_S2M_RD_DESC_PREF_CFG_2_EN_PREF_PREDICTION;
	else
		reg &= ~UDMA_S2M_RD_DESC_PREF_CFG_2_EN_PREF_PREDICTION;

	reg &= ~UDMA_S2M_RD_DESC_PREF_CFG_2_PROMOTION_TH_MASK;
	reg |= (conf->promotion_th
			<< UDMA_S2M_RD_DESC_PREF_CFG_2_PROMOTION_TH_SHIFT) &
		UDMA_S2M_RD_DESC_PREF_CFG_2_PROMOTION_TH_MASK;

	al_reg_write32(&udma->udma_regs->s2m.s2m_rd.desc_pref_cfg_2, reg);

	reg = al_reg_read32(&udma->udma_regs->s2m.s2m_rd.desc_pref_cfg_3);
	reg &= ~UDMA_S2M_RD_DESC_PREF_CFG_3_PREF_THR_MASK;
	reg |= (conf->pref_thr << UDMA_S2M_RD_DESC_PREF_CFG_3_PREF_THR_SHIFT) &
		UDMA_S2M_RD_DESC_PREF_CFG_3_PREF_THR_MASK;

	reg &= ~UDMA_S2M_RD_DESC_PREF_CFG_3_MIN_BURST_BELOW_THR_MASK;
	reg |= conf->min_burst_below_thr &
		UDMA_S2M_RD_DESC_PREF_CFG_3_MIN_BURST_BELOW_THR_MASK;

	reg &= ~UDMA_S2M_RD_DESC_PREF_CFG_3_MIN_BURST_ABOVE_THR_MASK;
	reg |=(conf->min_burst_above_thr <<
	       UDMA_S2M_RD_DESC_PREF_CFG_3_MIN_BURST_ABOVE_THR_SHIFT) &
		UDMA_S2M_RD_DESC_PREF_CFG_3_MIN_BURST_ABOVE_THR_MASK;

	al_reg_write32(&udma->udma_regs->s2m.s2m_rd.desc_pref_cfg_3, reg);

	reg = al_reg_read32(&udma->udma_regs->s2m.s2m_rd.desc_pref_cfg_4);
	reg &= ~UDMA_S2M_RD_DESC_PREF_CFG_4_A_FULL_THR_MASK;
	reg |= conf->a_full_thr & UDMA_S2M_RD_DESC_PREF_CFG_4_A_FULL_THR_MASK;
	al_reg_write32(&udma->udma_regs->s2m.s2m_rd.desc_pref_cfg_4, reg);


	return 0;
}