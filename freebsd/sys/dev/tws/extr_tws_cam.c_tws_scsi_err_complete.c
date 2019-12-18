#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int status; scalar_t__ target_lun; } ;
struct TYPE_8__ {int* cdb_bytes; } ;
struct TYPE_10__ {int /*<<< orphan*/  scsi_status; int /*<<< orphan*/  sense_len; int /*<<< orphan*/  sense_data; TYPE_1__ cdb_io; } ;
union ccb {TYPE_7__ ccb_h; TYPE_3__ csio; } ;
typedef  int /*<<< orphan*/  u_int8_t ;
struct tws_softc {int /*<<< orphan*/  q_lock; int /*<<< orphan*/  sim_lock; } ;
struct tws_request {struct tws_softc* sc; int /*<<< orphan*/  timeout; TYPE_6__* cmd_pkt; union ccb* ccb_ptr; } ;
struct TYPE_9__ {int /*<<< orphan*/  error; } ;
struct tws_command_header {int /*<<< orphan*/  sense_data; TYPE_2__ status_block; } ;
struct TYPE_11__ {int /*<<< orphan*/  status; } ;
struct TYPE_12__ {TYPE_4__ pkt_a; } ;
struct TYPE_13__ {TYPE_5__ cmd; } ;

/* Variables and functions */
 int CAM_AUTOSNS_VALID ; 
 int CAM_DEV_NOT_THERE ; 
 int CAM_REQ_CMP_ERR ; 
 int CAM_SCSI_STATUS_ERROR ; 
 int CAM_SEL_TIMEOUT ; 
 int CAM_SIM_QUEUED ; 
 int /*<<< orphan*/  TWS_BUSY_Q ; 
 int /*<<< orphan*/  TWS_ERROR_LOGICAL_UNIT_NOT_SUPPORTED ; 
 int /*<<< orphan*/  TWS_ERROR_NOT_SUPPORTED ; 
 int /*<<< orphan*/  TWS_ERROR_UNIT_OFFLINE ; 
 int /*<<< orphan*/  TWS_FREE_Q ; 
 int /*<<< orphan*/  TWS_SENSE_DATA_LENGTH ; 
 int /*<<< orphan*/  TWS_TRACE_DEBUG (struct tws_softc*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tws_q_insert_tail (struct tws_softc*,struct tws_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tws_q_remove_request (struct tws_softc*,struct tws_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tws_unmap_request (struct tws_softc*,struct tws_request*) ; 
 int /*<<< orphan*/  xpt_done (union ccb*) ; 

__attribute__((used)) static void
tws_scsi_err_complete(struct tws_request *req, struct tws_command_header *hdr)
{ 
    u_int8_t *sense_data;
    struct tws_softc *sc = req->sc;
    union ccb *ccb = req->ccb_ptr;

    TWS_TRACE_DEBUG(sc, "sbe, cmd_status", hdr->status_block.error, 
                                 req->cmd_pkt->cmd.pkt_a.status);
    if ( hdr->status_block.error == TWS_ERROR_LOGICAL_UNIT_NOT_SUPPORTED ||
         hdr->status_block.error == TWS_ERROR_UNIT_OFFLINE ) {

        if ( ccb->ccb_h.target_lun ) {
            TWS_TRACE_DEBUG(sc, "invalid lun error",0,0);
            ccb->ccb_h.status |= CAM_DEV_NOT_THERE;
        } else {
            TWS_TRACE_DEBUG(sc, "invalid target error",0,0);
            ccb->ccb_h.status |= CAM_SEL_TIMEOUT;
        }

    } else {
        TWS_TRACE_DEBUG(sc, "scsi status  error",0,0);
        ccb->ccb_h.status |= CAM_SCSI_STATUS_ERROR;
        if (((ccb->csio.cdb_io.cdb_bytes[0] == 0x1A) && 
              (hdr->status_block.error == TWS_ERROR_NOT_SUPPORTED))) {
            ccb->ccb_h.status |= CAM_SCSI_STATUS_ERROR | CAM_AUTOSNS_VALID;
            TWS_TRACE_DEBUG(sc, "page mode not supported",0,0);
        }
    }

    /* if there were no error simply mark complete error */ 
    if (ccb->ccb_h.status == 0)
        ccb->ccb_h.status = CAM_REQ_CMP_ERR;

    sense_data = (u_int8_t *)&ccb->csio.sense_data;
    if (sense_data) {
        memcpy(sense_data, hdr->sense_data, TWS_SENSE_DATA_LENGTH );
        ccb->csio.sense_len = TWS_SENSE_DATA_LENGTH;
        ccb->ccb_h.status |= CAM_AUTOSNS_VALID;
    }
    ccb->csio.scsi_status = req->cmd_pkt->cmd.pkt_a.status;
 
    ccb->ccb_h.status &= ~CAM_SIM_QUEUED;
    mtx_lock(&sc->sim_lock);
    xpt_done(ccb);
    mtx_unlock(&sc->sim_lock);

    callout_stop(&req->timeout);
    tws_unmap_request(req->sc, req);
    mtx_lock(&sc->q_lock);
    tws_q_remove_request(sc, req, TWS_BUSY_Q);
    tws_q_insert_tail(sc, req, TWS_FREE_Q);
    mtx_unlock(&sc->q_lock);
}