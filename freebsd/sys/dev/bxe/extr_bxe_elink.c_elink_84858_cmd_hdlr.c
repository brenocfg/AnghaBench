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
typedef  int /*<<< orphan*/  elink_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  ELINK_DEBUG_P0 (struct bxe_softc*,char*) ; 
 int /*<<< orphan*/  ELINK_STATUS_ERROR ; 
 int /*<<< orphan*/  ELINK_STATUS_OK ; 
 scalar_t__ MDIO_848xx_CMD_HDLR_COMMAND ; 
 scalar_t__ MDIO_848xx_CMD_HDLR_DATA1 ; 
 scalar_t__ MDIO_848xx_CMD_HDLR_STATUS ; 
 int /*<<< orphan*/  MDIO_CTL_DEVAD ; 
 scalar_t__ PHY84858_STATUS_CMD_COMPLETE_ERROR ; 
 scalar_t__ PHY84858_STATUS_CMD_COMPLETE_PASS ; 
 scalar_t__ PHY84858_STATUS_CMD_IN_PROGRESS ; 
 scalar_t__ PHY84858_STATUS_CMD_SYSTEM_BUSY ; 
 int PHY848xx_CMDHDLR_WAIT ; 
 int /*<<< orphan*/  elink_cl45_read (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  elink_cl45_write (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static elink_status_t elink_84858_cmd_hdlr(struct elink_phy *phy,
					   struct elink_params *params,
					   uint16_t fw_cmd,
					   uint16_t cmd_args[], int argc)
{
	int idx;
	uint16_t val;
	struct bxe_softc *sc = params->sc;

	/* Step 1: Poll the STATUS register to see whether the previous command
	 * is in progress or the system is busy (CMD_IN_PROGRESS or
	 * SYSTEM_BUSY). If previous command is in progress or system is busy,
	 * check again until the previous command finishes execution and the
	 * system is available for taking command
	 */

	for (idx = 0; idx < PHY848xx_CMDHDLR_WAIT; idx++) {
		elink_cl45_read(sc, phy, MDIO_CTL_DEVAD,
				MDIO_848xx_CMD_HDLR_STATUS, &val);
		if ((val != PHY84858_STATUS_CMD_IN_PROGRESS) &&
		    (val != PHY84858_STATUS_CMD_SYSTEM_BUSY))
			break;
		DELAY(1000 * 1);
	}
	if (idx >= PHY848xx_CMDHDLR_WAIT) {
		ELINK_DEBUG_P0(sc, "FW cmd: FW not ready.\n");
		return ELINK_STATUS_ERROR;
	}

	/* Step2: If any parameters are required for the function, write them
	 * to the required DATA registers
	 */

	for (idx = 0; idx < argc; idx++) {
		elink_cl45_write(sc, phy, MDIO_CTL_DEVAD,
				 MDIO_848xx_CMD_HDLR_DATA1 + idx,
				 cmd_args[idx]);
	}

	/* Step3: When the firmware is ready for commands, write the 'Command
	 * code' to the CMD register
	 */
	elink_cl45_write(sc, phy, MDIO_CTL_DEVAD,
			 MDIO_848xx_CMD_HDLR_COMMAND, fw_cmd);

	/* Step4: Once the command has been written, poll the STATUS register
	 * to check whether the command has completed (CMD_COMPLETED_PASS/
	 * CMD_FOR_CMDS or CMD_COMPLETED_ERROR).
	 */

	for (idx = 0; idx < PHY848xx_CMDHDLR_WAIT; idx++) {
		elink_cl45_read(sc, phy, MDIO_CTL_DEVAD,
				MDIO_848xx_CMD_HDLR_STATUS, &val);
		if ((val == PHY84858_STATUS_CMD_COMPLETE_PASS) ||
		    (val == PHY84858_STATUS_CMD_COMPLETE_ERROR))
			break;
		DELAY(1000 * 1);
	}
	if ((idx >= PHY848xx_CMDHDLR_WAIT) ||
	    (val == PHY84858_STATUS_CMD_COMPLETE_ERROR)) {
		ELINK_DEBUG_P0(sc, "FW cmd failed.\n");
		return ELINK_STATUS_ERROR;
	}
	/* Step5: Once the command has completed, read the specficied DATA
	 * registers for any saved results for the command, if applicable
	 */

	/* Gather returning data */
	for (idx = 0; idx < argc; idx++) {
		elink_cl45_read(sc, phy, MDIO_CTL_DEVAD,
				MDIO_848xx_CMD_HDLR_DATA1 + idx,
				&cmd_args[idx]);
	}

	return ELINK_STATUS_OK;
}