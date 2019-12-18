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
typedef  union ccb {int dummy; } ccb ;
struct scsi_sense_data {int dummy; } ;
struct ciss_softc {int ciss_flags; } ;
struct ciss_request {scalar_t__ cr_private; struct ciss_command* cr_cc; struct ciss_softc* cr_sc; } ;
struct ciss_error_info {int /*<<< orphan*/ * sense_info; int /*<<< orphan*/  residual_count; scalar_t__ sense_length; } ;
struct ciss_command {int /*<<< orphan*/ * sg; } ;
struct TYPE_2__ {int status; int /*<<< orphan*/  path; } ;
struct ccb_scsiio {int scsi_status; TYPE_1__ ccb_h; scalar_t__ sense_resid; scalar_t__ sense_len; int /*<<< orphan*/  resid; int /*<<< orphan*/  sense_data; } ;

/* Variables and functions */
 int CAM_AUTOSNS_VALID ; 
 int CAM_RELEASE_SIMQ ; 
 int CAM_REQ_CMP ; 
 int CAM_REQ_CMP_ERR ; 
 int CAM_SCSI_BUSY ; 
 int CAM_SCSI_STATUS_ERROR ; 
 int CISS_FLAG_BUSY ; 
#define  SCSI_STATUS_BUSY 130 
#define  SCSI_STATUS_CHECK_COND 129 
#define  SCSI_STATUS_OK 128 
 int /*<<< orphan*/  SSD_FULL_SIZE ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ciss_cam_complete_fixup (struct ciss_softc*,struct ccb_scsiio*) ; 
 int /*<<< orphan*/  ciss_release_request (struct ciss_request*) ; 
 int /*<<< orphan*/  ciss_report_request (struct ciss_request*,int*,int*) ; 
 int /*<<< orphan*/  debug (int,char*,...) ; 
 int /*<<< orphan*/  debug_called (int) ; 
 int scsi_get_sense_key (struct scsi_sense_data*,scalar_t__,int) ; 
 int /*<<< orphan*/  xpt_done (union ccb*) ; 
 int /*<<< orphan*/  xpt_path_sim (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_release_simq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ciss_cam_complete(struct ciss_request *cr)
{
    struct ciss_softc		*sc;
    struct ciss_command		*cc;
    struct ciss_error_info	*ce;
    struct ccb_scsiio		*csio;
    int				scsi_status;
    int				command_status;

    debug_called(2);

    sc = cr->cr_sc;
    cc = cr->cr_cc;
    ce = (struct ciss_error_info *)&(cc->sg[0]);
    csio = (struct ccb_scsiio *)cr->cr_private;

    /*
     * Extract status values from request.
     */
    ciss_report_request(cr, &command_status, &scsi_status);
    csio->scsi_status = scsi_status;

    /*
     * Handle specific SCSI status values.
     */
    switch(scsi_status) {
	/* no status due to adapter error */
    case -1:
	debug(0, "adapter error");
	csio->ccb_h.status |= CAM_REQ_CMP_ERR;
	break;

	/* no status due to command completed OK */
    case SCSI_STATUS_OK:		/* CISS_SCSI_STATUS_GOOD */
	debug(2, "SCSI_STATUS_OK");
	csio->ccb_h.status |= CAM_REQ_CMP;
	break;

	/* check condition, sense data included */
    case SCSI_STATUS_CHECK_COND:	/* CISS_SCSI_STATUS_CHECK_CONDITION */
	debug(0, "SCSI_STATUS_CHECK_COND  sense size %d  resid %d\n",
	      ce->sense_length, ce->residual_count);
	bzero(&csio->sense_data, SSD_FULL_SIZE);
	bcopy(&ce->sense_info[0], &csio->sense_data, ce->sense_length);
	if (csio->sense_len > ce->sense_length)
		csio->sense_resid = csio->sense_len - ce->sense_length;
	else
		csio->sense_resid = 0;
	csio->resid = ce->residual_count;
	csio->ccb_h.status |= CAM_SCSI_STATUS_ERROR | CAM_AUTOSNS_VALID;
#ifdef CISS_DEBUG
	{
	    struct scsi_sense_data	*sns = (struct scsi_sense_data *)&ce->sense_info[0];
	    debug(0, "sense key %x", scsi_get_sense_key(sns, csio->sense_len -
		  csio->sense_resid, /*show_errors*/ 1));
	}
#endif
	break;

    case SCSI_STATUS_BUSY:		/* CISS_SCSI_STATUS_BUSY */
	debug(0, "SCSI_STATUS_BUSY");
	csio->ccb_h.status |= CAM_SCSI_BUSY;
	break;

    default:
	debug(0, "unknown status 0x%x", csio->scsi_status);
	csio->ccb_h.status |= CAM_REQ_CMP_ERR;
	break;
    }

    /* handle post-command fixup */
    ciss_cam_complete_fixup(sc, csio);

    ciss_release_request(cr);
    if (sc->ciss_flags & CISS_FLAG_BUSY) {
	sc->ciss_flags &= ~CISS_FLAG_BUSY;
	if (csio->ccb_h.status & CAM_RELEASE_SIMQ)
	    xpt_release_simq(xpt_path_sim(csio->ccb_h.path), 0);
	else
	    csio->ccb_h.status |= CAM_RELEASE_SIMQ;
    }
    xpt_done((union ccb *)csio);
}