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
typedef  unsigned long uint64_t ;
struct lmac {int lmacid; struct bgx* bgx; } ;
struct bgx {int lmac_type; int /*<<< orphan*/  dev; scalar_t__ use_training; } ;

/* Variables and functions */
 int BGX_MODE_10G_KR ; 
 int BGX_MODE_40G_KR ; 
 int BGX_MODE_XFI ; 
 int BGX_MODE_XLAUI ; 
 int /*<<< orphan*/  BGX_SMUX_CTL ; 
 int /*<<< orphan*/  BGX_SMUX_RX_CTL ; 
 int /*<<< orphan*/  BGX_SPUX_BR_PMD_CRTL ; 
 int /*<<< orphan*/  BGX_SPUX_BR_STATUS1 ; 
 int /*<<< orphan*/  BGX_SPUX_BX_STATUS ; 
 int /*<<< orphan*/  BGX_SPUX_CONTROL1 ; 
 int /*<<< orphan*/  BGX_SPUX_INT ; 
 int /*<<< orphan*/  BGX_SPUX_MISC_CONTROL ; 
 int /*<<< orphan*/  BGX_SPUX_STATUS1 ; 
 int /*<<< orphan*/  BGX_SPUX_STATUS2 ; 
 int ENXIO ; 
 int /*<<< orphan*/  FALSE ; 
 int SMU_CTL_RX_IDLE ; 
 int SMU_CTL_TX_IDLE ; 
 int SMU_RX_CTL_STATUS ; 
 int SPU_BR_STATUS_BLK_LOCK ; 
 int SPU_BX_STATUS_RX_ALIGN ; 
 int SPU_CTL_RESET ; 
 unsigned long SPU_MISC_CTL_RX_DIS ; 
 int SPU_STATUS1_RCV_LNK ; 
 int SPU_STATUS2_RCVFLT ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ bgx_poll_reg (struct bgx*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bgx_reg_modify (struct bgx*,int,int /*<<< orphan*/ ,int) ; 
 int bgx_reg_read (struct bgx*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bgx_reg_write (struct bgx*,int,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
bgx_xaui_check_link(struct lmac *lmac)
{
	struct bgx *bgx = lmac->bgx;
	int lmacid = lmac->lmacid;
	int lmac_type = bgx->lmac_type;
	uint64_t cfg;

	bgx_reg_modify(bgx, lmacid, BGX_SPUX_MISC_CONTROL, SPU_MISC_CTL_RX_DIS);
	if (bgx->use_training) {
		cfg = bgx_reg_read(bgx, lmacid, BGX_SPUX_INT);
		if ((cfg & (1UL << 13)) == 0) {
			cfg = (1UL << 13) | (1UL << 14);
			bgx_reg_write(bgx, lmacid, BGX_SPUX_INT, cfg);
			cfg = bgx_reg_read(bgx, lmacid, BGX_SPUX_BR_PMD_CRTL);
			cfg |= (1UL << 0);
			bgx_reg_write(bgx, lmacid, BGX_SPUX_BR_PMD_CRTL, cfg);
			return (ENXIO);
		}
	}

	/* wait for PCS to come out of reset */
	if (bgx_poll_reg(bgx, lmacid, BGX_SPUX_CONTROL1,
	    SPU_CTL_RESET, TRUE) != 0) {
		device_printf(bgx->dev, "BGX SPU reset not completed\n");
		return (ENXIO);
	}

	if ((lmac_type == BGX_MODE_10G_KR) || (lmac_type == BGX_MODE_XFI) ||
	    (lmac_type == BGX_MODE_40G_KR) || (lmac_type == BGX_MODE_XLAUI)) {
		if (bgx_poll_reg(bgx, lmacid, BGX_SPUX_BR_STATUS1,
		    SPU_BR_STATUS_BLK_LOCK, FALSE)) {
			device_printf(bgx->dev,
			    "SPU_BR_STATUS_BLK_LOCK not completed\n");
			return (ENXIO);
		}
	} else {
		if (bgx_poll_reg(bgx, lmacid, BGX_SPUX_BX_STATUS,
		    SPU_BX_STATUS_RX_ALIGN, FALSE) != 0) {
			device_printf(bgx->dev,
			    "SPU_BX_STATUS_RX_ALIGN not completed\n");
			return (ENXIO);
		}
	}

	/* Clear rcvflt bit (latching high) and read it back */
	bgx_reg_modify(bgx, lmacid, BGX_SPUX_STATUS2, SPU_STATUS2_RCVFLT);
	if (bgx_reg_read(bgx, lmacid, BGX_SPUX_STATUS2) & SPU_STATUS2_RCVFLT) {
		device_printf(bgx->dev, "Receive fault, retry training\n");
		if (bgx->use_training) {
			cfg = bgx_reg_read(bgx, lmacid, BGX_SPUX_INT);
			if ((cfg & (1UL << 13)) == 0) {
				cfg = (1UL << 13) | (1UL << 14);
				bgx_reg_write(bgx, lmacid, BGX_SPUX_INT, cfg);
				cfg = bgx_reg_read(bgx, lmacid,
				    BGX_SPUX_BR_PMD_CRTL);
				cfg |= (1UL << 0);
				bgx_reg_write(bgx, lmacid,
				    BGX_SPUX_BR_PMD_CRTL, cfg);
				return (ENXIO);
			}
		}
		return (ENXIO);
	}

	/* Wait for MAC RX to be ready */
	if (bgx_poll_reg(bgx, lmacid, BGX_SMUX_RX_CTL,
	    SMU_RX_CTL_STATUS, TRUE) != 0) {
		device_printf(bgx->dev, "SMU RX link not okay\n");
		return (ENXIO);
	}

	/* Wait for BGX RX to be idle */
	if (bgx_poll_reg(bgx, lmacid, BGX_SMUX_CTL,
	    SMU_CTL_RX_IDLE, FALSE) != 0) {
		device_printf(bgx->dev, "SMU RX not idle\n");
		return (ENXIO);
	}

	/* Wait for BGX TX to be idle */
	if (bgx_poll_reg(bgx, lmacid, BGX_SMUX_CTL,
	    SMU_CTL_TX_IDLE, FALSE) != 0) {
		device_printf(bgx->dev, "SMU TX not idle\n");
		return (ENXIO);
	}

	if ((bgx_reg_read(bgx, lmacid, BGX_SPUX_STATUS2) &
	    SPU_STATUS2_RCVFLT) != 0) {
		device_printf(bgx->dev, "Receive fault\n");
		return (ENXIO);
	}

	/* Receive link is latching low. Force it high and verify it */
	bgx_reg_modify(bgx, lmacid, BGX_SPUX_STATUS1, SPU_STATUS1_RCV_LNK);
	if (bgx_poll_reg(bgx, lmacid, BGX_SPUX_STATUS1,
	    SPU_STATUS1_RCV_LNK, FALSE) != 0) {
		device_printf(bgx->dev, "SPU receive link down\n");
		return (ENXIO);
	}

	cfg = bgx_reg_read(bgx, lmacid, BGX_SPUX_MISC_CONTROL);
	cfg &= ~SPU_MISC_CTL_RX_DIS;
	bgx_reg_write(bgx, lmacid, BGX_SPUX_MISC_CONTROL, cfg);
	return (0);
}