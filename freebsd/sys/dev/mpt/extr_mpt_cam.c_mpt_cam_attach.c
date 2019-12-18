#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int GlobalCredits; } ;
struct mpt_softc {int role; int /*<<< orphan*/ * phydisk_sim; int /*<<< orphan*/  phydisk_path; int /*<<< orphan*/  dev; TYPE_2__* ioc_page2; int /*<<< orphan*/ * sim; int /*<<< orphan*/  path; TYPE_5__* tmf_req; scalar_t__ is_sas; int /*<<< orphan*/  scsi_tgt_handler_id; scalar_t__ is_fc; scalar_t__ els_cmds_allocated; TYPE_1__ ioc_facts; int /*<<< orphan*/  request_timeout_list; } ;
struct cam_devq {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  reply_handler; } ;
typedef  TYPE_3__ mpt_handler_t ;
struct TYPE_9__ {int /*<<< orphan*/  state; } ;
struct TYPE_7__ {scalar_t__ MaxPhysDisks; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_LUN_WILDCARD ; 
 scalar_t__ CAM_REQ_CMP ; 
 scalar_t__ CAM_SUCCESS ; 
 int /*<<< orphan*/  CAM_TARGET_WILDCARD ; 
 int ENOMEM ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  MPT_HANDLER_REPLY ; 
 int /*<<< orphan*/  MPT_LOCK (struct mpt_softc*) ; 
 int MPT_MAX_REQUESTS (struct mpt_softc*) ; 
 int /*<<< orphan*/  MPT_PRT_DEBUG ; 
 int MPT_ROLE_TARGET ; 
 int /*<<< orphan*/  MPT_UNLOCK (struct mpt_softc*) ; 
 int /*<<< orphan*/  REQ_STATE_FREE ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cam_sim_path (int /*<<< orphan*/ *) ; 
 struct cam_devq* cam_simq_alloc (int) ; 
 int /*<<< orphan*/  cam_simq_free (struct cam_devq*) ; 
 int /*<<< orphan*/  fc_els_handler_id ; 
 int /*<<< orphan*/  mpt_action ; 
 scalar_t__ mpt_add_els_buffers (struct mpt_softc*) ; 
 int /*<<< orphan*/  mpt_cam_detach (struct mpt_softc*) ; 
 int /*<<< orphan*/  mpt_fc_els_reply_handler ; 
 TYPE_5__* mpt_get_request (struct mpt_softc*,scalar_t__) ; 
 int /*<<< orphan*/  mpt_lprt (struct mpt_softc*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mpt_poll ; 
 int /*<<< orphan*/  mpt_prt (struct mpt_softc*,char*) ; 
 int mpt_register_handler (struct mpt_softc*,int /*<<< orphan*/ ,TYPE_3__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpt_sata_pass_reply_handler ; 
 int /*<<< orphan*/  mpt_scsi_reply_handler ; 
 int /*<<< orphan*/  mpt_scsi_tgt_reply_handler ; 
 int /*<<< orphan*/  mpt_scsi_tmf_reply_handler ; 
 void* mpt_sim_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct mpt_softc*,int,int,struct cam_devq*) ; 
 scalar_t__ mpt_spawn_recovery_thread (struct mpt_softc*) ; 
 int /*<<< orphan*/  sata_pass_handler_id ; 
 int /*<<< orphan*/  scsi_io_handler_id ; 
 int /*<<< orphan*/  scsi_tmf_handler_id ; 
 scalar_t__ xpt_bus_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ xpt_create_path (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mpt_cam_attach(struct mpt_softc *mpt)
{
	struct cam_devq *devq;
	mpt_handler_t	 handler;
	int		 maxq;
	int		 error;

	MPT_LOCK(mpt);
	TAILQ_INIT(&mpt->request_timeout_list);
	maxq = (mpt->ioc_facts.GlobalCredits < MPT_MAX_REQUESTS(mpt))?
	    mpt->ioc_facts.GlobalCredits : MPT_MAX_REQUESTS(mpt);

	handler.reply_handler = mpt_scsi_reply_handler;
	error = mpt_register_handler(mpt, MPT_HANDLER_REPLY, handler,
				     &scsi_io_handler_id);
	if (error != 0) {
		MPT_UNLOCK(mpt);
		goto cleanup;
	}

	handler.reply_handler = mpt_scsi_tmf_reply_handler;
	error = mpt_register_handler(mpt, MPT_HANDLER_REPLY, handler,
				     &scsi_tmf_handler_id);
	if (error != 0) {
		MPT_UNLOCK(mpt);
		goto cleanup;
	}

	/*
	 * If we're fibre channel and could support target mode, we register
	 * an ELS reply handler and give it resources.
	 */
	if (mpt->is_fc && (mpt->role & MPT_ROLE_TARGET) != 0) {
		handler.reply_handler = mpt_fc_els_reply_handler;
		error = mpt_register_handler(mpt, MPT_HANDLER_REPLY, handler,
		    &fc_els_handler_id);
		if (error != 0) {
			MPT_UNLOCK(mpt);
			goto cleanup;
		}
		if (mpt_add_els_buffers(mpt) == FALSE) {
			error = ENOMEM;
			MPT_UNLOCK(mpt);
			goto cleanup;
		}
		maxq -= mpt->els_cmds_allocated;
	}

	/*
	 * If we support target mode, we register a reply handler for it,
	 * but don't add command resources until we actually enable target
	 * mode.
	 */
	if (mpt->is_fc && (mpt->role & MPT_ROLE_TARGET) != 0) {
		handler.reply_handler = mpt_scsi_tgt_reply_handler;
		error = mpt_register_handler(mpt, MPT_HANDLER_REPLY, handler,
		    &mpt->scsi_tgt_handler_id);
		if (error != 0) {
			MPT_UNLOCK(mpt);
			goto cleanup;
		}
	}

	if (mpt->is_sas) {
		handler.reply_handler = mpt_sata_pass_reply_handler;
		error = mpt_register_handler(mpt, MPT_HANDLER_REPLY, handler,
		    &sata_pass_handler_id);
		if (error != 0) {
			MPT_UNLOCK(mpt);
			goto cleanup;
		}
	}

	/*
	 * We keep one request reserved for timeout TMF requests.
	 */
	mpt->tmf_req = mpt_get_request(mpt, FALSE);
	if (mpt->tmf_req == NULL) {
		mpt_prt(mpt, "Unable to allocate dedicated TMF request!\n");
		error = ENOMEM;
		MPT_UNLOCK(mpt);
		goto cleanup;
	}

	/*
	 * Mark the request as free even though not on the free list.
	 * There is only one TMF request allowed to be outstanding at
	 * a time and the TMF routines perform their own allocation
	 * tracking using the standard state flags.
	 */
	mpt->tmf_req->state = REQ_STATE_FREE;
	maxq--;

	/*
	 * The rest of this is CAM foo, for which we need to drop our lock
	 */
	MPT_UNLOCK(mpt);

	if (mpt_spawn_recovery_thread(mpt) != 0) {
		mpt_prt(mpt, "Unable to spawn recovery thread!\n");
		error = ENOMEM;
		goto cleanup;
	}

	/*
	 * Create the device queue for our SIM(s).
	 */
	devq = cam_simq_alloc(maxq);
	if (devq == NULL) {
		mpt_prt(mpt, "Unable to allocate CAM SIMQ!\n");
		error = ENOMEM;
		goto cleanup;
	}

	/*
	 * Construct our SIM entry.
	 */
	mpt->sim =
	    mpt_sim_alloc(mpt_action, mpt_poll, "mpt", mpt, 1, maxq, devq);
	if (mpt->sim == NULL) {
		mpt_prt(mpt, "Unable to allocate CAM SIM!\n");
		cam_simq_free(devq);
		error = ENOMEM;
		goto cleanup;
	}

	/*
	 * Register exactly this bus.
	 */
	MPT_LOCK(mpt);
	if (xpt_bus_register(mpt->sim, mpt->dev, 0) != CAM_SUCCESS) {
		mpt_prt(mpt, "Bus registration Failed!\n");
		error = ENOMEM;
		MPT_UNLOCK(mpt);
		goto cleanup;
	}

	if (xpt_create_path(&mpt->path, NULL, cam_sim_path(mpt->sim),
	    CAM_TARGET_WILDCARD, CAM_LUN_WILDCARD) != CAM_REQ_CMP) {
		mpt_prt(mpt, "Unable to allocate Path!\n");
		error = ENOMEM;
		MPT_UNLOCK(mpt);
		goto cleanup;
	}
	MPT_UNLOCK(mpt);

	/*
	 * Only register a second bus for RAID physical
	 * devices if the controller supports RAID.
	 */
	if (mpt->ioc_page2 == NULL || mpt->ioc_page2->MaxPhysDisks == 0) {
		return (0);
	}

	/*
	 * Create a "bus" to export all hidden disks to CAM.
	 */
	mpt->phydisk_sim =
	    mpt_sim_alloc(mpt_action, mpt_poll, "mpt", mpt, 1, maxq, devq);
	if (mpt->phydisk_sim == NULL) {
		mpt_prt(mpt, "Unable to allocate Physical Disk CAM SIM!\n");
		error = ENOMEM;
		goto cleanup;
	}

	/*
	 * Register this bus.
	 */
	MPT_LOCK(mpt);
	if (xpt_bus_register(mpt->phydisk_sim, mpt->dev, 1) !=
	    CAM_SUCCESS) {
		mpt_prt(mpt, "Physical Disk Bus registration Failed!\n");
		error = ENOMEM;
		MPT_UNLOCK(mpt);
		goto cleanup;
	}

	if (xpt_create_path(&mpt->phydisk_path, NULL,
	    cam_sim_path(mpt->phydisk_sim),
	    CAM_TARGET_WILDCARD, CAM_LUN_WILDCARD) != CAM_REQ_CMP) {
		mpt_prt(mpt, "Unable to allocate Physical Disk Path!\n");
		error = ENOMEM;
		MPT_UNLOCK(mpt);
		goto cleanup;
	}
	MPT_UNLOCK(mpt);
	mpt_lprt(mpt, MPT_PRT_DEBUG, "attached cam\n");
	return (0);

cleanup:
	mpt_cam_detach(mpt);
	return (error);
}