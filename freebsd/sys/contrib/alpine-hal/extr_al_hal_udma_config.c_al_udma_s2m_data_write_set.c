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
struct al_udma_s2m_data_write_conf {int data_fifo_depth; int max_pkt_limit; int fifo_margin; int desc_wait_timer; int flags; } ;
struct al_udma {TYPE_3__* udma_regs; } ;
struct TYPE_4__ {int /*<<< orphan*/  data_cfg_2; int /*<<< orphan*/  data_cfg_1; } ;
struct TYPE_5__ {TYPE_1__ s2m_wr; } ;
struct TYPE_6__ {TYPE_2__ s2m; } ;

/* Variables and functions */
 int UDMA_S2M_WR_DATA_CFG_1_DATA_FIFO_DEPTH_MASK ; 
 int UDMA_S2M_WR_DATA_CFG_1_FIFO_MARGIN_MASK ; 
 int UDMA_S2M_WR_DATA_CFG_1_FIFO_MARGIN_SHIFT ; 
 int UDMA_S2M_WR_DATA_CFG_1_MAX_PKT_LIMIT_MASK ; 
 int UDMA_S2M_WR_DATA_CFG_1_MAX_PKT_LIMIT_SHIFT ; 
 int UDMA_S2M_WR_DATA_CFG_2_DESC_WAIT_TIMER_MASK ; 
 int UDMA_S2M_WR_DATA_CFG_2_DIRECT_HDR_USE_BUF1 ; 
 int UDMA_S2M_WR_DATA_CFG_2_DROP_IF_NO_DESC ; 
 int UDMA_S2M_WR_DATA_CFG_2_FULL_LINE_MODE ; 
 int UDMA_S2M_WR_DATA_CFG_2_HINT_IF_NO_DESC ; 
 int UDMA_S2M_WR_DATA_CFG_2_WAIT_FOR_PREF ; 
 int al_reg_read32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  al_reg_write32 (int /*<<< orphan*/ *,int) ; 

int al_udma_s2m_data_write_set(struct al_udma *udma,
				struct al_udma_s2m_data_write_conf *conf)
{
	uint32_t reg;

	reg = al_reg_read32(&udma->udma_regs->s2m.s2m_wr.data_cfg_1);
	reg &= ~UDMA_S2M_WR_DATA_CFG_1_DATA_FIFO_DEPTH_MASK;
	reg |= conf->data_fifo_depth &
			UDMA_S2M_WR_DATA_CFG_1_DATA_FIFO_DEPTH_MASK;
	reg &= ~UDMA_S2M_WR_DATA_CFG_1_MAX_PKT_LIMIT_MASK;
	reg |= (conf->max_pkt_limit <<
				UDMA_S2M_WR_DATA_CFG_1_MAX_PKT_LIMIT_SHIFT) &
			UDMA_S2M_WR_DATA_CFG_1_MAX_PKT_LIMIT_MASK;
	reg &= ~UDMA_S2M_WR_DATA_CFG_1_FIFO_MARGIN_MASK;
	reg |= (conf->fifo_margin <<
				UDMA_S2M_WR_DATA_CFG_1_FIFO_MARGIN_SHIFT) &
			UDMA_S2M_WR_DATA_CFG_1_FIFO_MARGIN_MASK;
	al_reg_write32(&udma->udma_regs->s2m.s2m_wr.data_cfg_1, reg);

	reg = al_reg_read32(&udma->udma_regs->s2m.s2m_wr.data_cfg_2);
	reg &= ~UDMA_S2M_WR_DATA_CFG_2_DESC_WAIT_TIMER_MASK;
	reg |= conf->desc_wait_timer &
			UDMA_S2M_WR_DATA_CFG_2_DESC_WAIT_TIMER_MASK;
	reg &= ~(UDMA_S2M_WR_DATA_CFG_2_DROP_IF_NO_DESC |
		 UDMA_S2M_WR_DATA_CFG_2_HINT_IF_NO_DESC |
		 UDMA_S2M_WR_DATA_CFG_2_WAIT_FOR_PREF |
		 UDMA_S2M_WR_DATA_CFG_2_FULL_LINE_MODE |
		 UDMA_S2M_WR_DATA_CFG_2_DIRECT_HDR_USE_BUF1);
	reg |= conf->flags &
		(UDMA_S2M_WR_DATA_CFG_2_DROP_IF_NO_DESC |
		 UDMA_S2M_WR_DATA_CFG_2_HINT_IF_NO_DESC |
		 UDMA_S2M_WR_DATA_CFG_2_WAIT_FOR_PREF |
		 UDMA_S2M_WR_DATA_CFG_2_FULL_LINE_MODE |
		 UDMA_S2M_WR_DATA_CFG_2_DIRECT_HDR_USE_BUF1);
	al_reg_write32(&udma->udma_regs->s2m.s2m_wr.data_cfg_2, reg);

	return 0;
}