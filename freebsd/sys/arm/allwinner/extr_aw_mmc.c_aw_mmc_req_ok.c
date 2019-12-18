#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct mmc_command {int flags; void* error; TYPE_4__* data; void** resp; } ;
struct aw_mmc_softc {int aw_resid; TYPE_3__* aw_req; TYPE_2__* ccb; } ;
struct TYPE_8__ {int len; } ;
struct TYPE_7__ {struct mmc_command* cmd; } ;
struct TYPE_5__ {struct mmc_command cmd; } ;
struct TYPE_6__ {TYPE_1__ mmcio; } ;

/* Variables and functions */
 void* AW_MMC_READ_4 (struct aw_mmc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AW_MMC_RESP0 ; 
 int /*<<< orphan*/  AW_MMC_RESP1 ; 
 int /*<<< orphan*/  AW_MMC_RESP2 ; 
 int /*<<< orphan*/  AW_MMC_RESP3 ; 
 int /*<<< orphan*/  AW_MMC_STAR ; 
 int AW_MMC_STAR_CARD_BUSY ; 
 int /*<<< orphan*/  DELAY (int) ; 
 void* MMC_ERR_FAILED ; 
 int MMC_RSP_136 ; 
 int MMC_RSP_PRESENT ; 
 int /*<<< orphan*/  aw_mmc_req_done (struct aw_mmc_softc*) ; 

__attribute__((used)) static void
aw_mmc_req_ok(struct aw_mmc_softc *sc)
{
	int timeout;
	struct mmc_command *cmd;
	uint32_t status;

	timeout = 1000;
	while (--timeout > 0) {
		status = AW_MMC_READ_4(sc, AW_MMC_STAR);
		if ((status & AW_MMC_STAR_CARD_BUSY) == 0)
			break;
		DELAY(1000);
	}
#ifdef MMCCAM
	cmd = &sc->ccb->mmcio.cmd;
#else
	cmd = sc->aw_req->cmd;
#endif
	if (timeout == 0) {
		cmd->error = MMC_ERR_FAILED;
		aw_mmc_req_done(sc);
		return;
	}
	if (cmd->flags & MMC_RSP_PRESENT) {
		if (cmd->flags & MMC_RSP_136) {
			cmd->resp[0] = AW_MMC_READ_4(sc, AW_MMC_RESP3);
			cmd->resp[1] = AW_MMC_READ_4(sc, AW_MMC_RESP2);
			cmd->resp[2] = AW_MMC_READ_4(sc, AW_MMC_RESP1);
			cmd->resp[3] = AW_MMC_READ_4(sc, AW_MMC_RESP0);
		} else
			cmd->resp[0] = AW_MMC_READ_4(sc, AW_MMC_RESP0);
	}
	/* All data has been transferred ? */
	if (cmd->data != NULL && (sc->aw_resid << 2) < cmd->data->len)
		cmd->error = MMC_ERR_FAILED;
	aw_mmc_req_done(sc);
}