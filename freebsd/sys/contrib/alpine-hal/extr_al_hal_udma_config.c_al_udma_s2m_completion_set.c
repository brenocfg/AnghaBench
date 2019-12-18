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
struct al_udma_s2m_completion_conf {int desc_size; scalar_t__ cnt_words; scalar_t__ q_promotion; scalar_t__ force_rr; int q_free_min; int comp_fifo_depth; int unack_fifo_depth; int timeout; } ;
struct al_udma {TYPE_3__* udma_regs; } ;
struct TYPE_4__ {int /*<<< orphan*/  cfg_application_ack; int /*<<< orphan*/  cfg_2c; int /*<<< orphan*/  cfg_1c; } ;
struct TYPE_5__ {TYPE_1__ s2m_comp; } ;
struct TYPE_6__ {TYPE_2__ s2m; } ;

/* Variables and functions */
 scalar_t__ AL_TRUE ; 
 int UDMA_S2M_COMP_CFG_1C_CNT_WORDS ; 
 int UDMA_S2M_COMP_CFG_1C_DESC_SIZE_MASK ; 
 int UDMA_S2M_COMP_CFG_1C_FORCE_RR ; 
 int UDMA_S2M_COMP_CFG_1C_Q_FREE_MIN_MASK ; 
 int UDMA_S2M_COMP_CFG_1C_Q_FREE_MIN_SHIFT ; 
 int UDMA_S2M_COMP_CFG_1C_Q_PROMOTION ; 
 int UDMA_S2M_COMP_CFG_2C_COMP_FIFO_DEPTH_MASK ; 
 int UDMA_S2M_COMP_CFG_2C_UNACK_FIFO_DEPTH_MASK ; 
 int UDMA_S2M_COMP_CFG_2C_UNACK_FIFO_DEPTH_SHIFT ; 
 int al_reg_read32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  al_reg_write32 (int /*<<< orphan*/ *,int) ; 

int al_udma_s2m_completion_set(struct al_udma *udma,
				struct al_udma_s2m_completion_conf *conf)
{
	uint32_t reg = al_reg_read32(&udma->udma_regs->s2m.s2m_comp.cfg_1c);
	reg &= ~UDMA_S2M_COMP_CFG_1C_DESC_SIZE_MASK;
	reg |= conf->desc_size & UDMA_S2M_COMP_CFG_1C_DESC_SIZE_MASK;
	if (conf->cnt_words == AL_TRUE)
		reg |= UDMA_S2M_COMP_CFG_1C_CNT_WORDS;
	else
		reg &= ~UDMA_S2M_COMP_CFG_1C_CNT_WORDS;
	if (conf->q_promotion == AL_TRUE)
		reg |= UDMA_S2M_COMP_CFG_1C_Q_PROMOTION;
	else
		reg &= ~UDMA_S2M_COMP_CFG_1C_Q_PROMOTION;
	if (conf->force_rr == AL_TRUE)
		reg |= UDMA_S2M_COMP_CFG_1C_FORCE_RR;
	else
		reg &= ~UDMA_S2M_COMP_CFG_1C_FORCE_RR;
	reg &= ~UDMA_S2M_COMP_CFG_1C_Q_FREE_MIN_MASK;
	reg |= (conf->q_free_min << UDMA_S2M_COMP_CFG_1C_Q_FREE_MIN_SHIFT) &
		UDMA_S2M_COMP_CFG_1C_Q_FREE_MIN_MASK;
	al_reg_write32(&udma->udma_regs->s2m.s2m_comp.cfg_1c, reg);

	reg = al_reg_read32(&udma->udma_regs->s2m.s2m_comp.cfg_2c);
	reg &= ~UDMA_S2M_COMP_CFG_2C_COMP_FIFO_DEPTH_MASK;
	reg |= conf->comp_fifo_depth
				& UDMA_S2M_COMP_CFG_2C_COMP_FIFO_DEPTH_MASK;
	reg &= ~UDMA_S2M_COMP_CFG_2C_UNACK_FIFO_DEPTH_MASK;
	reg |= (conf->unack_fifo_depth
			<< UDMA_S2M_COMP_CFG_2C_UNACK_FIFO_DEPTH_SHIFT) &
			UDMA_S2M_COMP_CFG_2C_UNACK_FIFO_DEPTH_MASK;
	al_reg_write32(&udma->udma_regs->s2m.s2m_comp.cfg_2c, reg);

	al_reg_write32(&udma->udma_regs->s2m.s2m_comp.cfg_application_ack,
		       conf->timeout);
	return 0;
}