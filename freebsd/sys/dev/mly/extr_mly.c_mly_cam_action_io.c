#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct mly_softc {int /*<<< orphan*/  mly_qfrzn_cnt; TYPE_1__** mly_btl; } ;
struct TYPE_19__ {int value; int /*<<< orphan*/  scale; } ;
struct TYPE_17__ {int target; int channel; int /*<<< orphan*/  lun; } ;
struct TYPE_18__ {TYPE_6__ phys; } ;
struct TYPE_16__ {int disable_disconnect; int /*<<< orphan*/  data_direction; } ;
struct mly_command_scsi_small {int /*<<< orphan*/  cdb; int /*<<< orphan*/  cdb_length; int /*<<< orphan*/  maximum_sense_size; TYPE_8__ timeout; TYPE_7__ addr; int /*<<< orphan*/  data_size; TYPE_5__ command_control; int /*<<< orphan*/  opcode; } ;
struct mly_command {TYPE_4__* mc_packet; int /*<<< orphan*/  mc_flags; struct ccb_scsiio* mc_private; int /*<<< orphan*/  mc_complete; int /*<<< orphan*/  mc_length; struct ccb_scsiio* mc_data; } ;
struct TYPE_14__ {TYPE_2__* entries; } ;
struct TYPE_20__ {int target_id; int status; int flags; int timeout; int /*<<< orphan*/  target_lun; TYPE_3__ sim_priv; } ;
struct TYPE_11__ {int /*<<< orphan*/  cdb_bytes; int /*<<< orphan*/  cdb_ptr; } ;
struct ccb_scsiio {TYPE_9__ ccb_h; int /*<<< orphan*/  cdb_len; TYPE_10__ cdb_io; int /*<<< orphan*/  sense_len; int /*<<< orphan*/  dxfer_len; } ;
struct cam_sim {int dummy; } ;
struct TYPE_15__ {struct mly_command_scsi_small scsi_small; } ;
struct TYPE_13__ {int field; } ;
struct TYPE_12__ {int mb_flags; } ;

/* Variables and functions */
 int CAM_CDB_PHYS ; 
 int CAM_CDB_POINTER ; 
 int CAM_DIR_MASK ; 
 int CAM_DIR_OUT ; 
 int CAM_DIS_DISCONNECT ; 
 int CAM_REQUEUE_REQ ; 
 void* CAM_REQ_CMP_ERR ; 
 int CAM_REQ_INPROG ; 
 int CAM_STATUS_MASK ; 
 int EINVAL ; 
 int /*<<< orphan*/  MDACMD_SCSI ; 
 int MLY_BTL_LOGICAL ; 
 int MLY_BTL_PHYSICAL ; 
 int MLY_BTL_PROTECTED ; 
 int /*<<< orphan*/  MLY_BUS_IS_VALID (struct mly_softc*,int) ; 
 int /*<<< orphan*/  MLY_CCB_WRITE ; 
 int /*<<< orphan*/  MLY_CMD_CCB ; 
 int /*<<< orphan*/  MLY_CMD_SCSI_SMALL_CDB ; 
 int /*<<< orphan*/  MLY_TIMEOUT_HOURS ; 
 int /*<<< orphan*/  MLY_TIMEOUT_MINUTES ; 
 int /*<<< orphan*/  MLY_TIMEOUT_SECONDS ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cam_sim_bus (struct cam_sim*) ; 
 struct mly_softc* cam_sim_softc (struct cam_sim*) ; 
 int /*<<< orphan*/  debug (int,char*,...) ; 
 int mly_alloc_command (struct mly_softc*,struct mly_command**) ; 
 int /*<<< orphan*/  mly_cam_complete ; 
 int mly_start (struct mly_command*) ; 
 int /*<<< orphan*/  xpt_freeze_simq (struct cam_sim*,int) ; 

__attribute__((used)) static int
mly_cam_action_io(struct cam_sim *sim, struct ccb_scsiio *csio)
{
    struct mly_softc			*sc = cam_sim_softc(sim);
    struct mly_command			*mc;
    struct mly_command_scsi_small	*ss;
    int					bus, target;
    int					error;

    bus = cam_sim_bus(sim);
    target = csio->ccb_h.target_id;

    debug(2, "XPT_SCSI_IO %d:%d:%d", bus, target, csio->ccb_h.target_lun);

    /* validate bus number */
    if (!MLY_BUS_IS_VALID(sc, bus)) {
	debug(0, " invalid bus %d", bus);
	csio->ccb_h.status = CAM_REQ_CMP_ERR;
    }

    /*  check for I/O attempt to a protected device */
    if (sc->mly_btl[bus][target].mb_flags & MLY_BTL_PROTECTED) {
	debug(2, "  device protected");
	csio->ccb_h.status = CAM_REQ_CMP_ERR;
    }

    /* check for I/O attempt to nonexistent device */
    if (!(sc->mly_btl[bus][target].mb_flags & (MLY_BTL_LOGICAL | MLY_BTL_PHYSICAL))) {
	debug(2, "  device %d:%d does not exist", bus, target);
	csio->ccb_h.status = CAM_REQ_CMP_ERR;
    }

    /* XXX increase if/when we support large SCSI commands */
    if (csio->cdb_len > MLY_CMD_SCSI_SMALL_CDB) {
	debug(0, "  command too large (%d > %d)", csio->cdb_len, MLY_CMD_SCSI_SMALL_CDB);
	csio->ccb_h.status = CAM_REQ_CMP_ERR;
    }

    /* check that the CDB pointer is not to a physical address */
    if ((csio->ccb_h.flags & CAM_CDB_POINTER) && (csio->ccb_h.flags & CAM_CDB_PHYS)) {
	debug(0, "  CDB pointer is to physical address");
	csio->ccb_h.status = CAM_REQ_CMP_ERR;
    }

    /* abandon aborted ccbs or those that have failed validation */
    if ((csio->ccb_h.status & CAM_STATUS_MASK) != CAM_REQ_INPROG) {
	debug(2, "abandoning CCB due to abort/validation failure");
	return(EINVAL);
    }

    /*
     * Get a command, or push the ccb back to CAM and freeze the queue.
     */
    if ((error = mly_alloc_command(sc, &mc))) {
	xpt_freeze_simq(sim, 1);
	csio->ccb_h.status |= CAM_REQUEUE_REQ;
	sc->mly_qfrzn_cnt++;
	return(error);
    }
    
    /* build the command */
    mc->mc_data = csio;
    mc->mc_length = csio->dxfer_len;
    mc->mc_complete = mly_cam_complete;
    mc->mc_private = csio;
    mc->mc_flags |= MLY_CMD_CCB;
    /* XXX This code doesn't set the data direction in mc_flags. */

    /* save the bus number in the ccb for later recovery XXX should be a better way */
     csio->ccb_h.sim_priv.entries[0].field = bus;

    /* build the packet for the controller */
    ss = &mc->mc_packet->scsi_small;
    ss->opcode = MDACMD_SCSI;
    if (csio->ccb_h.flags & CAM_DIS_DISCONNECT)
	ss->command_control.disable_disconnect = 1;
    if ((csio->ccb_h.flags & CAM_DIR_MASK) == CAM_DIR_OUT)
	ss->command_control.data_direction = MLY_CCB_WRITE;
    ss->data_size = csio->dxfer_len;
    ss->addr.phys.lun = csio->ccb_h.target_lun;
    ss->addr.phys.target = csio->ccb_h.target_id;
    ss->addr.phys.channel = bus;
    if (csio->ccb_h.timeout < (60 * 1000)) {
	ss->timeout.value = csio->ccb_h.timeout / 1000;
	ss->timeout.scale = MLY_TIMEOUT_SECONDS;
    } else if (csio->ccb_h.timeout < (60 * 60 * 1000)) {
	ss->timeout.value = csio->ccb_h.timeout / (60 * 1000);
	ss->timeout.scale = MLY_TIMEOUT_MINUTES;
    } else {
	ss->timeout.value = csio->ccb_h.timeout / (60 * 60 * 1000);	/* overflow? */
	ss->timeout.scale = MLY_TIMEOUT_HOURS;
    }
    ss->maximum_sense_size = csio->sense_len;
    ss->cdb_length = csio->cdb_len;
    if (csio->ccb_h.flags & CAM_CDB_POINTER) {
	bcopy(csio->cdb_io.cdb_ptr, ss->cdb, csio->cdb_len);
    } else {
	bcopy(csio->cdb_io.cdb_bytes, ss->cdb, csio->cdb_len);
    }

    /* give the command to the controller */
    if ((error = mly_start(mc))) {
	xpt_freeze_simq(sim, 1);
	csio->ccb_h.status |= CAM_REQUEUE_REQ;
	sc->mly_qfrzn_cnt++;
	return(error);
    }

    return(0);
}