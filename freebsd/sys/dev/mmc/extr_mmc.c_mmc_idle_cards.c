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
struct mmc_softc {int /*<<< orphan*/  dev; } ;
struct mmc_command {int flags; int /*<<< orphan*/ * data; scalar_t__ arg; int /*<<< orphan*/  opcode; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_RETRIES ; 
 int MMC_CMD_BC ; 
 int /*<<< orphan*/  MMC_GO_IDLE_STATE ; 
 int MMC_RSP_NONE ; 
 int /*<<< orphan*/  cs_dontcare ; 
 int /*<<< orphan*/  cs_high ; 
 int /*<<< orphan*/  memset (struct mmc_command*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmc_ms_delay (int) ; 
 int /*<<< orphan*/  mmc_wait_for_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mmc_command*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmcbr_set_chip_select (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmcbr_update_ios (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mmc_idle_cards(struct mmc_softc *sc)
{
	device_t dev;
	struct mmc_command cmd;

	dev = sc->dev;
	mmcbr_set_chip_select(dev, cs_high);
	mmcbr_update_ios(dev);
	mmc_ms_delay(1);

	memset(&cmd, 0, sizeof(cmd));
	cmd.opcode = MMC_GO_IDLE_STATE;
	cmd.arg = 0;
	cmd.flags = MMC_RSP_NONE | MMC_CMD_BC;
	cmd.data = NULL;
	mmc_wait_for_cmd(sc->dev, sc->dev, &cmd, CMD_RETRIES);
	mmc_ms_delay(1);

	mmcbr_set_chip_select(dev, cs_dontcare);
	mmcbr_update_ios(dev);
	mmc_ms_delay(1);
}