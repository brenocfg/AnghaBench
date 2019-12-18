#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint16_t ;
typedef  scalar_t__ target_id_t ;
struct mpt_softc {TYPE_1__* tmf_req; scalar_t__ is_fc; } ;
typedef  scalar_t__ lun_id_t ;
struct TYPE_2__ {int ResponseCode; int /*<<< orphan*/  state; int /*<<< orphan*/  IOCStatus; } ;

/* Variables and functions */
 scalar_t__ CAM_LUN_WILDCARD ; 
 scalar_t__ CAM_TARGET_WILDCARD ; 
 int EIO ; 
 int ETIMEDOUT ; 
 int MPI_IOCSTATUS_MASK ; 
 int MPI_IOCSTATUS_SUCCESS ; 
 int /*<<< orphan*/  MPI_SCSITASKMGMT_MSGFLAGS_LIP_RESET_OPTION ; 
 int MPI_SCSITASKMGMT_RSP_TM_COMPLETE ; 
 int MPI_SCSITASKMGMT_RSP_TM_SUCCEEDED ; 
 int /*<<< orphan*/  MPI_SCSITASKMGMT_TASKTYPE_RESET_BUS ; 
 int /*<<< orphan*/  MPI_SCSITASKMGMT_TASKTYPE_TARGET_RESET ; 
 int /*<<< orphan*/  REQ_STATE_DONE ; 
 int /*<<< orphan*/  REQ_STATE_FREE ; 
 int /*<<< orphan*/  TRUE ; 
 int le16toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpt_prt (struct mpt_softc*,char*,...) ; 
 int /*<<< orphan*/  mpt_reset (struct mpt_softc*,int /*<<< orphan*/ ) ; 
 int mpt_scsi_send_tmf (struct mpt_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int mpt_wait_req (struct mpt_softc*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
mpt_bus_reset(struct mpt_softc *mpt, target_id_t tgt, lun_id_t lun,
    int sleep_ok)
{
	int   error;
	uint16_t status;
	uint8_t response;

	error = mpt_scsi_send_tmf(mpt,
	    (tgt != CAM_TARGET_WILDCARD || lun != CAM_LUN_WILDCARD) ?
	    MPI_SCSITASKMGMT_TASKTYPE_TARGET_RESET :
	    MPI_SCSITASKMGMT_TASKTYPE_RESET_BUS,
	    mpt->is_fc ? MPI_SCSITASKMGMT_MSGFLAGS_LIP_RESET_OPTION : 0,
	    0,	/* XXX How do I get the channel ID? */
	    tgt != CAM_TARGET_WILDCARD ? tgt : 0,
	    lun != CAM_LUN_WILDCARD ? lun : 0,
	    0, sleep_ok);

	if (error != 0) {
		/*
		 * mpt_scsi_send_tmf hard resets on failure, so no
		 * need to do so here.
		 */
		mpt_prt(mpt,
		    "mpt_bus_reset: mpt_scsi_send_tmf returned %d\n", error);
		return (EIO);
	}

	/* Wait for bus reset to be processed by the IOC. */
	error = mpt_wait_req(mpt, mpt->tmf_req, REQ_STATE_DONE,
	    REQ_STATE_DONE, sleep_ok, 5000);

	status = le16toh(mpt->tmf_req->IOCStatus);
	response = mpt->tmf_req->ResponseCode;
	mpt->tmf_req->state = REQ_STATE_FREE;

	if (error) {
		mpt_prt(mpt, "mpt_bus_reset: Reset timed-out. "
		    "Resetting controller.\n");
		mpt_reset(mpt, TRUE);
		return (ETIMEDOUT);
	}

	if ((status & MPI_IOCSTATUS_MASK) != MPI_IOCSTATUS_SUCCESS) {
		mpt_prt(mpt, "mpt_bus_reset: TMF IOC Status 0x%x. "
		    "Resetting controller.\n", status);
		mpt_reset(mpt, TRUE);
		return (EIO);
	}

	if (response != MPI_SCSITASKMGMT_RSP_TM_SUCCEEDED &&
	    response != MPI_SCSITASKMGMT_RSP_TM_COMPLETE) {
		mpt_prt(mpt, "mpt_bus_reset: TMF Response 0x%x. "
		    "Resetting controller.\n", response);
		mpt_reset(mpt, TRUE);
		return (EIO);
	}
	return (0);
}