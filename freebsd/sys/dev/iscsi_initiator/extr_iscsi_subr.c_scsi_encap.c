#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct ccb_hdr {int flags; int /*<<< orphan*/  status; int /*<<< orphan*/  target_lun; TYPE_6__* spriv_ptr0; } ;
struct TYPE_19__ {int /*<<< orphan*/  cdb_bytes; int /*<<< orphan*/  cdb_ptr; } ;
struct ccb_scsiio {int tag_action; int cdb_len; int /*<<< orphan*/  dxfer_len; TYPE_3__ cdb_io; } ;
union ccb {struct ccb_hdr ccb_h; struct ccb_scsiio csio; } ;
typedef  int /*<<< orphan*/  u_char ;
struct cam_sim {int dummy; } ;
struct TYPE_20__ {int F; int W; int R; int /*<<< orphan*/  edtlen; int /*<<< orphan*/  cdb; int /*<<< orphan*/  lun; void* attr; int /*<<< orphan*/  opcode; } ;
typedef  TYPE_4__ scsi_req_t ;
struct TYPE_17__ {TYPE_4__ scsi_req; } ;
struct TYPE_18__ {TYPE_1__ ipdu; } ;
struct TYPE_21__ {union ccb* ccb; TYPE_2__ pdu; } ;
typedef  TYPE_5__ pduq_t ;
struct TYPE_22__ {TYPE_7__* isc; } ;
typedef  TYPE_6__ isc_session_t ;
struct TYPE_23__ {int /*<<< orphan*/  npdu_alloc; int /*<<< orphan*/  npdu_max; } ;

/* Variables and functions */
 int CAM_CDB_PHYS ; 
 int CAM_CDB_POINTER ; 
 int CAM_DIR_IN ; 
 int CAM_DIR_MASK ; 
 int CAM_DIR_OUT ; 
 int /*<<< orphan*/  CAM_REQ_INVALID ; 
 int /*<<< orphan*/  ISCSI_SCSI_CMD ; 
#define  MSG_ACA_TASK 131 
#define  MSG_HEAD_OF_Q_TAG 130 
#define  MSG_ORDERED_Q_TAG 129 
#define  MSG_SIMPLE_Q_TAG 128 
 int /*<<< orphan*/  M_NOWAIT ; 
 TYPE_6__* cam_sim_softc (struct cam_sim*) ; 
 int /*<<< orphan*/  debug (int,char*,TYPE_6__*) ; 
 int /*<<< orphan*/  debug_called (int) ; 
 int /*<<< orphan*/  dwl (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int hz ; 
 void* iSCSI_TASK_ACA ; 
 void* iSCSI_TASK_HOFQ ; 
 void* iSCSI_TASK_ORDER ; 
 void* iSCSI_TASK_SIMPLE ; 
 scalar_t__ isc_qout (TYPE_6__*,TYPE_5__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pause (char*,int) ; 
 TYPE_5__* pdu_alloc (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdu_free (TYPE_7__*,TYPE_5__*) ; 
 int /*<<< orphan*/  sdebug (int,char*,...) ; 
 int /*<<< orphan*/  tsleep (TYPE_7__*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  xdebug (char*,int,long) ; 

int
scsi_encap(struct cam_sim *sim, union ccb *ccb)
{
     isc_session_t	*sp = cam_sim_softc(sim);
     struct ccb_scsiio	*csio = &ccb->csio;
     struct ccb_hdr	*ccb_h = &ccb->ccb_h;
     pduq_t		*pq;
     scsi_req_t		*cmd;

     debug_called(8);

     debug(4, "ccb->sp=%p", ccb_h->spriv_ptr0);
     sp = ccb_h->spriv_ptr0;

     if((pq = pdu_alloc(sp->isc, M_NOWAIT)) == NULL) {
	  debug(2, "ccb->sp=%p", ccb_h->spriv_ptr0);
	  sdebug(1, "pdu_alloc failed sc->npdu_max=%d npdu_alloc=%d",
		 sp->isc->npdu_max, sp->isc->npdu_alloc);
	  while((pq = pdu_alloc(sp->isc, M_NOWAIT)) == NULL) {
	       sdebug(2, "waiting...");
#if __FreeBSD_version >= 700000
	       pause("isc_encap", 5*hz);
#else
	       tsleep(sp->isc, 0, "isc_encap", 5*hz);
#endif
	  }
     }
     cmd = &pq->pdu.ipdu.scsi_req;
     cmd->opcode = ISCSI_SCSI_CMD;
     cmd->F = 1;
#if 0
// this breaks at least Isilon's iscsi target.
     /*
      | map tag option, default is UNTAGGED
      */
     switch(csio->tag_action) {
     case MSG_SIMPLE_Q_TAG:	cmd->attr = iSCSI_TASK_SIMPLE;	break;
     case MSG_HEAD_OF_Q_TAG:	cmd->attr = iSCSI_TASK_HOFQ;	break;
     case MSG_ORDERED_Q_TAG:	cmd->attr = iSCSI_TASK_ORDER;	break;
     case MSG_ACA_TASK:		cmd->attr = iSCSI_TASK_ACA;	break;
     }
#else
     cmd->attr = iSCSI_TASK_SIMPLE;
#endif

     dwl(sp, ccb_h->target_lun, (u_char *)&cmd->lun);

     if((ccb_h->flags & CAM_CDB_POINTER) != 0) {
	  if((ccb_h->flags & CAM_CDB_PHYS) == 0) {
	       if(csio->cdb_len > 16) {
		    sdebug(3, "oversize cdb %d > 16", csio->cdb_len);
		    goto invalid;
	       }
	  }
	  else {
	       sdebug(3, "not phys");
	       goto invalid;
	  }
     }

     if(csio->cdb_len > sizeof(cmd->cdb))
	  xdebug("guevalt! %d > %ld", csio->cdb_len, (long)sizeof(cmd->cdb));

     memcpy(cmd->cdb,
	    ccb_h->flags & CAM_CDB_POINTER? csio->cdb_io.cdb_ptr: csio->cdb_io.cdb_bytes,
	    csio->cdb_len);

     cmd->W = (ccb->ccb_h.flags & CAM_DIR_MASK) == CAM_DIR_OUT;
     cmd->R = (ccb->ccb_h.flags & CAM_DIR_MASK) == CAM_DIR_IN;
     cmd->edtlen = htonl(csio->dxfer_len);

     pq->ccb = ccb;
     /*
      | place it in the out queue
      */
     if(isc_qout(sp, pq) == 0)
	  return 1; 
 invalid:
     ccb->ccb_h.status = CAM_REQ_INVALID;
     pdu_free(sp->isc, pq);

     return 0;
}