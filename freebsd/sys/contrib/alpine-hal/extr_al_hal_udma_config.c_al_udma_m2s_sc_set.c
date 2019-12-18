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
struct al_udma_m2s_dwrr_conf {scalar_t__ enable_dwrr; scalar_t__ pkt_mode; int weight; int inc_factor; int deficit_init_val; } ;
struct al_udma {TYPE_3__* udma_regs; } ;
struct TYPE_4__ {int /*<<< orphan*/  ctrl_deficit_cnt; int /*<<< orphan*/  cfg_sched; } ;
struct TYPE_5__ {TYPE_1__ m2s_dwrr; } ;
struct TYPE_6__ {TYPE_2__ m2s; } ;

/* Variables and functions */
 scalar_t__ AL_TRUE ; 
 int UDMA_M2S_DWRR_CFG_SCHED_EN_DWRR ; 
 int UDMA_M2S_DWRR_CFG_SCHED_INC_FACTOR_MASK ; 
 int UDMA_M2S_DWRR_CFG_SCHED_INC_FACTOR_SHIFT ; 
 int UDMA_M2S_DWRR_CFG_SCHED_PKT_MODE_EN ; 
 int UDMA_M2S_DWRR_CFG_SCHED_WEIGHT_INC_MASK ; 
 int UDMA_M2S_DWRR_CFG_SCHED_WEIGHT_INC_SHIFT ; 
 int UDMA_M2S_DWRR_CTRL_DEFICIT_CNT_INIT_MASK ; 
 int al_reg_read32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  al_reg_write32 (int /*<<< orphan*/ *,int) ; 

int al_udma_m2s_sc_set(struct al_udma *udma,
					struct al_udma_m2s_dwrr_conf *sched)
{
	uint32_t reg = al_reg_read32(&udma->udma_regs->m2s.m2s_dwrr.cfg_sched);

	if (sched->enable_dwrr == AL_TRUE)
		reg |= UDMA_M2S_DWRR_CFG_SCHED_EN_DWRR;
	else
		reg &= ~UDMA_M2S_DWRR_CFG_SCHED_EN_DWRR;

	if (sched->pkt_mode == AL_TRUE)
		reg |= UDMA_M2S_DWRR_CFG_SCHED_PKT_MODE_EN;
	else
		reg &= ~UDMA_M2S_DWRR_CFG_SCHED_PKT_MODE_EN;

	reg &= ~UDMA_M2S_DWRR_CFG_SCHED_WEIGHT_INC_MASK;
	reg |= sched->weight << UDMA_M2S_DWRR_CFG_SCHED_WEIGHT_INC_SHIFT;
	reg &= ~UDMA_M2S_DWRR_CFG_SCHED_INC_FACTOR_MASK;
	reg |= sched->inc_factor << UDMA_M2S_DWRR_CFG_SCHED_INC_FACTOR_SHIFT;
	al_reg_write32(&udma->udma_regs->m2s.m2s_dwrr.cfg_sched, reg);

	reg = al_reg_read32(&udma->udma_regs->m2s.m2s_dwrr.ctrl_deficit_cnt);
	reg &= ~UDMA_M2S_DWRR_CTRL_DEFICIT_CNT_INIT_MASK;
	reg |= sched->deficit_init_val;
	al_reg_write32(&udma->udma_regs->m2s.m2s_dwrr.ctrl_deficit_cnt, reg);

	return 0;
}