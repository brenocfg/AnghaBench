#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ccb_hdr {scalar_t__ target_id; int target_lun; int flags; int timeout; int /*<<< orphan*/  status; } ;
struct TYPE_5__ {int /*<<< orphan*/  cdb_bytes; int /*<<< orphan*/  cdb_ptr; } ;
struct ccb_scsiio {int cdb_len; TYPE_1__ cdb_io; } ;
union ccb {struct ccb_hdr ccb_h; struct ccb_scsiio csio; } ;
typedef  int u_int16_t ;
struct TYPE_8__ {int /*<<< orphan*/  scsi_ios; } ;
struct tws_softc {TYPE_4__ stats; int /*<<< orphan*/  sim_lock; } ;
struct tws_request {int request_id; int /*<<< orphan*/  timeout; union ccb* ccb_ptr; int /*<<< orphan*/  flags; union ccb* data; struct tws_command_packet* cmd_pkt; int /*<<< orphan*/  cb; int /*<<< orphan*/  type; } ;
struct TYPE_6__ {scalar_t__ unit; int sgl_offset; int lun_l4__req_id; int lun_h4__sgl_entries; int /*<<< orphan*/  cdb; scalar_t__ status; int /*<<< orphan*/  res__opcode; } ;
struct TYPE_7__ {TYPE_2__ pkt_a; } ;
struct tws_command_packet {TYPE_3__ cmd; } ;
typedef  int int32_t ;

/* Variables and functions */
 int CAM_CDB_PHYS ; 
 int CAM_CDB_POINTER ; 
 int CAM_DIR_IN ; 
 int CAM_DIR_MASK ; 
 int CAM_DIR_NONE ; 
 int CAM_DIR_OUT ; 
 int /*<<< orphan*/  CAM_LUN_INVALID ; 
 int /*<<< orphan*/  CAM_REQUEUE_REQ ; 
 int /*<<< orphan*/  CAM_REQ_INVALID ; 
 int /*<<< orphan*/  CAM_SIM_QUEUED ; 
 int /*<<< orphan*/  CAM_TID_INVALID ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int SBT_1MS ; 
 int /*<<< orphan*/  TWS_DATA_CCB ; 
 int /*<<< orphan*/  TWS_DIR_IN ; 
 int /*<<< orphan*/  TWS_DIR_NONE ; 
 int /*<<< orphan*/  TWS_DIR_OUT ; 
 int /*<<< orphan*/  TWS_FW_CMD_EXECUTE_SCSI ; 
 int TWS_MAX_NUM_LUNS ; 
 scalar_t__ TWS_MAX_NUM_UNITS ; 
 int /*<<< orphan*/  TWS_REQ_TYPE_SCSI_IO ; 
 int /*<<< orphan*/  TWS_TRACE (struct tws_softc*,char*,scalar_t__,int) ; 
 int /*<<< orphan*/  TWS_TRACE_DEBUG (struct tws_softc*,char*,scalar_t__,int) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  callout_reset_sbt (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tws_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct tws_request* tws_get_request (struct tws_softc*,int /*<<< orphan*/ ) ; 
 int tws_map_request (struct tws_softc*,struct tws_request*) ; 
 int /*<<< orphan*/  tws_scsi_complete ; 
 int /*<<< orphan*/  tws_timeout ; 
 int /*<<< orphan*/  xpt_done (union ccb*) ; 

__attribute__((used)) static int32_t
tws_execute_scsi(struct tws_softc *sc, union ccb *ccb)
{
    struct tws_command_packet *cmd_pkt;
    struct tws_request *req;
    struct ccb_hdr *ccb_h = &(ccb->ccb_h);
    struct ccb_scsiio *csio = &(ccb->csio);
    int error;
    u_int16_t lun;

    mtx_assert(&sc->sim_lock, MA_OWNED);
    if (ccb_h->target_id >= TWS_MAX_NUM_UNITS) {
        TWS_TRACE_DEBUG(sc, "traget id too big", ccb_h->target_id, ccb_h->target_lun);
        ccb_h->status |= CAM_TID_INVALID;
        xpt_done(ccb);
        return(0);
    }
    if (ccb_h->target_lun >= TWS_MAX_NUM_LUNS) {
        TWS_TRACE_DEBUG(sc, "target lun 2 big", ccb_h->target_id, ccb_h->target_lun);
        ccb_h->status |= CAM_LUN_INVALID;
        xpt_done(ccb);
        return(0);
    }

    if(ccb_h->flags & CAM_CDB_PHYS) {
        TWS_TRACE_DEBUG(sc, "cdb phy", ccb_h->target_id, ccb_h->target_lun);
        ccb_h->status = CAM_REQ_INVALID;
        xpt_done(ccb);
        return(0);
    }

    /*
     * We are going to work on this request.  Mark it as enqueued (though
     * we don't actually queue it...)
     */
    ccb_h->status |= CAM_SIM_QUEUED;

    req = tws_get_request(sc, TWS_REQ_TYPE_SCSI_IO);
    if ( !req ) {
        TWS_TRACE_DEBUG(sc, "no reqs", ccb_h->target_id, ccb_h->target_lun);
        ccb_h->status |= CAM_REQUEUE_REQ;
        xpt_done(ccb);
        return(0);
    }

    if((ccb_h->flags & CAM_DIR_MASK) != CAM_DIR_NONE) {
        if(ccb_h->flags & CAM_DIR_IN)
            req->flags |= TWS_DIR_IN;
        if(ccb_h->flags & CAM_DIR_OUT)
            req->flags |= TWS_DIR_OUT;
    } else {
        req->flags = TWS_DIR_NONE; /* no data */
    }

    req->type = TWS_REQ_TYPE_SCSI_IO;
    req->cb = tws_scsi_complete;

    cmd_pkt = req->cmd_pkt;
    /* cmd_pkt->hdr.header_desc.size_header = 128; */
    cmd_pkt->cmd.pkt_a.res__opcode = TWS_FW_CMD_EXECUTE_SCSI;
    cmd_pkt->cmd.pkt_a.unit = ccb_h->target_id;
    cmd_pkt->cmd.pkt_a.status = 0;
    cmd_pkt->cmd.pkt_a.sgl_offset = 16;

    /* lower nibble */
    lun = ccb_h->target_lun & 0XF;
    lun = lun << 12;
    cmd_pkt->cmd.pkt_a.lun_l4__req_id = lun | req->request_id;
    /* upper nibble */
    lun = ccb_h->target_lun & 0XF0;
    lun = lun << 8;
    cmd_pkt->cmd.pkt_a.lun_h4__sgl_entries = lun;

#ifdef TWS_DEBUG 
    if ( csio->cdb_len > 16 ) 
         TWS_TRACE(sc, "cdb len too big", ccb_h->target_id, csio->cdb_len);
#endif

    if(ccb_h->flags & CAM_CDB_POINTER)
        bcopy(csio->cdb_io.cdb_ptr, cmd_pkt->cmd.pkt_a.cdb, csio->cdb_len);
    else
        bcopy(csio->cdb_io.cdb_bytes, cmd_pkt->cmd.pkt_a.cdb, csio->cdb_len);

    req->data = ccb;
    req->flags |= TWS_DATA_CCB;
    /* save ccb ptr */
    req->ccb_ptr = ccb;
    /* 
     * tws_map_load_data_callback will fill in the SGL,
     * and submit the I/O.
     */
    sc->stats.scsi_ios++;
    callout_reset_sbt(&req->timeout, SBT_1MS * ccb->ccb_h.timeout, 0,
      tws_timeout, req, 0);
    error = tws_map_request(sc, req);
    return(error);
}