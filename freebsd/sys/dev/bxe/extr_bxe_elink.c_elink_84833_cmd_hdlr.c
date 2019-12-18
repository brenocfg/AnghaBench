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
typedef  scalar_t__ uint16_t ;
struct elink_phy {int dummy; } ;
struct elink_params {struct bxe_softc* sc; } ;
struct bxe_softc {int dummy; } ;
typedef  scalar_t__ elink_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  ELINK_DEBUG_P0 (struct bxe_softc*,char*) ; 
 scalar_t__ ELINK_STATUS_ERROR ; 
 scalar_t__ ELINK_STATUS_OK ; 
 scalar_t__ MDIO_848xx_CMD_HDLR_COMMAND ; 
 scalar_t__ MDIO_848xx_CMD_HDLR_DATA1 ; 
 scalar_t__ MDIO_848xx_CMD_HDLR_STATUS ; 
 int /*<<< orphan*/  MDIO_CTL_DEVAD ; 
 int PHY84833_MB_PROCESS1 ; 
 int PHY84833_MB_PROCESS2 ; 
 int PHY84833_MB_PROCESS3 ; 
 scalar_t__ PHY84833_STATUS_CMD_CLEAR_COMPLETE ; 
 scalar_t__ PHY84833_STATUS_CMD_COMPLETE_ERROR ; 
 scalar_t__ PHY84833_STATUS_CMD_COMPLETE_PASS ; 
 scalar_t__ PHY84833_STATUS_CMD_OPEN_FOR_CMDS ; 
 scalar_t__ PHY84833_STATUS_CMD_OPEN_OVERRIDE ; 
 int PHY848xx_CMDHDLR_WAIT ; 
 int /*<<< orphan*/  elink_cl45_read (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  elink_cl45_write (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static elink_status_t elink_84833_cmd_hdlr(struct elink_phy *phy,
				struct elink_params *params, uint16_t fw_cmd,
				uint16_t cmd_args[], int argc, int process)
{
	int idx;
	uint16_t val;
	struct bxe_softc *sc = params->sc;
	elink_status_t rc = ELINK_STATUS_OK;

	if (process == PHY84833_MB_PROCESS2) {
	/* Write CMD_OPEN_OVERRIDE to STATUS reg */
	elink_cl45_write(sc, phy, MDIO_CTL_DEVAD,
				 MDIO_848xx_CMD_HDLR_STATUS,
			PHY84833_STATUS_CMD_OPEN_OVERRIDE);
	}

	for (idx = 0; idx < PHY848xx_CMDHDLR_WAIT; idx++) {
		elink_cl45_read(sc, phy, MDIO_CTL_DEVAD,
			       MDIO_848xx_CMD_HDLR_STATUS, &val);
		if (val == PHY84833_STATUS_CMD_OPEN_FOR_CMDS)
			break;
		DELAY(1000 * 1);
	}
	if (idx >= PHY848xx_CMDHDLR_WAIT) {
		ELINK_DEBUG_P0(sc, "FW cmd: FW not ready.\n");
		/* if the status is CMD_COMPLETE_PASS or CMD_COMPLETE_ERROR
		 * clear the status to CMD_CLEAR_COMPLETE
		 */
		if (val == PHY84833_STATUS_CMD_COMPLETE_PASS ||
		    val == PHY84833_STATUS_CMD_COMPLETE_ERROR) {
			elink_cl45_write(sc, phy, MDIO_CTL_DEVAD,
					 MDIO_848xx_CMD_HDLR_STATUS,
					 PHY84833_STATUS_CMD_CLEAR_COMPLETE);
		}
		return ELINK_STATUS_ERROR;
	}
	if (process == PHY84833_MB_PROCESS1 ||
	    process == PHY84833_MB_PROCESS2) {
		/* Prepare argument(s) */
	for (idx = 0; idx < argc; idx++) {
		elink_cl45_write(sc, phy, MDIO_CTL_DEVAD,
					 MDIO_848xx_CMD_HDLR_DATA1 + idx,
				cmd_args[idx]);
	}
	}

	/* Issue command */
	elink_cl45_write(sc, phy, MDIO_CTL_DEVAD,
			MDIO_848xx_CMD_HDLR_COMMAND, fw_cmd);
	for (idx = 0; idx < PHY848xx_CMDHDLR_WAIT; idx++) {
		elink_cl45_read(sc, phy, MDIO_CTL_DEVAD,
			       MDIO_848xx_CMD_HDLR_STATUS, &val);
		if ((val == PHY84833_STATUS_CMD_COMPLETE_PASS) ||
			(val == PHY84833_STATUS_CMD_COMPLETE_ERROR))
			break;
		DELAY(1000 * 1);
	}
	if ((idx >= PHY848xx_CMDHDLR_WAIT) ||
		(val == PHY84833_STATUS_CMD_COMPLETE_ERROR)) {
		ELINK_DEBUG_P0(sc, "FW cmd failed.\n");
		rc = ELINK_STATUS_ERROR;
	}
	if (process == PHY84833_MB_PROCESS3 && rc == ELINK_STATUS_OK) {
	/* Gather returning data */
	for (idx = 0; idx < argc; idx++) {
		elink_cl45_read(sc, phy, MDIO_CTL_DEVAD,
					MDIO_848xx_CMD_HDLR_DATA1 + idx,
				&cmd_args[idx]);
	}
	}
	if (val == PHY84833_STATUS_CMD_COMPLETE_ERROR ||
	    val == PHY84833_STATUS_CMD_COMPLETE_PASS) {
	elink_cl45_write(sc, phy, MDIO_CTL_DEVAD,
				 MDIO_848xx_CMD_HDLR_STATUS,
			PHY84833_STATUS_CMD_CLEAR_COMPLETE);
	}
	return rc;
}