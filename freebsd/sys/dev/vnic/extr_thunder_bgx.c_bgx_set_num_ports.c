#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint64_t ;
struct bgx {int qlm_mode; int lmac_count; int lane_to_sds; int use_training; int /*<<< orphan*/  lmac_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BGX_CMR_RX_LMACS ; 
 int /*<<< orphan*/  BGX_MODE_10G_KR ; 
 int /*<<< orphan*/  BGX_MODE_40G_KR ; 
 int /*<<< orphan*/  BGX_MODE_RXAUI ; 
 int /*<<< orphan*/  BGX_MODE_SGMII ; 
 int /*<<< orphan*/  BGX_MODE_XAUI ; 
 int /*<<< orphan*/  BGX_MODE_XFI ; 
 int /*<<< orphan*/  BGX_MODE_XLAUI ; 
#define  QLM_MODE_10G_KR_4X1 134 
#define  QLM_MODE_40G_KR4_1X4 133 
#define  QLM_MODE_RXAUI_2X2 132 
#define  QLM_MODE_SGMII 131 
#define  QLM_MODE_XAUI_1X4 130 
#define  QLM_MODE_XFI_4X1 129 
#define  QLM_MODE_XLAUI_1X4 128 
 int bgx_reg_read (struct bgx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bgx_set_num_ports(struct bgx *bgx)
{
	uint64_t lmac_count;

	switch (bgx->qlm_mode) {
	case QLM_MODE_SGMII:
		bgx->lmac_count = 4;
		bgx->lmac_type = BGX_MODE_SGMII;
		bgx->lane_to_sds = 0;
		break;
	case QLM_MODE_XAUI_1X4:
		bgx->lmac_count = 1;
		bgx->lmac_type = BGX_MODE_XAUI;
		bgx->lane_to_sds = 0xE4;
			break;
	case QLM_MODE_RXAUI_2X2:
		bgx->lmac_count = 2;
		bgx->lmac_type = BGX_MODE_RXAUI;
		bgx->lane_to_sds = 0xE4;
			break;
	case QLM_MODE_XFI_4X1:
		bgx->lmac_count = 4;
		bgx->lmac_type = BGX_MODE_XFI;
		bgx->lane_to_sds = 0;
		break;
	case QLM_MODE_XLAUI_1X4:
		bgx->lmac_count = 1;
		bgx->lmac_type = BGX_MODE_XLAUI;
		bgx->lane_to_sds = 0xE4;
		break;
	case QLM_MODE_10G_KR_4X1:
		bgx->lmac_count = 4;
		bgx->lmac_type = BGX_MODE_10G_KR;
		bgx->lane_to_sds = 0;
		bgx->use_training = 1;
		break;
	case QLM_MODE_40G_KR4_1X4:
		bgx->lmac_count = 1;
		bgx->lmac_type = BGX_MODE_40G_KR;
		bgx->lane_to_sds = 0xE4;
		bgx->use_training = 1;
		break;
	default:
		bgx->lmac_count = 0;
		break;
	}

	/*
	 * Check if low level firmware has programmed LMAC count
	 * based on board type, if yes consider that otherwise
	 * the default static values
	 */
	lmac_count = bgx_reg_read(bgx, 0, BGX_CMR_RX_LMACS) & 0x7;
	if (lmac_count != 4)
		bgx->lmac_count = lmac_count;
}