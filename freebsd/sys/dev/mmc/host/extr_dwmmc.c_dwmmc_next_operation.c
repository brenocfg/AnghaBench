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
struct mmc_request {int /*<<< orphan*/  (* done ) (struct mmc_request*) ;int /*<<< orphan*/  stop; int /*<<< orphan*/  cmd; } ;
struct dwmmc_softc {int flags; int /*<<< orphan*/ * curcmd; struct mmc_request* req; int /*<<< orphan*/  use_auto_stop; scalar_t__ cmd_done; scalar_t__ dto_rcvd; scalar_t__ acd_rcvd; } ;

/* Variables and functions */
 int PENDING_CMD ; 
 int PENDING_STOP ; 
 int READ4 (struct dwmmc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDMMC_STATUS ; 
 int SDMMC_STATUS_DATA_BUSY ; 
 int /*<<< orphan*/  dwmmc_start_cmd (struct dwmmc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct mmc_request*) ; 

__attribute__((used)) static void
dwmmc_next_operation(struct dwmmc_softc *sc)
{
	struct mmc_request *req;

	req = sc->req;
	if (req == NULL)
		return;

	sc->acd_rcvd = 0;
	sc->dto_rcvd = 0;
	sc->cmd_done = 0;

	/*
	 * XXX: Wait until card is still busy.
	 * We do need this to prevent data timeouts,
	 * mostly caused by multi-block write command
	 * followed by single-read.
	 */
	while(READ4(sc, SDMMC_STATUS) & (SDMMC_STATUS_DATA_BUSY))
		continue;

	if (sc->flags & PENDING_CMD) {
		sc->flags &= ~PENDING_CMD;
		dwmmc_start_cmd(sc, req->cmd);
		return;
	} else if (sc->flags & PENDING_STOP && !sc->use_auto_stop) {
		sc->flags &= ~PENDING_STOP;
		dwmmc_start_cmd(sc, req->stop);
		return;
	}

	sc->req = NULL;
	sc->curcmd = NULL;
	req->done(req);
}