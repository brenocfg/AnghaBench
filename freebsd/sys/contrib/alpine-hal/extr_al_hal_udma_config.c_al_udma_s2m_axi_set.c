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
struct al_udma_s2m_axi_conf {scalar_t__ break_on_max_boundary; int min_axi_beats; int ostand_max_desc_read; int ack_fifo_depth; int ostand_max_data_req; int ostand_max_data_write; int ostand_max_comp_req; int ostand_max_comp_write; int /*<<< orphan*/  comp_write; int /*<<< orphan*/  desc_read; int /*<<< orphan*/  data_write; } ;
struct al_udma {TYPE_3__* udma_regs; } ;
struct TYPE_4__ {int /*<<< orphan*/  ostand_cfg_wr; int /*<<< orphan*/  ostand_cfg_rd; int /*<<< orphan*/  desc_wr_cfg_1; int /*<<< orphan*/  desc_rd_cfg_3; int /*<<< orphan*/  comp_wr_cfg_2; int /*<<< orphan*/  comp_wr_cfg_1; int /*<<< orphan*/  desc_rd_cfg_5; int /*<<< orphan*/  desc_rd_cfg_4; int /*<<< orphan*/  data_wr_cfg; int /*<<< orphan*/  data_wr_cfg_2; int /*<<< orphan*/  data_wr_cfg_1; } ;
struct TYPE_5__ {TYPE_1__ axi_s2m; } ;
struct TYPE_6__ {TYPE_2__ s2m; } ;

/* Variables and functions */
 scalar_t__ AL_TRUE ; 
 int UDMA_AXI_S2M_DESC_RD_CFG_3_ALWAYS_BREAK_ON_MAX_BOUDRY ; 
 int UDMA_AXI_S2M_DESC_WR_CFG_1_MIN_AXI_BEATS_MASK ; 
 int UDMA_AXI_S2M_DESC_WR_CFG_1_MIN_AXI_BEATS_SHIFT ; 
 int UDMA_AXI_S2M_OSTAND_CFG_RD_MAX_DESC_RD_OSTAND_MASK ; 
 int UDMA_AXI_S2M_OSTAND_CFG_RD_MAX_STREAM_ACK_MASK ; 
 int UDMA_AXI_S2M_OSTAND_CFG_RD_MAX_STREAM_ACK_SHIFT ; 
 int UDMA_AXI_S2M_OSTAND_CFG_WR_MAX_COMP_DATA_WR_OSTAND_MASK ; 
 int UDMA_AXI_S2M_OSTAND_CFG_WR_MAX_COMP_DATA_WR_OSTAND_SHIFT ; 
 int UDMA_AXI_S2M_OSTAND_CFG_WR_MAX_COMP_REQ_MASK ; 
 int UDMA_AXI_S2M_OSTAND_CFG_WR_MAX_COMP_REQ_SHIFT ; 
 int UDMA_AXI_S2M_OSTAND_CFG_WR_MAX_DATA_BEATS_WR_OSTAND_MASK ; 
 int UDMA_AXI_S2M_OSTAND_CFG_WR_MAX_DATA_BEATS_WR_OSTAND_SHIFT ; 
 int UDMA_AXI_S2M_OSTAND_CFG_WR_MAX_DATA_WR_OSTAND_MASK ; 
 int al_reg_read32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  al_reg_write32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  al_udma_s2m_axi_sm_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int al_udma_s2m_axi_set(struct al_udma *udma,
				struct al_udma_s2m_axi_conf *axi_s2m)
{

	uint32_t reg;

	al_udma_s2m_axi_sm_set(&axi_s2m->data_write,
			       &udma->udma_regs->s2m.axi_s2m.data_wr_cfg_1,
			       &udma->udma_regs->s2m.axi_s2m.data_wr_cfg_2,
			       &udma->udma_regs->s2m.axi_s2m.data_wr_cfg);

	al_udma_s2m_axi_sm_set(&axi_s2m->desc_read,
			       &udma->udma_regs->s2m.axi_s2m.desc_rd_cfg_4,
			       &udma->udma_regs->s2m.axi_s2m.desc_rd_cfg_5,
			       &udma->udma_regs->s2m.axi_s2m.desc_rd_cfg_3);

	al_udma_s2m_axi_sm_set(&axi_s2m->comp_write,
			       &udma->udma_regs->s2m.axi_s2m.comp_wr_cfg_1,
			       &udma->udma_regs->s2m.axi_s2m.comp_wr_cfg_2,
			       &udma->udma_regs->s2m.axi_s2m.desc_wr_cfg_1);

	reg = al_reg_read32(&udma->udma_regs->s2m.axi_s2m.desc_rd_cfg_3);
	if (axi_s2m->break_on_max_boundary == AL_TRUE)
		reg |= UDMA_AXI_S2M_DESC_RD_CFG_3_ALWAYS_BREAK_ON_MAX_BOUDRY;
	else
		reg &= ~UDMA_AXI_S2M_DESC_RD_CFG_3_ALWAYS_BREAK_ON_MAX_BOUDRY;
	al_reg_write32(&udma->udma_regs->s2m.axi_s2m.desc_rd_cfg_3, reg);

	reg = al_reg_read32(&udma->udma_regs->s2m.axi_s2m.desc_wr_cfg_1);
	reg &= ~UDMA_AXI_S2M_DESC_WR_CFG_1_MIN_AXI_BEATS_MASK;
	reg |= (axi_s2m->min_axi_beats <<
			UDMA_AXI_S2M_DESC_WR_CFG_1_MIN_AXI_BEATS_SHIFT) &
		UDMA_AXI_S2M_DESC_WR_CFG_1_MIN_AXI_BEATS_MASK;
	al_reg_write32(&udma->udma_regs->s2m.axi_s2m.desc_wr_cfg_1, reg);

	reg = al_reg_read32(&udma->udma_regs->s2m.axi_s2m.ostand_cfg_rd);
	reg &= ~UDMA_AXI_S2M_OSTAND_CFG_RD_MAX_DESC_RD_OSTAND_MASK;
	reg |= axi_s2m->ostand_max_desc_read &
			UDMA_AXI_S2M_OSTAND_CFG_RD_MAX_DESC_RD_OSTAND_MASK;

	reg &= ~UDMA_AXI_S2M_OSTAND_CFG_RD_MAX_STREAM_ACK_MASK;
	reg |= (axi_s2m->ack_fifo_depth <<
			UDMA_AXI_S2M_OSTAND_CFG_RD_MAX_STREAM_ACK_SHIFT) &
		UDMA_AXI_S2M_OSTAND_CFG_RD_MAX_STREAM_ACK_MASK;

	al_reg_write32(&udma->udma_regs->s2m.axi_s2m.ostand_cfg_rd, reg);

	reg = al_reg_read32(&udma->udma_regs->s2m.axi_s2m.ostand_cfg_wr);
	reg &= ~UDMA_AXI_S2M_OSTAND_CFG_WR_MAX_DATA_WR_OSTAND_MASK;
	reg |= axi_s2m->ostand_max_data_req &
			UDMA_AXI_S2M_OSTAND_CFG_WR_MAX_DATA_WR_OSTAND_MASK;
	reg &= ~UDMA_AXI_S2M_OSTAND_CFG_WR_MAX_DATA_BEATS_WR_OSTAND_MASK;
	reg |= (axi_s2m->ostand_max_data_write <<
		UDMA_AXI_S2M_OSTAND_CFG_WR_MAX_DATA_BEATS_WR_OSTAND_SHIFT) &
		UDMA_AXI_S2M_OSTAND_CFG_WR_MAX_DATA_BEATS_WR_OSTAND_MASK;
	reg &= ~UDMA_AXI_S2M_OSTAND_CFG_WR_MAX_COMP_REQ_MASK;
	reg |= (axi_s2m->ostand_max_comp_req <<
			UDMA_AXI_S2M_OSTAND_CFG_WR_MAX_COMP_REQ_SHIFT) &
		UDMA_AXI_S2M_OSTAND_CFG_WR_MAX_COMP_REQ_MASK;
	reg &= ~UDMA_AXI_S2M_OSTAND_CFG_WR_MAX_COMP_DATA_WR_OSTAND_MASK;
	reg |= (axi_s2m->ostand_max_comp_write <<
		UDMA_AXI_S2M_OSTAND_CFG_WR_MAX_COMP_DATA_WR_OSTAND_SHIFT) &
		UDMA_AXI_S2M_OSTAND_CFG_WR_MAX_COMP_DATA_WR_OSTAND_MASK;
	al_reg_write32(&udma->udma_regs->s2m.axi_s2m.ostand_cfg_wr, reg);
	return 0;
}