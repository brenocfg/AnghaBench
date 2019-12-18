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
struct bgx {int lmac_count; int lmac_type; int lane_to_sds; TYPE_1__* lmac; int /*<<< orphan*/  bgx_id; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  lmacid_bd; } ;

/* Variables and functions */
 scalar_t__ BGX_CMRX_CFG ; 
 int /*<<< orphan*/  BGX_CMR_BIST_STATUS ; 
 int /*<<< orphan*/  BGX_CMR_CHAN_MSK_AND ; 
 int /*<<< orphan*/  BGX_CMR_GLOBAL_CFG ; 
 scalar_t__ BGX_CMR_RX_DMACX_CAM ; 
 scalar_t__ BGX_CMR_RX_LMACS ; 
 scalar_t__ BGX_CMR_RX_STREERING ; 
 scalar_t__ BGX_CMR_TX_LMACS ; 
 int BGX_MODE_RXAUI ; 
 unsigned long CMR_GLOBAL_CFG_FCS_STRIP ; 
 unsigned long MAX_BGX_CHANS_PER_LMAC ; 
 int RX_DMAC_COUNT ; 
 int RX_TRAFFIC_STEER_RULE_COUNT ; 
 int /*<<< orphan*/  bgx_reg_modify (struct bgx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ bgx_reg_read (struct bgx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bgx_reg_write (struct bgx*,int,scalar_t__,int) ; 
 int /*<<< orphan*/  bgx_set_num_ports (struct bgx*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lmac_count ; 

__attribute__((used)) static void
bgx_init_hw(struct bgx *bgx)
{
	int i;

	bgx_set_num_ports(bgx);

	bgx_reg_modify(bgx, 0, BGX_CMR_GLOBAL_CFG, CMR_GLOBAL_CFG_FCS_STRIP);
	if (bgx_reg_read(bgx, 0, BGX_CMR_BIST_STATUS))
		device_printf(bgx->dev, "BGX%d BIST failed\n", bgx->bgx_id);

	/* Set lmac type and lane2serdes mapping */
	for (i = 0; i < bgx->lmac_count; i++) {
		if (bgx->lmac_type == BGX_MODE_RXAUI) {
			if (i)
				bgx->lane_to_sds = 0x0e;
			else
				bgx->lane_to_sds = 0x04;
			bgx_reg_write(bgx, i, BGX_CMRX_CFG,
			    (bgx->lmac_type << 8) | bgx->lane_to_sds);
			continue;
		}
		bgx_reg_write(bgx, i, BGX_CMRX_CFG,
		    (bgx->lmac_type << 8) | (bgx->lane_to_sds + i));
		bgx->lmac[i].lmacid_bd = lmac_count;
		lmac_count++;
	}

	bgx_reg_write(bgx, 0, BGX_CMR_TX_LMACS, bgx->lmac_count);
	bgx_reg_write(bgx, 0, BGX_CMR_RX_LMACS, bgx->lmac_count);

	/* Set the backpressure AND mask */
	for (i = 0; i < bgx->lmac_count; i++) {
		bgx_reg_modify(bgx, 0, BGX_CMR_CHAN_MSK_AND,
		    ((1UL << MAX_BGX_CHANS_PER_LMAC) - 1) <<
		    (i * MAX_BGX_CHANS_PER_LMAC));
	}

	/* Disable all MAC filtering */
	for (i = 0; i < RX_DMAC_COUNT; i++)
		bgx_reg_write(bgx, 0, BGX_CMR_RX_DMACX_CAM + (i * 8), 0x00);

	/* Disable MAC steering (NCSI traffic) */
	for (i = 0; i < RX_TRAFFIC_STEER_RULE_COUNT; i++)
		bgx_reg_write(bgx, 0, BGX_CMR_RX_STREERING + (i * 8), 0x00);
}