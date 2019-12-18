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
struct mmc_command {scalar_t__ error; scalar_t__ opcode; scalar_t__ data; } ;
struct dwmmc_softc {scalar_t__ acd_rcvd; scalar_t__ use_auto_stop; scalar_t__ dto_rcvd; int /*<<< orphan*/  cmd_done; struct mmc_command* curcmd; } ;

/* Variables and functions */
 scalar_t__ MMC_ERR_NONE ; 
 scalar_t__ MMC_READ_MULTIPLE_BLOCK ; 
 scalar_t__ MMC_WRITE_MULTIPLE_BLOCK ; 
 int /*<<< orphan*/  dwmmc_next_operation (struct dwmmc_softc*) ; 

__attribute__((used)) static void
dwmmc_tasklet(struct dwmmc_softc *sc)
{
	struct mmc_command *cmd;

	cmd = sc->curcmd;
	if (cmd == NULL)
		return;

	if (!sc->cmd_done)
		return;

	if (cmd->error != MMC_ERR_NONE || !cmd->data) {
		dwmmc_next_operation(sc);
	} else if (cmd->data && sc->dto_rcvd) {
		if ((cmd->opcode == MMC_WRITE_MULTIPLE_BLOCK ||
		     cmd->opcode == MMC_READ_MULTIPLE_BLOCK) &&
		     sc->use_auto_stop) {
			if (sc->acd_rcvd)
				dwmmc_next_operation(sc);
		} else {
			dwmmc_next_operation(sc);
		}
	}
}