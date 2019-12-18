#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_47__   TYPE_9__ ;
typedef  struct TYPE_46__   TYPE_8__ ;
typedef  struct TYPE_45__   TYPE_7__ ;
typedef  struct TYPE_44__   TYPE_6__ ;
typedef  struct TYPE_43__   TYPE_5__ ;
typedef  struct TYPE_42__   TYPE_4__ ;
typedef  struct TYPE_41__   TYPE_3__ ;
typedef  struct TYPE_40__   TYPE_2__ ;
typedef  struct TYPE_39__   TYPE_1__ ;
typedef  struct TYPE_38__   TYPE_15__ ;
typedef  struct TYPE_37__   TYPE_14__ ;
typedef  struct TYPE_36__   TYPE_13__ ;
typedef  struct TYPE_35__   TYPE_12__ ;
typedef  struct TYPE_34__   TYPE_11__ ;
typedef  struct TYPE_33__   TYPE_10__ ;

/* Type definitions */
struct TYPE_43__ {int* cdb_ptr; int* cdb_bytes; } ;
struct ccb_hdr {int status; size_t target_id; scalar_t__ target_lun; int flags; } ;
struct ccb_scsiio {int tag_action; TYPE_5__ cdb_io; struct ccb_hdr ccb_h; } ;
struct TYPE_42__ {scalar_t__ func_code; int /*<<< orphan*/  path; } ;
union ccb {struct ccb_scsiio csio; TYPE_4__ ccb_h; } ;
typedef  int u_int ;
typedef  int u_char ;
typedef  TYPE_12__* tcb_p ;
struct cam_sim {int dummy; } ;
typedef  TYPE_13__* lcb_p ;
typedef  TYPE_14__* hcb_p ;
typedef  TYPE_15__* ccb_p ;
struct TYPE_47__ {void* restart; void* start; } ;
struct TYPE_45__ {scalar_t__ width; scalar_t__ period; scalar_t__ offset; scalar_t__ options; } ;
struct TYPE_44__ {scalar_t__ width; scalar_t__ period; scalar_t__ offset; scalar_t__ options; } ;
struct TYPE_46__ {TYPE_7__ goal; TYPE_6__ current; } ;
struct TYPE_41__ {void* size; void* addr; } ;
struct TYPE_40__ {int /*<<< orphan*/  uval; int /*<<< orphan*/  sval; int /*<<< orphan*/  wval; } ;
struct TYPE_39__ {int /*<<< orphan*/  sel_scntl4; int /*<<< orphan*/  sel_sxfer; int /*<<< orphan*/  sel_scntl3; int /*<<< orphan*/  sel_id; } ;
struct TYPE_33__ {TYPE_9__ go; } ;
struct TYPE_34__ {TYPE_3__ smsg; TYPE_1__ select; TYPE_10__ head; } ;
struct TYPE_38__ {int lun; int tag; int* scsi_smsg; int ext_sg; scalar_t__ ext_ofs; scalar_t__ extra_bytes; scalar_t__ host_flags; scalar_t__ xerr_status; int /*<<< orphan*/  ssss_status; scalar_t__ nego_status; int /*<<< orphan*/  host_status; int /*<<< orphan*/  actualquirks; TYPE_11__ phys; int /*<<< orphan*/  target; union ccb* cam_ccb; } ;
struct TYPE_37__ {size_t myaddr; TYPE_12__* target; } ;
struct TYPE_36__ {int current_flags; } ;
struct TYPE_35__ {int usrflags; int /*<<< orphan*/  quirks; TYPE_2__ head; int /*<<< orphan*/  nego_cp; TYPE_8__ tinfo; } ;

/* Variables and functions */
 int CAM_CDB_PHYS ; 
 int CAM_CDB_POINTER ; 
 int /*<<< orphan*/  CAM_DEBUG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CAM_DEBUG_TRACE ; 
 int /*<<< orphan*/  CAM_DEV_NOT_THERE ; 
 int CAM_REQ_INPROG ; 
 int /*<<< orphan*/  CAM_RESRC_UNAVAIL ; 
 int CAM_STATUS_MASK ; 
 int CAM_TAG_ACTION_VALID ; 
 int CCB_BA (TYPE_15__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HS_BUSY ; 
 int /*<<< orphan*/  HS_NEGOTIATE ; 
 int /*<<< orphan*/  MA_OWNED ; 
#define  M_HEAD_TAG 129 
 int M_IDENTIFY ; 
#define  M_ORDERED_TAG 128 
 int M_SIMPLE_TAG ; 
 int NO_TAG ; 
 int SCRIPTA_BA (TYPE_14__*,int /*<<< orphan*/ ) ; 
 scalar_t__ SYM_CONF_MAX_LUN ; 
 size_t SYM_CONF_MAX_TARGET ; 
 int SYM_DISC_ENABLED ; 
 int /*<<< orphan*/  SYM_LOCK_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYM_QUIRK_AUTOSAVE ; 
 int SYM_SCAN_BOOT_DISABLED ; 
 int SYM_SCAN_LUNS_DISABLED ; 
 int /*<<< orphan*/  S_ILLEGAL ; 
 scalar_t__ XPT_SCSI_IO ; 
 scalar_t__ cam_sim_softc (struct cam_sim*) ; 
 void* cpu_to_scr (int) ; 
 int /*<<< orphan*/  resel_dsa ; 
 int /*<<< orphan*/  scsi_smsg ; 
 int /*<<< orphan*/  select ; 
 int /*<<< orphan*/  sym_action2 (struct cam_sim*,union ccb*) ; 
 int /*<<< orphan*/  sym_free_ccb (TYPE_14__*,TYPE_15__*) ; 
 TYPE_15__* sym_get_ccb (TYPE_14__*,size_t,scalar_t__,int) ; 
 TYPE_13__* sym_lp (TYPE_12__*,scalar_t__) ; 
 int sym_prepare_nego (TYPE_14__*,TYPE_15__*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ sym_setup_cdb (TYPE_14__*,struct ccb_scsiio*,TYPE_15__*) ; 
 int /*<<< orphan*/  sym_setup_data_and_start (TYPE_14__*,struct ccb_scsiio*,TYPE_15__*) ; 
 int /*<<< orphan*/  sym_xpt_done (TYPE_14__*,union ccb*,TYPE_15__*) ; 
 int /*<<< orphan*/  sym_xpt_done2 (TYPE_14__*,union ccb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_done (union ccb*) ; 

__attribute__((used)) static void sym_action(struct cam_sim *sim, union ccb *ccb)
{
	hcb_p	np;
	tcb_p	tp;
	lcb_p	lp;
	ccb_p	cp;
	int 	tmp;
	u_char	idmsg, *msgptr;
	u_int   msglen;
	struct	ccb_scsiio *csio;
	struct	ccb_hdr  *ccb_h;

	CAM_DEBUG(ccb->ccb_h.path, CAM_DEBUG_TRACE, ("sym_action\n"));

	/*
	 *  Retrieve our controller data structure.
	 */
	np = (hcb_p) cam_sim_softc(sim);

	SYM_LOCK_ASSERT(MA_OWNED);

	/*
	 *  The common case is SCSI IO.
	 *  We deal with other ones elsewhere.
	 */
	if (ccb->ccb_h.func_code != XPT_SCSI_IO) {
		sym_action2(sim, ccb);
		return;
	}
	csio  = &ccb->csio;
	ccb_h = &csio->ccb_h;

	/*
	 *  Work around races.
	 */
	if ((ccb_h->status & CAM_STATUS_MASK) != CAM_REQ_INPROG) {
		xpt_done(ccb);
		return;
	}

	/*
	 *  Minimal checkings, so that we will not
	 *  go outside our tables.
	 */
	if (ccb_h->target_id   == np->myaddr ||
	    ccb_h->target_id   >= SYM_CONF_MAX_TARGET ||
	    ccb_h->target_lun  >= SYM_CONF_MAX_LUN) {
		sym_xpt_done2(np, ccb, CAM_DEV_NOT_THERE);
		return;
        }

	/*
	 *  Retrieve the target and lun descriptors.
	 */
	tp = &np->target[ccb_h->target_id];
	lp = sym_lp(tp, ccb_h->target_lun);

	/*
	 *  Complete the 1st INQUIRY command with error
	 *  condition if the device is flagged NOSCAN
	 *  at BOOT in the NVRAM. This may speed up
	 *  the boot and maintain coherency with BIOS
	 *  device numbering. Clearing the flag allows
	 *  user to rescan skipped devices later.
	 *  We also return error for devices not flagged
	 *  for SCAN LUNS in the NVRAM since some mono-lun
	 *  devices behave badly when asked for some non
	 *  zero LUN. Btw, this is an absolute hack.:-)
	 */
	if (!(ccb_h->flags & CAM_CDB_PHYS) &&
	    (0x12 == ((ccb_h->flags & CAM_CDB_POINTER) ?
		  csio->cdb_io.cdb_ptr[0] : csio->cdb_io.cdb_bytes[0]))) {
		if ((tp->usrflags & SYM_SCAN_BOOT_DISABLED) ||
		    ((tp->usrflags & SYM_SCAN_LUNS_DISABLED) &&
		     ccb_h->target_lun != 0)) {
			tp->usrflags &= ~SYM_SCAN_BOOT_DISABLED;
			sym_xpt_done2(np, ccb, CAM_DEV_NOT_THERE);
			return;
		}
	}

	/*
	 *  Get a control block for this IO.
	 */
	tmp = ((ccb_h->flags & CAM_TAG_ACTION_VALID) != 0);
	cp = sym_get_ccb(np, ccb_h->target_id, ccb_h->target_lun, tmp);
	if (!cp) {
		sym_xpt_done2(np, ccb, CAM_RESRC_UNAVAIL);
		return;
	}

	/*
	 *  Keep track of the IO in our CCB.
	 */
	cp->cam_ccb = ccb;

	/*
	 *  Build the IDENTIFY message.
	 */
	idmsg = M_IDENTIFY | cp->lun;
	if (cp->tag != NO_TAG || (lp && (lp->current_flags & SYM_DISC_ENABLED)))
		idmsg |= 0x40;

	msgptr = cp->scsi_smsg;
	msglen = 0;
	msgptr[msglen++] = idmsg;

	/*
	 *  Build the tag message if present.
	 */
	if (cp->tag != NO_TAG) {
		u_char order = csio->tag_action;

		switch(order) {
		case M_ORDERED_TAG:
			break;
		case M_HEAD_TAG:
			break;
		default:
			order = M_SIMPLE_TAG;
		}
		msgptr[msglen++] = order;

		/*
		 *  For less than 128 tags, actual tags are numbered
		 *  1,3,5,..2*MAXTAGS+1,since we may have to deal
		 *  with devices that have problems with #TAG 0 or too
		 *  great #TAG numbers. For more tags (up to 256),
		 *  we use directly our tag number.
		 */
#if SYM_CONF_MAX_TASK > (512/4)
		msgptr[msglen++] = cp->tag;
#else
		msgptr[msglen++] = (cp->tag << 1) + 1;
#endif
	}

	/*
	 *  Build a negotiation message if needed.
	 *  (nego_status is filled by sym_prepare_nego())
	 */
	cp->nego_status = 0;
	if (tp->tinfo.current.width   != tp->tinfo.goal.width  ||
	    tp->tinfo.current.period  != tp->tinfo.goal.period ||
	    tp->tinfo.current.offset  != tp->tinfo.goal.offset ||
	    tp->tinfo.current.options != tp->tinfo.goal.options) {
		if (!tp->nego_cp && lp)
			msglen += sym_prepare_nego(np, cp, 0, msgptr + msglen);
	}

	/*
	 *  Fill in our ccb
	 */

	/*
	 *  Startqueue
	 */
	cp->phys.head.go.start   = cpu_to_scr(SCRIPTA_BA (np, select));
	cp->phys.head.go.restart = cpu_to_scr(SCRIPTA_BA (np, resel_dsa));

	/*
	 *  select
	 */
	cp->phys.select.sel_id		= cp->target;
	cp->phys.select.sel_scntl3	= tp->head.wval;
	cp->phys.select.sel_sxfer	= tp->head.sval;
	cp->phys.select.sel_scntl4	= tp->head.uval;

	/*
	 *  message
	 */
	cp->phys.smsg.addr	= cpu_to_scr(CCB_BA (cp, scsi_smsg));
	cp->phys.smsg.size	= cpu_to_scr(msglen);

	/*
	 *  command
	 */
	if (sym_setup_cdb(np, csio, cp) < 0) {
		sym_xpt_done(np, ccb, cp);
		sym_free_ccb(np, cp);
		return;
	}

	/*
	 *  status
	 */
#if	0	/* Provision */
	cp->actualquirks	= tp->quirks;
#endif
	cp->actualquirks	= SYM_QUIRK_AUTOSAVE;
	cp->host_status		= cp->nego_status ? HS_NEGOTIATE : HS_BUSY;
	cp->ssss_status		= S_ILLEGAL;
	cp->xerr_status		= 0;
	cp->host_flags		= 0;
	cp->extra_bytes		= 0;

	/*
	 *  extreme data pointer.
	 *  shall be positive, so -1 is lower than lowest.:)
	 */
	cp->ext_sg  = -1;
	cp->ext_ofs = 0;

	/*
	 *  Build the data descriptor block
	 *  and start the IO.
	 */
	sym_setup_data_and_start(np, csio, cp);
}