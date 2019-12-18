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
struct mpr_softc {int num_reqs; scalar_t__ io_cmds_active; struct mpr_command* commands; int /*<<< orphan*/  mpr_mtx; } ;
struct mpr_command {scalar_t__ cm_state; int cm_flags; int /*<<< orphan*/  cm_ccb; int /*<<< orphan*/  (* cm_complete ) (struct mpr_softc*,struct mpr_command*) ;int /*<<< orphan*/ * cm_data; int /*<<< orphan*/ * cm_reply; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  MPASS (int /*<<< orphan*/ *) ; 
 int MPR_CM_FLAGS_COMPLETE ; 
 int MPR_CM_FLAGS_POLLED ; 
 int MPR_CM_FLAGS_SATA_ID_TIMEOUT ; 
 int MPR_CM_FLAGS_WAKEUP ; 
 scalar_t__ MPR_CM_STATE_BUSY ; 
 scalar_t__ MPR_CM_STATE_FREE ; 
 int /*<<< orphan*/  MPR_FUNCTRACE (struct mpr_softc*) ; 
 int /*<<< orphan*/  MPR_RECOVERY ; 
 int /*<<< orphan*/  M_MPR ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mprsas_log_command (struct mpr_command*,int /*<<< orphan*/ ,char*,struct mpr_command*,scalar_t__,int,...) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct mpr_softc*,struct mpr_command*) ; 
 int /*<<< orphan*/  wakeup (struct mpr_command*) ; 

__attribute__((used)) static void 
mprsas_complete_all_commands(struct mpr_softc *sc)
{
	struct mpr_command *cm;
	int i;
	int completed;

	MPR_FUNCTRACE(sc);
	mtx_assert(&sc->mpr_mtx, MA_OWNED);

	/* complete all commands with a NULL reply */
	for (i = 1; i < sc->num_reqs; i++) {
		cm = &sc->commands[i];
		if (cm->cm_state == MPR_CM_STATE_FREE)
			continue;

		cm->cm_state = MPR_CM_STATE_BUSY;
		cm->cm_reply = NULL;
		completed = 0;

		if (cm->cm_flags & MPR_CM_FLAGS_SATA_ID_TIMEOUT) {
			MPASS(cm->cm_data);
			free(cm->cm_data, M_MPR);
			cm->cm_data = NULL;
		}

		if (cm->cm_flags & MPR_CM_FLAGS_POLLED)
			cm->cm_flags |= MPR_CM_FLAGS_COMPLETE;

		if (cm->cm_complete != NULL) {
			mprsas_log_command(cm, MPR_RECOVERY,
			    "completing cm %p state %x ccb %p for diag reset\n",
			    cm, cm->cm_state, cm->cm_ccb);
			cm->cm_complete(sc, cm);
			completed = 1;
		} else if (cm->cm_flags & MPR_CM_FLAGS_WAKEUP) {
			mprsas_log_command(cm, MPR_RECOVERY,
			    "waking up cm %p state %x ccb %p for diag reset\n", 
			    cm, cm->cm_state, cm->cm_ccb);
			wakeup(cm);
			completed = 1;
		}

		if ((completed == 0) && (cm->cm_state != MPR_CM_STATE_FREE)) {
			/* this should never happen, but if it does, log */
			mprsas_log_command(cm, MPR_RECOVERY,
			    "cm %p state %x flags 0x%x ccb %p during diag "
			    "reset\n", cm, cm->cm_state, cm->cm_flags,
			    cm->cm_ccb);
		}
	}

	sc->io_cmds_active = 0;
}