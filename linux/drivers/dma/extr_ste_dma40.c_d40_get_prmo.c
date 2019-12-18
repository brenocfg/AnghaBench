#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int const u32 ;
struct TYPE_2__ {size_t mode_opt; } ;
struct d40_chan {TYPE_1__ dma_cfg; } ;

/* Variables and functions */
#define  D40_DREG_PRMO_LCHAN_SRC_LOG_DST_LOG 139 
#define  D40_DREG_PRMO_LCHAN_SRC_LOG_DST_PHY 138 
#define  D40_DREG_PRMO_LCHAN_SRC_PHY_DST_LOG 137 
#define  D40_DREG_PRMO_PCHAN_BASIC 136 
#define  D40_DREG_PRMO_PCHAN_DOUBLE_DST 135 
#define  D40_DREG_PRMO_PCHAN_MODULO 134 
#define  STEDMA40_LCHAN_SRC_LOG_DST_LOG 133 
#define  STEDMA40_LCHAN_SRC_LOG_DST_PHY 132 
#define  STEDMA40_LCHAN_SRC_PHY_DST_LOG 131 
#define  STEDMA40_PCHAN_BASIC_MODE 130 
#define  STEDMA40_PCHAN_DOUBLE_DST_MODE 129 
#define  STEDMA40_PCHAN_MODULO_MODE 128 
 scalar_t__ chan_is_physical (struct d40_chan*) ; 

__attribute__((used)) static u32 d40_get_prmo(struct d40_chan *d40c)
{
	static const unsigned int phy_map[] = {
		[STEDMA40_PCHAN_BASIC_MODE]
			= D40_DREG_PRMO_PCHAN_BASIC,
		[STEDMA40_PCHAN_MODULO_MODE]
			= D40_DREG_PRMO_PCHAN_MODULO,
		[STEDMA40_PCHAN_DOUBLE_DST_MODE]
			= D40_DREG_PRMO_PCHAN_DOUBLE_DST,
	};
	static const unsigned int log_map[] = {
		[STEDMA40_LCHAN_SRC_PHY_DST_LOG]
			= D40_DREG_PRMO_LCHAN_SRC_PHY_DST_LOG,
		[STEDMA40_LCHAN_SRC_LOG_DST_PHY]
			= D40_DREG_PRMO_LCHAN_SRC_LOG_DST_PHY,
		[STEDMA40_LCHAN_SRC_LOG_DST_LOG]
			= D40_DREG_PRMO_LCHAN_SRC_LOG_DST_LOG,
	};

	if (chan_is_physical(d40c))
		return phy_map[d40c->dma_cfg.mode_opt];
	else
		return log_map[d40c->dma_cfg.mode_opt];
}