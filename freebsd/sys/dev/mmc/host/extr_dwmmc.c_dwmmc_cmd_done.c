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
struct mmc_command {int flags; void** resp; } ;
struct dwmmc_softc {struct mmc_command* curcmd; } ;

/* Variables and functions */
 int MMC_RSP_136 ; 
 int MMC_RSP_PRESENT ; 
 void* READ4 (struct dwmmc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDMMC_RESP0 ; 
 int /*<<< orphan*/  SDMMC_RESP1 ; 
 int /*<<< orphan*/  SDMMC_RESP2 ; 
 int /*<<< orphan*/  SDMMC_RESP3 ; 

__attribute__((used)) static void
dwmmc_cmd_done(struct dwmmc_softc *sc)
{
	struct mmc_command *cmd;

	cmd = sc->curcmd;
	if (cmd == NULL)
		return;

	if (cmd->flags & MMC_RSP_PRESENT) {
		if (cmd->flags & MMC_RSP_136) {
			cmd->resp[3] = READ4(sc, SDMMC_RESP0);
			cmd->resp[2] = READ4(sc, SDMMC_RESP1);
			cmd->resp[1] = READ4(sc, SDMMC_RESP2);
			cmd->resp[0] = READ4(sc, SDMMC_RESP3);
		} else {
			cmd->resp[3] = 0;
			cmd->resp[2] = 0;
			cmd->resp[1] = 0;
			cmd->resp[0] = READ4(sc, SDMMC_RESP0);
		}
	}
}