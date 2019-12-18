#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct al_udma_q {int flags; int cdesc_size; TYPE_7__* udma; TYPE_3__* q_regs; } ;
struct TYPE_14__ {scalar_t__ type; TYPE_6__* udma_regs; } ;
struct TYPE_11__ {int cfg_1c; } ;
struct TYPE_12__ {TYPE_4__ s2m_comp; } ;
struct TYPE_13__ {TYPE_5__ s2m; } ;
struct TYPE_9__ {int comp_cfg; } ;
struct TYPE_8__ {int comp_cfg; } ;
struct TYPE_10__ {TYPE_2__ s2m_q; TYPE_1__ m2s_q; } ;

/* Variables and functions */
 int AL_UDMA_Q_FLAGS_EN_COMP_COAL ; 
 int AL_UDMA_Q_FLAGS_NO_COMP_UPDATE ; 
 int UDMA_M2S_Q_COMP_CFG_DIS_COMP_COAL ; 
 int UDMA_M2S_Q_COMP_CFG_EN_COMP_RING_UPDATE ; 
 scalar_t__ UDMA_RX ; 
 int UDMA_S2M_COMP_CFG_1C_DESC_SIZE_MASK ; 
 scalar_t__ UDMA_TX ; 
 int al_reg_read32 (int*) ; 
 int /*<<< orphan*/  al_reg_write32 (int*,int) ; 

__attribute__((used)) static int al_udma_q_config_compl(struct al_udma_q *udma_q)
{
	uint32_t *reg_addr;
	uint32_t val;

	if (udma_q->udma->type == UDMA_TX)
		reg_addr = &udma_q->q_regs->m2s_q.comp_cfg;
	else
		reg_addr = &udma_q->q_regs->s2m_q.comp_cfg;

	val = al_reg_read32(reg_addr);

	if (udma_q->flags & AL_UDMA_Q_FLAGS_NO_COMP_UPDATE)
		val &= ~UDMA_M2S_Q_COMP_CFG_EN_COMP_RING_UPDATE;
	else
		val |= UDMA_M2S_Q_COMP_CFG_EN_COMP_RING_UPDATE;

	if (udma_q->flags & AL_UDMA_Q_FLAGS_EN_COMP_COAL)
		val &= ~UDMA_M2S_Q_COMP_CFG_DIS_COMP_COAL;
	else
		val |= UDMA_M2S_Q_COMP_CFG_DIS_COMP_COAL;

	al_reg_write32(reg_addr, val);

	/* set the completion queue size */
	if (udma_q->udma->type == UDMA_RX) {
		val = al_reg_read32(
				&udma_q->udma->udma_regs->s2m.s2m_comp.cfg_1c);
		val &= ~UDMA_S2M_COMP_CFG_1C_DESC_SIZE_MASK;
		/* the register expects it to be in words */
		val |= (udma_q->cdesc_size >> 2)
				& UDMA_S2M_COMP_CFG_1C_DESC_SIZE_MASK;
		al_reg_write32(&udma_q->udma->udma_regs->s2m.s2m_comp.cfg_1c
							, val);
	}
	return 0;
}