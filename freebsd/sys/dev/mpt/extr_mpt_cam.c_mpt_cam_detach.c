#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mpt_softc {int /*<<< orphan*/ * phydisk_sim; int /*<<< orphan*/  phydisk_path; int /*<<< orphan*/ * sim; int /*<<< orphan*/  path; int /*<<< orphan*/ * sas_portinfo; TYPE_2__* tmf_req; int /*<<< orphan*/  scsi_tgt_handler_id; scalar_t__ ready; } ;
struct TYPE_4__ {int /*<<< orphan*/  reply_handler; } ;
typedef  TYPE_1__ mpt_handler_t ;
struct TYPE_5__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPT_HANDLER_REPLY ; 
 int /*<<< orphan*/  MPT_LOCK (struct mpt_softc*) ; 
 int /*<<< orphan*/  MPT_UNLOCK (struct mpt_softc*) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  REQ_STATE_ALLOCATED ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  cam_sim_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_sim_path (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fc_els_handler_id ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpt_deregister_handler (struct mpt_softc*,int /*<<< orphan*/ ,TYPE_1__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpt_fc_els_reply_handler ; 
 int /*<<< orphan*/  mpt_free_request (struct mpt_softc*,TYPE_2__*) ; 
 int /*<<< orphan*/  mpt_sata_pass_reply_handler ; 
 int /*<<< orphan*/  mpt_scsi_reply_handler ; 
 int /*<<< orphan*/  mpt_scsi_tgt_reply_handler ; 
 int /*<<< orphan*/  mpt_scsi_tmf_reply_handler ; 
 int /*<<< orphan*/  mpt_terminate_recovery_thread (struct mpt_softc*) ; 
 int /*<<< orphan*/  sata_pass_handler_id ; 
 int /*<<< orphan*/  scsi_io_handler_id ; 
 int /*<<< orphan*/  scsi_tmf_handler_id ; 
 int /*<<< orphan*/  xpt_bus_deregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_free_path (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mpt_cam_detach(struct mpt_softc *mpt)
{
	mpt_handler_t handler;

	MPT_LOCK(mpt);
	mpt->ready = 0;
	mpt_terminate_recovery_thread(mpt); 

	handler.reply_handler = mpt_scsi_reply_handler;
	mpt_deregister_handler(mpt, MPT_HANDLER_REPLY, handler,
			       scsi_io_handler_id);
	handler.reply_handler = mpt_scsi_tmf_reply_handler;
	mpt_deregister_handler(mpt, MPT_HANDLER_REPLY, handler,
			       scsi_tmf_handler_id);
	handler.reply_handler = mpt_fc_els_reply_handler;
	mpt_deregister_handler(mpt, MPT_HANDLER_REPLY, handler,
			       fc_els_handler_id);
	handler.reply_handler = mpt_scsi_tgt_reply_handler;
	mpt_deregister_handler(mpt, MPT_HANDLER_REPLY, handler,
			       mpt->scsi_tgt_handler_id);
	handler.reply_handler = mpt_sata_pass_reply_handler;
	mpt_deregister_handler(mpt, MPT_HANDLER_REPLY, handler,
			       sata_pass_handler_id);

	if (mpt->tmf_req != NULL) {
		mpt->tmf_req->state = REQ_STATE_ALLOCATED;
		mpt_free_request(mpt, mpt->tmf_req);
		mpt->tmf_req = NULL;
	}
	if (mpt->sas_portinfo != NULL) {
		free(mpt->sas_portinfo, M_DEVBUF);
		mpt->sas_portinfo = NULL;
	}

	if (mpt->sim != NULL) {
		xpt_free_path(mpt->path);
		xpt_bus_deregister(cam_sim_path(mpt->sim));
		cam_sim_free(mpt->sim, TRUE);
		mpt->sim = NULL;
	}

	if (mpt->phydisk_sim != NULL) {
		xpt_free_path(mpt->phydisk_path);
		xpt_bus_deregister(cam_sim_path(mpt->phydisk_sim));
		cam_sim_free(mpt->phydisk_sim, TRUE);
		mpt->phydisk_sim = NULL;
	}
	MPT_UNLOCK(mpt);
}