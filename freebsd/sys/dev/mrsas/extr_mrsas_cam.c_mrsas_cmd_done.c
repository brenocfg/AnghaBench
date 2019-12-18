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
struct mrsas_softc {int /*<<< orphan*/  sim_lock; } ;
struct mrsas_mpt_cmd {int callout_owner; int /*<<< orphan*/ * ccb_ptr; int /*<<< orphan*/  cm_callout; } ;

/* Variables and functions */
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrsas_release_mpt_cmd (struct mrsas_mpt_cmd*) ; 
 int /*<<< orphan*/  mrsas_unmap_request (struct mrsas_softc*,struct mrsas_mpt_cmd*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xpt_done (int /*<<< orphan*/ *) ; 

void
mrsas_cmd_done(struct mrsas_softc *sc, struct mrsas_mpt_cmd *cmd)
{
	mrsas_unmap_request(sc, cmd);
	
	mtx_lock(&sc->sim_lock);
	if (cmd->callout_owner) {
		callout_stop(&cmd->cm_callout);
		cmd->callout_owner  = false;
	}
	xpt_done(cmd->ccb_ptr);
	cmd->ccb_ptr = NULL;
	mtx_unlock(&sc->sim_lock);
	mrsas_release_mpt_cmd(cmd);
}