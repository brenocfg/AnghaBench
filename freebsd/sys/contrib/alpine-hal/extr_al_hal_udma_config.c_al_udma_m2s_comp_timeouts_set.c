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
struct al_udma_m2s_comp_timeouts {scalar_t__ sch_mode; scalar_t__ enable_q_promotion; int comp_fifo_depth; int unack_fifo_depth; int coal_timeout; int app_timeout; } ;
struct al_udma {TYPE_3__* udma_regs; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int /*<<< orphan*/  cfg_application_ack; int /*<<< orphan*/  cfg_coal; int /*<<< orphan*/  cfg_1c; } ;
struct TYPE_5__ {TYPE_1__ m2s_comp; } ;
struct TYPE_6__ {TYPE_2__ m2s; } ;

/* Variables and functions */
 scalar_t__ AL_TRUE ; 
 int EINVAL ; 
 scalar_t__ SRR ; 
 scalar_t__ STRICT ; 
 int UDMA_M2S_COMP_CFG_1C_COMP_FIFO_DEPTH_MASK ; 
 int UDMA_M2S_COMP_CFG_1C_COMP_FIFO_DEPTH_SHIFT ; 
 int UDMA_M2S_COMP_CFG_1C_FORCE_RR ; 
 int UDMA_M2S_COMP_CFG_1C_Q_PROMOTION ; 
 int UDMA_M2S_COMP_CFG_1C_UNACK_FIFO_DEPTH_MASK ; 
 int UDMA_M2S_COMP_CFG_1C_UNACK_FIFO_DEPTH_SHIFT ; 
 int UDMA_M2S_COMP_CFG_APPLICATION_ACK_TOUT_MASK ; 
 int UDMA_M2S_COMP_CFG_APPLICATION_ACK_TOUT_SHIFT ; 
 int /*<<< orphan*/  al_err (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int al_reg_read32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  al_reg_write32 (int /*<<< orphan*/ *,int) ; 

int al_udma_m2s_comp_timeouts_set(struct al_udma *udma,
				struct al_udma_m2s_comp_timeouts *conf)
{
	uint32_t reg = al_reg_read32(&udma->udma_regs->m2s.m2s_comp.cfg_1c);

	if (conf->sch_mode == SRR)
		reg |= UDMA_M2S_COMP_CFG_1C_FORCE_RR;
	else if (conf->sch_mode == STRICT)
		reg &= ~UDMA_M2S_COMP_CFG_1C_FORCE_RR;
	else {
		al_err("udma [%s]: requested completion descriptor preferch "
				"arbiter mode (%d) is invalid\n",
				udma->name, conf->sch_mode);
		return -EINVAL;
	}
	if (conf->enable_q_promotion == AL_TRUE)
		reg |= UDMA_M2S_COMP_CFG_1C_Q_PROMOTION;
	else
		reg &= ~UDMA_M2S_COMP_CFG_1C_Q_PROMOTION;
	reg &= ~UDMA_M2S_COMP_CFG_1C_COMP_FIFO_DEPTH_MASK;
	reg |=
	    conf->comp_fifo_depth << UDMA_M2S_COMP_CFG_1C_COMP_FIFO_DEPTH_SHIFT;

	reg &= ~UDMA_M2S_COMP_CFG_1C_UNACK_FIFO_DEPTH_MASK;
	reg |= conf->unack_fifo_depth
				<< UDMA_M2S_COMP_CFG_1C_UNACK_FIFO_DEPTH_SHIFT;
	al_reg_write32(&udma->udma_regs->m2s.m2s_comp.cfg_1c, reg);

	al_reg_write32(&udma->udma_regs->m2s.m2s_comp.cfg_coal
							, conf->coal_timeout);

	reg = al_reg_read32(&udma->udma_regs->m2s.m2s_comp.cfg_application_ack);
	reg &= ~UDMA_M2S_COMP_CFG_APPLICATION_ACK_TOUT_MASK;
	reg |= conf->app_timeout << UDMA_M2S_COMP_CFG_APPLICATION_ACK_TOUT_SHIFT;
	al_reg_write32(&udma->udma_regs->m2s.m2s_comp.cfg_application_ack, reg);
	return 0;
}