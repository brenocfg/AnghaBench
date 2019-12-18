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
typedef  int uint32_t ;
struct al_udma_q {TYPE_2__* q_regs; } ;
struct al_udma_m2s_q_dwrr_conf {int max_deficit_cnt_sz; scalar_t__ strict; int axi_qos; int q_qos; int weight; } ;
struct TYPE_3__ {int /*<<< orphan*/  dwrr_cfg_3; int /*<<< orphan*/  dwrr_cfg_2; int /*<<< orphan*/  dwrr_cfg_1; } ;
struct TYPE_4__ {TYPE_1__ m2s_q; } ;

/* Variables and functions */
 scalar_t__ AL_TRUE ; 
 int UDMA_M2S_Q_DWRR_CFG_1_MAX_DEFICIT_CNT_SIZE_MASK ; 
 int UDMA_M2S_Q_DWRR_CFG_1_STRICT ; 
 int UDMA_M2S_Q_DWRR_CFG_2_Q_QOS_MASK ; 
 int UDMA_M2S_Q_DWRR_CFG_2_Q_QOS_SHIFT ; 
 int UDMA_M2S_Q_DWRR_CFG_3_WEIGHT_MASK ; 
 int al_reg_read32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  al_reg_write32 (int /*<<< orphan*/ *,int) ; 

int al_udma_m2s_q_sc_set(struct al_udma_q *udma_q,
					struct al_udma_m2s_q_dwrr_conf *conf)
{
	uint32_t reg = al_reg_read32(&udma_q->q_regs->m2s_q.dwrr_cfg_1);

	reg &= ~UDMA_M2S_Q_DWRR_CFG_1_MAX_DEFICIT_CNT_SIZE_MASK;
	reg |= conf->max_deficit_cnt_sz &
		UDMA_M2S_Q_DWRR_CFG_1_MAX_DEFICIT_CNT_SIZE_MASK;
	if (conf->strict == AL_TRUE)
		reg |= UDMA_M2S_Q_DWRR_CFG_1_STRICT;
	else
		reg &= ~UDMA_M2S_Q_DWRR_CFG_1_STRICT;
	al_reg_write32(&udma_q->q_regs->m2s_q.dwrr_cfg_1, reg);

	reg = al_reg_read32(&udma_q->q_regs->m2s_q.dwrr_cfg_2);
	reg &= ~UDMA_M2S_Q_DWRR_CFG_2_Q_QOS_MASK;
	reg |= (conf->axi_qos << UDMA_M2S_Q_DWRR_CFG_2_Q_QOS_SHIFT) &
	    UDMA_M2S_Q_DWRR_CFG_2_Q_QOS_MASK;
	reg &= ~UDMA_M2S_Q_DWRR_CFG_2_Q_QOS_MASK;
	reg |= conf->q_qos & UDMA_M2S_Q_DWRR_CFG_2_Q_QOS_MASK;
	al_reg_write32(&udma_q->q_regs->m2s_q.dwrr_cfg_2, reg);

	reg = al_reg_read32(&udma_q->q_regs->m2s_q.dwrr_cfg_3);
	reg &= ~UDMA_M2S_Q_DWRR_CFG_3_WEIGHT_MASK;
	reg |= conf->weight & UDMA_M2S_Q_DWRR_CFG_3_WEIGHT_MASK;
	al_reg_write32(&udma_q->q_regs->m2s_q.dwrr_cfg_3, reg);

	return 0;
}