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
struct al_udma_s2m_q_comp_conf {scalar_t__ en_comp_ring_update; scalar_t__ dis_comp_coal; int comp_timer; int hdr_split_size; scalar_t__ force_hdr_split; scalar_t__ en_hdr_split; int q_qos; } ;
struct al_udma_q {TYPE_2__* q_regs; } ;
struct TYPE_3__ {int /*<<< orphan*/  qos_cfg; int /*<<< orphan*/  pkt_cfg; int /*<<< orphan*/  comp_cfg_2; int /*<<< orphan*/  comp_cfg; } ;
struct TYPE_4__ {TYPE_1__ s2m_q; } ;

/* Variables and functions */
 scalar_t__ AL_TRUE ; 
 int UDMA_S2M_QOS_CFG_Q_QOS_MASK ; 
 int UDMA_S2M_Q_COMP_CFG_DIS_COMP_COAL ; 
 int UDMA_S2M_Q_COMP_CFG_EN_COMP_RING_UPDATE ; 
 int UDMA_S2M_Q_PKT_CFG_EN_HDR_SPLIT ; 
 int UDMA_S2M_Q_PKT_CFG_FORCE_HDR_SPLIT ; 
 int UDMA_S2M_Q_PKT_CFG_HDR_SPLIT_SIZE_MASK ; 
 int al_reg_read32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  al_reg_write32 (int /*<<< orphan*/ *,int) ; 

int al_udma_s2m_q_comp_set(struct al_udma_q *udma_q,
					struct al_udma_s2m_q_comp_conf *conf)
{
	uint32_t reg = al_reg_read32(&udma_q->q_regs->s2m_q.comp_cfg);
	if (conf->en_comp_ring_update == AL_TRUE)
		reg |= UDMA_S2M_Q_COMP_CFG_EN_COMP_RING_UPDATE;
	else
		reg &= ~UDMA_S2M_Q_COMP_CFG_EN_COMP_RING_UPDATE;

	if (conf->dis_comp_coal == AL_TRUE)
		reg |= UDMA_S2M_Q_COMP_CFG_DIS_COMP_COAL;
	else
		reg &= ~UDMA_S2M_Q_COMP_CFG_DIS_COMP_COAL;

	al_reg_write32(&udma_q->q_regs->s2m_q.comp_cfg, reg);

	al_reg_write32(&udma_q->q_regs->s2m_q.comp_cfg_2, conf->comp_timer);

	reg = al_reg_read32(&udma_q->q_regs->s2m_q.pkt_cfg);

	reg &= ~UDMA_S2M_Q_PKT_CFG_HDR_SPLIT_SIZE_MASK;
	reg |= conf->hdr_split_size & UDMA_S2M_Q_PKT_CFG_HDR_SPLIT_SIZE_MASK;
	if (conf->force_hdr_split == AL_TRUE)
		reg |= UDMA_S2M_Q_PKT_CFG_FORCE_HDR_SPLIT;
	else
		reg &= ~UDMA_S2M_Q_PKT_CFG_FORCE_HDR_SPLIT;
	if (conf->en_hdr_split == AL_TRUE)
		reg |= UDMA_S2M_Q_PKT_CFG_EN_HDR_SPLIT;
	else
		reg &= ~UDMA_S2M_Q_PKT_CFG_EN_HDR_SPLIT;

	al_reg_write32(&udma_q->q_regs->s2m_q.pkt_cfg, reg);

	reg = al_reg_read32(&udma_q->q_regs->s2m_q.qos_cfg);
	reg &= ~UDMA_S2M_QOS_CFG_Q_QOS_MASK;
	reg |= conf->q_qos & UDMA_S2M_QOS_CFG_Q_QOS_MASK;
	al_reg_write32(&udma_q->q_regs->s2m_q.qos_cfg, reg);

	return 0;
}