#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  void* u_int ;
typedef  int /*<<< orphan*/  target_id_t ;
struct mpt_softc {scalar_t__ verbose; TYPE_2__* tmf_req; int /*<<< orphan*/  request_pending_list; } ;
typedef  int /*<<< orphan*/  lun_id_t ;
struct TYPE_12__ {int state; int index; int /*<<< orphan*/  serno; scalar_t__ req_vbuf; } ;
struct TYPE_11__ {int /*<<< orphan*/  MsgContext; void* TaskMsgContext; int /*<<< orphan*/  LUN; void* MsgFlags; void* TaskType; int /*<<< orphan*/  Function; void* Bus; int /*<<< orphan*/  TargetID; } ;
typedef  TYPE_1__ MSG_SCSI_TASK_MGMT ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_EXTLUN_BYTE_SWIZZLE (int /*<<< orphan*/ ) ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MPI_FUNCTION_SCSI_TASK_MGMT ; 
 int MPT_OK ; 
 scalar_t__ MPT_PRT_DEBUG ; 
 int /*<<< orphan*/  MPT_TMF_MAX_TIMEOUT ; 
 int REQ_STATE_ALLOCATED ; 
 int REQ_STATE_FREE ; 
 int REQ_STATE_QUEUED ; 
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  be64enc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htole32 (int) ; 
 int /*<<< orphan*/  links ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mpt_assign_serno (struct mpt_softc*,TYPE_2__*) ; 
 int /*<<< orphan*/  mpt_lprt (struct mpt_softc*,scalar_t__,char*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpt_print_request (TYPE_1__*) ; 
 scalar_t__ mpt_req_on_pending_list (struct mpt_softc*,TYPE_2__*) ; 
 int /*<<< orphan*/  mpt_reset (struct mpt_softc*,int /*<<< orphan*/ ) ; 
 int mpt_send_handshake_cmd (struct mpt_softc*,int,TYPE_1__*) ; 
 int mpt_wait_req (struct mpt_softc*,TYPE_2__*,int,int,int,int /*<<< orphan*/ ) ; 
 int scsi_tmf_handler_id ; 

__attribute__((used)) static int
mpt_scsi_send_tmf(struct mpt_softc *mpt, u_int type, u_int flags,
    u_int channel, target_id_t target, lun_id_t lun, u_int abort_ctx,
    int sleep_ok)
{
	MSG_SCSI_TASK_MGMT *tmf_req;
	int		    error;

	/*
	 * Wait for any current TMF request to complete.
	 * We're only allowed to issue one TMF at a time.
	 */
	error = mpt_wait_req(mpt, mpt->tmf_req, REQ_STATE_FREE, REQ_STATE_FREE,
	    sleep_ok, MPT_TMF_MAX_TIMEOUT);
	if (error != 0) {
		mpt_reset(mpt, TRUE);
		return (ETIMEDOUT);
	}

	mpt_assign_serno(mpt, mpt->tmf_req);
	mpt->tmf_req->state = REQ_STATE_ALLOCATED|REQ_STATE_QUEUED;

	tmf_req = (MSG_SCSI_TASK_MGMT *)mpt->tmf_req->req_vbuf;
	memset(tmf_req, 0, sizeof(*tmf_req));
	tmf_req->TargetID = target;
	tmf_req->Bus = channel;
	tmf_req->Function = MPI_FUNCTION_SCSI_TASK_MGMT;
	tmf_req->TaskType = type;
	tmf_req->MsgFlags = flags;
	tmf_req->MsgContext =
	    htole32(mpt->tmf_req->index | scsi_tmf_handler_id);
	be64enc(tmf_req->LUN, CAM_EXTLUN_BYTE_SWIZZLE(lun));
	tmf_req->TaskMsgContext = abort_ctx;

	mpt_lprt(mpt, MPT_PRT_DEBUG,
	    "Issuing TMF %p:%u with MsgContext of 0x%x\n", mpt->tmf_req,
	    mpt->tmf_req->serno, tmf_req->MsgContext);
	if (mpt->verbose > MPT_PRT_DEBUG) {
		mpt_print_request(tmf_req);
	}

	KASSERT(mpt_req_on_pending_list(mpt, mpt->tmf_req) == 0,
	    ("mpt_scsi_send_tmf: tmf_req already on pending list"));
	TAILQ_INSERT_HEAD(&mpt->request_pending_list, mpt->tmf_req, links);
	error = mpt_send_handshake_cmd(mpt, sizeof(*tmf_req), tmf_req);
	if (error != MPT_OK) {
		TAILQ_REMOVE(&mpt->request_pending_list, mpt->tmf_req, links);
		mpt->tmf_req->state = REQ_STATE_FREE;
		mpt_reset(mpt, TRUE);
	}
	return (error);
}