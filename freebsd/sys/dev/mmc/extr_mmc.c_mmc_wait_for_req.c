#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mmc_softc {int /*<<< orphan*/  dev; int /*<<< orphan*/  sc_mtx; } ;
struct mmc_request {int flags; TYPE_2__* cmd; struct mmc_softc* done_data; int /*<<< orphan*/  done; } ;
struct TYPE_4__ {int /*<<< orphan*/  error; int /*<<< orphan*/  opcode; TYPE_1__* data; int /*<<< orphan*/  flags; int /*<<< orphan*/  arg; } ;
struct TYPE_3__ {scalar_t__ len; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMCBR_REQUEST (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mmc_request*) ; 
 int /*<<< orphan*/  MMC_ERR_NONE ; 
 int /*<<< orphan*/  MMC_LOCK (struct mmc_softc*) ; 
 int MMC_REQ_DONE ; 
 int /*<<< orphan*/  MMC_UNLOCK (struct mmc_softc*) ; 
 scalar_t__ __predict_false (int) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int mmc_debug ; 
 int /*<<< orphan*/  mmc_wakeup ; 
 int /*<<< orphan*/  msleep (struct mmc_request*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static int
mmc_wait_for_req(struct mmc_softc *sc, struct mmc_request *req)
{

	req->done = mmc_wakeup;
	req->done_data = sc;
	if (__predict_false(mmc_debug > 1)) {
		device_printf(sc->dev, "REQUEST: CMD%d arg %#x flags %#x",
		    req->cmd->opcode, req->cmd->arg, req->cmd->flags);
		if (req->cmd->data) {
			printf(" data %d\n", (int)req->cmd->data->len);
		} else
			printf("\n");
	}
	MMCBR_REQUEST(device_get_parent(sc->dev), sc->dev, req);
	MMC_LOCK(sc);
	while ((req->flags & MMC_REQ_DONE) == 0)
		msleep(req, &sc->sc_mtx, 0, "mmcreq", 0);
	MMC_UNLOCK(sc);
	if (__predict_false(mmc_debug > 2 || (mmc_debug > 0 &&
	    req->cmd->error != MMC_ERR_NONE)))
		device_printf(sc->dev, "CMD%d RESULT: %d\n",
		    req->cmd->opcode, req->cmd->error);
	return (0);
}