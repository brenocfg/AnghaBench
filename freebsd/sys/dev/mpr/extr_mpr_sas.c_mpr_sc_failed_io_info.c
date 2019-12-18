#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct mprsas_target {int /*<<< orphan*/  connector_name; int /*<<< orphan*/  encl_slot; int /*<<< orphan*/  encl_level; scalar_t__ encl_level_valid; } ;
struct mpr_softc {int mpr_debug; } ;
struct ccb_scsiio {int dummy; } ;
struct TYPE_3__ {int SCSIState; int SCSIStatus; int /*<<< orphan*/  ResponseInfo; int /*<<< orphan*/  DevHandle; int /*<<< orphan*/  IOCLogInfo; int /*<<< orphan*/  IOCStatus; } ;
typedef  TYPE_1__ Mpi2SCSIIOReply_t ;

/* Variables and functions */
 int MPI2_IOCSTATUS_MASK ; 
 int MPI2_SCSI_STATE_AUTOSENSE_VALID ; 
 int MPI2_SCSI_STATE_RESPONSE_INFO_VALID ; 
 int MPR_XINFO ; 
 int le16toh (int /*<<< orphan*/ ) ; 
 int le32toh (int /*<<< orphan*/ ) ; 
 char* mpr_describe_table (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mpr_dprint (struct mpr_softc*,int,char*,...) ; 
 int /*<<< orphan*/  mpr_iocstatus_string ; 
 int /*<<< orphan*/  mpr_scsi_status_string ; 
 int /*<<< orphan*/  mpr_scsi_taskmgmt_string ; 
 int /*<<< orphan*/  scsi_sense_print (struct ccb_scsiio*) ; 

__attribute__((used)) static void
mpr_sc_failed_io_info(struct mpr_softc *sc, struct ccb_scsiio *csio,
    Mpi2SCSIIOReply_t *mpi_reply, struct mprsas_target *targ)
{
	u32 response_info;
	u8 *response_bytes;
	u16 ioc_status = le16toh(mpi_reply->IOCStatus) &
	    MPI2_IOCSTATUS_MASK;
	u8 scsi_state = mpi_reply->SCSIState;
	u8 scsi_status = mpi_reply->SCSIStatus;
	char *desc_ioc_state = NULL;
	char *desc_scsi_status = NULL;
	u32 log_info = le32toh(mpi_reply->IOCLogInfo);
	
	if (log_info == 0x31170000)
		return;

	desc_ioc_state = mpr_describe_table(mpr_iocstatus_string,
	     ioc_status);
	desc_scsi_status = mpr_describe_table(mpr_scsi_status_string,
	    scsi_status);

	mpr_dprint(sc, MPR_XINFO, "\thandle(0x%04x), ioc_status(%s)(0x%04x)\n",
	    le16toh(mpi_reply->DevHandle), desc_ioc_state, ioc_status);
	if (targ->encl_level_valid) {
		mpr_dprint(sc, MPR_XINFO, "At enclosure level %d, slot %d, "
		    "connector name (%4s)\n", targ->encl_level, targ->encl_slot,
		    targ->connector_name);
	}
	
	/*
	 * We can add more detail about underflow data here
	 * TO-DO
	 */
	mpr_dprint(sc, MPR_XINFO, "\tscsi_status(%s)(0x%02x), "
	    "scsi_state %b\n", desc_scsi_status, scsi_status,
	    scsi_state, "\20" "\1AutosenseValid" "\2AutosenseFailed"
	    "\3NoScsiStatus" "\4Terminated" "\5Response InfoValid");

	if (sc->mpr_debug & MPR_XINFO &&
	    scsi_state & MPI2_SCSI_STATE_AUTOSENSE_VALID) {
		mpr_dprint(sc, MPR_XINFO, "-> Sense Buffer Data : Start :\n");
		scsi_sense_print(csio);
		mpr_dprint(sc, MPR_XINFO, "-> Sense Buffer Data : End :\n");
	}

	if (scsi_state & MPI2_SCSI_STATE_RESPONSE_INFO_VALID) {
		response_info = le32toh(mpi_reply->ResponseInfo);
		response_bytes = (u8 *)&response_info;
		mpr_dprint(sc, MPR_XINFO, "response code(0x%01x): %s\n",
		    response_bytes[0],
		    mpr_describe_table(mpr_scsi_taskmgmt_string,
		    response_bytes[0]));
	}
}