#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int32_t ;
struct mrsas_softc {int /*<<< orphan*/  target_reset_outstanding; struct mrsas_mpt_cmd** target_reset_pool; } ;
struct mrsas_mpt_cmd {TYPE_3__* ccb_ptr; int /*<<< orphan*/  cm_callout; struct mrsas_softc* sc; } ;
struct TYPE_5__ {size_t target_id; } ;
struct TYPE_4__ {scalar_t__ bus_id; } ;
struct TYPE_6__ {TYPE_2__ ccb_h; TYPE_1__ cpi; } ;

/* Variables and functions */
 int MRSAS_MAX_PD ; 
 int SBT_1S ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,void (*) (void*),struct mrsas_mpt_cmd*) ; 
 int /*<<< orphan*/  callout_reset_sbt (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,void (*) (void*),struct mrsas_mpt_cmd*,int /*<<< orphan*/ ) ; 
 int hz ; 
 int /*<<< orphan*/  mrsas_atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void
mrsas_scsiio_timeout(void *data)
{
	struct mrsas_mpt_cmd *cmd;
	struct mrsas_softc *sc;
	u_int32_t target_id;

	if (!data)
		return;

	cmd = (struct mrsas_mpt_cmd *)data;
	sc = cmd->sc;

	if (cmd->ccb_ptr == NULL) {
		printf("command timeout with NULL ccb\n");
		return;
	}

	/*
	 * Below callout is dummy entry so that it will be cancelled from
	 * mrsas_cmd_done(). Now Controller will go to OCR/Kill Adapter based
	 * on OCR enable/disable property of Controller from ocr_thread
	 * context.
	 */
#if (__FreeBSD_version >= 1000510)
	callout_reset_sbt(&cmd->cm_callout, SBT_1S * 180, 0,
	    mrsas_scsiio_timeout, cmd, 0);
#else
	callout_reset(&cmd->cm_callout, (180000 * hz) / 1000,
	    mrsas_scsiio_timeout, cmd);
#endif

	if (cmd->ccb_ptr->cpi.bus_id == 0)
		target_id = cmd->ccb_ptr->ccb_h.target_id;
	else
		target_id = (cmd->ccb_ptr->ccb_h.target_id + (MRSAS_MAX_PD - 1));

	/* Save the cmd to be processed for TM, if it is not there in the array */
	if (sc->target_reset_pool[target_id] == NULL) {
		sc->target_reset_pool[target_id] = cmd;
		mrsas_atomic_inc(&sc->target_reset_outstanding);
	}

	return;
}