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
struct mmc_command {int /*<<< orphan*/  error; TYPE_2__* data; } ;
struct jz4780_mmc_softc {int sc_resid; TYPE_1__* sc_req; } ;
struct TYPE_4__ {int len; } ;
struct TYPE_3__ {struct mmc_command* cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMC_ERR_FAILED ; 
 int /*<<< orphan*/  jz4780_mmc_req_done (struct jz4780_mmc_softc*) ; 

__attribute__((used)) static void
jz4780_mmc_req_ok(struct jz4780_mmc_softc *sc)
{
	struct mmc_command *cmd;

	cmd = sc->sc_req->cmd;
	/* All data has been transferred ? */
	if (cmd->data != NULL && (sc->sc_resid << 2) < cmd->data->len)
		cmd->error = MMC_ERR_FAILED;
	jz4780_mmc_req_done(sc);
}