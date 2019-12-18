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
struct mmc_softc {scalar_t__ squelched; int /*<<< orphan*/  dev; int /*<<< orphan*/  log_count; int /*<<< orphan*/  log_time; } ;
struct mmc_request {struct mmc_command* cmd; } ;
struct mmc_command {int error; int /*<<< orphan*/  opcode; TYPE_1__* data; struct mmc_request* mrq; scalar_t__ retries; struct mmc_request* resp; } ;
typedef  int /*<<< orphan*/  mreq ;
typedef  scalar_t__ device_t ;
struct TYPE_2__ {struct mmc_request* mrq; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_PPS ; 
 scalar_t__ MMCBUS_WAIT_FOR_REQUEST (scalar_t__,scalar_t__,struct mmc_request*) ; 
 int MMC_ERR_FAILED ; 
 int MMC_ERR_NONE ; 
 struct mmc_softc* device_get_softc (scalar_t__) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct mmc_request*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ppsratecheck (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
mmc_wait_for_cmd(device_t busdev, device_t dev, struct mmc_command *cmd,
    int retries)
{
	struct mmc_request mreq;
	struct mmc_softc *sc;
	int err;

	do {
		memset(&mreq, 0, sizeof(mreq));
		memset(cmd->resp, 0, sizeof(cmd->resp));
		cmd->retries = 0; /* Retries done here, not in hardware. */
		cmd->mrq = &mreq;
		if (cmd->data != NULL)
			cmd->data->mrq = &mreq;
		mreq.cmd = cmd;
		if (MMCBUS_WAIT_FOR_REQUEST(busdev, dev, &mreq) != 0)
			err = MMC_ERR_FAILED;
		else
			err = cmd->error;
	} while (err != MMC_ERR_NONE && retries-- > 0);

	if (err != MMC_ERR_NONE && busdev == dev) {
		sc = device_get_softc(busdev);
		if (sc->squelched == 0 && ppsratecheck(&sc->log_time,
		    &sc->log_count, LOG_PPS)) {
			device_printf(sc->dev, "CMD%d failed, RESULT: %d\n",
			    cmd->opcode, err);
		}
	}

	return (err);
}