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
struct bgx {int /*<<< orphan*/  bgx_id; void* qlm_mode; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BGX_CMRX_CFG ; 
#define  BGX_MODE_RXAUI 132 
#define  BGX_MODE_SGMII 131 
#define  BGX_MODE_XAUI 130 
#define  BGX_MODE_XFI 129 
#define  BGX_MODE_XLAUI 128 
 int /*<<< orphan*/  BGX_SPUX_BR_PMD_CRTL ; 
 void* QLM_MODE_10G_KR_4X1 ; 
 void* QLM_MODE_40G_KR4_1X4 ; 
 void* QLM_MODE_RXAUI_2X2 ; 
 void* QLM_MODE_SGMII ; 
 void* QLM_MODE_XAUI_1X4 ; 
 void* QLM_MODE_XFI_4X1 ; 
 void* QLM_MODE_XLAUI_1X4 ; 
 int SPU_PMD_CRTL_TRAIN_EN ; 
 int bgx_reg_read (struct bgx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bootverbose ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bgx_get_qlm_mode(struct bgx *bgx)
{
	device_t dev = bgx->dev;;
	int lmac_type;
	int train_en;

	/* Read LMAC0 type to figure out QLM mode
	 * This is configured by low level firmware
	 */
	lmac_type = bgx_reg_read(bgx, 0, BGX_CMRX_CFG);
	lmac_type = (lmac_type >> 8) & 0x07;

	train_en = bgx_reg_read(bgx, 0, BGX_SPUX_BR_PMD_CRTL) &
	    SPU_PMD_CRTL_TRAIN_EN;

	switch (lmac_type) {
	case BGX_MODE_SGMII:
		bgx->qlm_mode = QLM_MODE_SGMII;
		if (bootverbose) {
			device_printf(dev, "BGX%d QLM mode: SGMII\n",
			    bgx->bgx_id);
		}
		break;
	case BGX_MODE_XAUI:
		bgx->qlm_mode = QLM_MODE_XAUI_1X4;
		if (bootverbose) {
			device_printf(dev, "BGX%d QLM mode: XAUI\n",
			    bgx->bgx_id);
		}
		break;
	case BGX_MODE_RXAUI:
		bgx->qlm_mode = QLM_MODE_RXAUI_2X2;
		if (bootverbose) {
			device_printf(dev, "BGX%d QLM mode: RXAUI\n",
			    bgx->bgx_id);
		}
		break;
	case BGX_MODE_XFI:
		if (!train_en) {
			bgx->qlm_mode = QLM_MODE_XFI_4X1;
			if (bootverbose) {
				device_printf(dev, "BGX%d QLM mode: XFI\n",
				    bgx->bgx_id);
			}
		} else {
			bgx->qlm_mode = QLM_MODE_10G_KR_4X1;
			if (bootverbose) {
				device_printf(dev, "BGX%d QLM mode: 10G_KR\n",
				    bgx->bgx_id);
			}
		}
		break;
	case BGX_MODE_XLAUI:
		if (!train_en) {
			bgx->qlm_mode = QLM_MODE_XLAUI_1X4;
			if (bootverbose) {
				device_printf(dev, "BGX%d QLM mode: XLAUI\n",
				    bgx->bgx_id);
			}
		} else {
			bgx->qlm_mode = QLM_MODE_40G_KR4_1X4;
			if (bootverbose) {
				device_printf(dev, "BGX%d QLM mode: 40G_KR4\n",
				    bgx->bgx_id);
			}
		}
		break;
	default:
		bgx->qlm_mode = QLM_MODE_SGMII;
		if (bootverbose) {
			device_printf(dev, "BGX%d QLM default mode: SGMII\n",
			    bgx->bgx_id);
		}
	}
}