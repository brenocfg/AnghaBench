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
typedef  int u32 ;
struct TYPE_4__ {scalar_t__ flow_ctrl; int psize; scalar_t__ big_endian; int /*<<< orphan*/  data_width; } ;
struct TYPE_3__ {scalar_t__ flow_ctrl; int psize; scalar_t__ big_endian; int /*<<< orphan*/  data_width; } ;
struct stedma40_chan_cfg {scalar_t__ dir; TYPE_2__ dst_info; TYPE_1__ src_info; scalar_t__ high_priority; int /*<<< orphan*/  dev_type; } ;

/* Variables and functions */
 int BIT (int) ; 
 int D40_SREG_CFG_EIM_POS ; 
 int D40_SREG_CFG_ESIZE_POS ; 
 int D40_SREG_CFG_LBE_POS ; 
 int D40_SREG_CFG_MST_POS ; 
 int D40_SREG_CFG_PHY_PEN_POS ; 
 int D40_SREG_CFG_PHY_TM_POS ; 
 int D40_SREG_CFG_PRI_POS ; 
 int D40_SREG_CFG_PSIZE_POS ; 
 int D40_SREG_CFG_TIM_POS ; 
 int D40_TYPE_TO_EVENT (int /*<<< orphan*/ ) ; 
 scalar_t__ DMA_DEV_TO_DEV ; 
 scalar_t__ DMA_DEV_TO_MEM ; 
 scalar_t__ DMA_MEM_TO_DEV ; 
 scalar_t__ STEDMA40_NO_FLOW_CTRL ; 
 int STEDMA40_PSIZE_PHY_1 ; 
 int d40_width_to_bits (int /*<<< orphan*/ ) ; 

void d40_phy_cfg(struct stedma40_chan_cfg *cfg, u32 *src_cfg, u32 *dst_cfg)
{
	u32 src = 0;
	u32 dst = 0;

	if ((cfg->dir == DMA_DEV_TO_MEM) ||
	    (cfg->dir == DMA_DEV_TO_DEV)) {
		/* Set master port to 1 */
		src |= BIT(D40_SREG_CFG_MST_POS);
		src |= D40_TYPE_TO_EVENT(cfg->dev_type);

		if (cfg->src_info.flow_ctrl == STEDMA40_NO_FLOW_CTRL)
			src |= BIT(D40_SREG_CFG_PHY_TM_POS);
		else
			src |= 3 << D40_SREG_CFG_PHY_TM_POS;
	}
	if ((cfg->dir == DMA_MEM_TO_DEV) ||
	    (cfg->dir == DMA_DEV_TO_DEV)) {
		/* Set master port to 1 */
		dst |= BIT(D40_SREG_CFG_MST_POS);
		dst |= D40_TYPE_TO_EVENT(cfg->dev_type);

		if (cfg->dst_info.flow_ctrl == STEDMA40_NO_FLOW_CTRL)
			dst |= BIT(D40_SREG_CFG_PHY_TM_POS);
		else
			dst |= 3 << D40_SREG_CFG_PHY_TM_POS;
	}
	/* Interrupt on end of transfer for destination */
	dst |= BIT(D40_SREG_CFG_TIM_POS);

	/* Generate interrupt on error */
	src |= BIT(D40_SREG_CFG_EIM_POS);
	dst |= BIT(D40_SREG_CFG_EIM_POS);

	/* PSIZE */
	if (cfg->src_info.psize != STEDMA40_PSIZE_PHY_1) {
		src |= BIT(D40_SREG_CFG_PHY_PEN_POS);
		src |= cfg->src_info.psize << D40_SREG_CFG_PSIZE_POS;
	}
	if (cfg->dst_info.psize != STEDMA40_PSIZE_PHY_1) {
		dst |= BIT(D40_SREG_CFG_PHY_PEN_POS);
		dst |= cfg->dst_info.psize << D40_SREG_CFG_PSIZE_POS;
	}

	/* Element size */
	src |= d40_width_to_bits(cfg->src_info.data_width)
		<< D40_SREG_CFG_ESIZE_POS;
	dst |= d40_width_to_bits(cfg->dst_info.data_width)
		<< D40_SREG_CFG_ESIZE_POS;

	/* Set the priority bit to high for the physical channel */
	if (cfg->high_priority) {
		src |= BIT(D40_SREG_CFG_PRI_POS);
		dst |= BIT(D40_SREG_CFG_PRI_POS);
	}

	if (cfg->src_info.big_endian)
		src |= BIT(D40_SREG_CFG_LBE_POS);
	if (cfg->dst_info.big_endian)
		dst |= BIT(D40_SREG_CFG_LBE_POS);

	*src_cfg = src;
	*dst_cfg = dst;
}