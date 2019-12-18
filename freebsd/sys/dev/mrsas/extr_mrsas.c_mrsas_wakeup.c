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
struct mrsas_softc {void* chan; } ;
struct mrsas_mfi_cmd {int cmd_status; TYPE_2__* frame; } ;
struct TYPE_3__ {int cmd_status; } ;
struct TYPE_4__ {TYPE_1__ io; } ;

/* Variables and functions */
 int /*<<< orphan*/  wakeup_one (void*) ; 

void
mrsas_wakeup(struct mrsas_softc *sc, struct mrsas_mfi_cmd *cmd)
{
	cmd->cmd_status = cmd->frame->io.cmd_status;

	if (cmd->cmd_status == 0xFF)
		cmd->cmd_status = 0;

	sc->chan = (void *)&cmd;
	wakeup_one((void *)&sc->chan);
	return;
}