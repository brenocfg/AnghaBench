#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_38__   TYPE_9__ ;
typedef  struct TYPE_37__   TYPE_8__ ;
typedef  struct TYPE_36__   TYPE_7__ ;
typedef  struct TYPE_35__   TYPE_6__ ;
typedef  struct TYPE_34__   TYPE_5__ ;
typedef  struct TYPE_33__   TYPE_4__ ;
typedef  struct TYPE_32__   TYPE_3__ ;
typedef  struct TYPE_31__   TYPE_2__ ;
typedef  struct TYPE_30__   TYPE_1__ ;
typedef  struct TYPE_29__   TYPE_11__ ;
typedef  struct TYPE_28__   TYPE_10__ ;

/* Type definitions */
typedef  int u_char ;
typedef  int u32 ;
typedef  TYPE_9__* tcb_p ;
typedef  TYPE_10__* hcb_p ;
typedef  TYPE_11__* ccb_p ;
struct TYPE_32__ {int options; int scsi_version; int /*<<< orphan*/  offset; int /*<<< orphan*/  width; } ;
struct TYPE_33__ {TYPE_3__ current; } ;
struct TYPE_38__ {TYPE_4__ tinfo; } ;
struct TYPE_35__ {void* start; } ;
struct TYPE_36__ {TYPE_6__ go; void* lastp; void* goalp; void* savep; } ;
struct TYPE_34__ {void* size; void* addr; } ;
struct TYPE_31__ {void* size; void* addr; } ;
struct TYPE_30__ {void* size; void* addr; } ;
struct TYPE_37__ {TYPE_7__ head; TYPE_5__ sense; TYPE_2__ cmd; TYPE_1__ smsg; } ;
struct TYPE_29__ {size_t target; int ssss_status; int host_flags; int lun; int sv_scsi_status; int* scsi_smsg2; int* sensecmd; int data_len; TYPE_8__ phys; int /*<<< orphan*/  extra_bytes; int /*<<< orphan*/  xerr_status; int /*<<< orphan*/  nego_status; int /*<<< orphan*/  host_status; int /*<<< orphan*/  actualquirks; void* startp; int /*<<< orphan*/  sns_bbuf; int /*<<< orphan*/  sv_resid; int /*<<< orphan*/  sv_xerr_status; } ;
struct TYPE_28__ {int squeue_ba; int /*<<< orphan*/ * last_cp; TYPE_9__* target; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_8_BIT ; 
 int CCB_BA (TYPE_11__*,int /*<<< orphan*/ ) ; 
 int HF_DATA_IN ; 
 int HF_SENSE ; 
 int /*<<< orphan*/  HS_BUSY ; 
 int /*<<< orphan*/  HS_NEGOTIATE ; 
 int INL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int M_IDENTIFY ; 
 int NS_PPR ; 
 int NS_SYNC ; 
 int NS_WIDE ; 
 int /*<<< orphan*/  OUTL_DSP (int) ; 
 int PPR_OPT_MASK ; 
 int /*<<< orphan*/  PRINT_ADDR (TYPE_11__*) ; 
 int SCRIPTA_BA (TYPE_10__*,int /*<<< orphan*/ ) ; 
 int SCRIPTB_BA (TYPE_10__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYM_LOCK_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYM_QUIRK_AUTOSAVE ; 
 int SYM_SNS_BBUF_LEN ; 
#define  S_BUSY 131 
#define  S_CHECK_COND 130 
 int S_ILLEGAL ; 
#define  S_QUEUE_FULL 129 
#define  S_TERMINATED 128 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int) ; 
 void* cpu_to_scr (int) ; 
 int /*<<< orphan*/  nc_scratcha ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  scsi_smsg2 ; 
 int /*<<< orphan*/  sdata_in ; 
 int /*<<< orphan*/  select ; 
 int /*<<< orphan*/  sensecmd ; 
 int /*<<< orphan*/  start ; 
 int /*<<< orphan*/  sym_complete_error (TYPE_10__*,TYPE_11__*) ; 
 int /*<<< orphan*/  sym_compute_residual (TYPE_10__*,TYPE_11__*) ; 
 int /*<<< orphan*/  sym_dequeue_from_squeue (TYPE_10__*,int,size_t,int,int) ; 
 int /*<<< orphan*/  sym_flush_comp_queue (TYPE_10__*,int /*<<< orphan*/ ) ; 
 int sym_prepare_nego (TYPE_10__*,TYPE_11__*,int,int*) ; 
 int /*<<< orphan*/  sym_put_start_queue (TYPE_10__*,TYPE_11__*) ; 
 int sym_verbose ; 
 int vtobus (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sym_sir_bad_scsi_status(hcb_p np, ccb_p cp)
{
	tcb_p tp	= &np->target[cp->target];
	u32		startp;
	u_char		s_status = cp->ssss_status;
	u_char		h_flags  = cp->host_flags;
	int		msglen;
	int		nego;
	int		i;

	SYM_LOCK_ASSERT(MA_OWNED);

	/*
	 *  Compute the index of the next job to start from SCRIPTS.
	 */
	i = (INL (nc_scratcha) - np->squeue_ba) / 4;

	/*
	 *  The last CCB queued used for IARB hint may be
	 *  no longer relevant. Forget it.
	 */
#ifdef SYM_CONF_IARB_SUPPORT
	if (np->last_cp)
		np->last_cp = NULL;
#endif

	/*
	 *  Now deal with the SCSI status.
	 */
	switch(s_status) {
	case S_BUSY:
	case S_QUEUE_FULL:
		if (sym_verbose >= 2) {
			PRINT_ADDR(cp);
			printf (s_status == S_BUSY ? "BUSY" : "QUEUE FULL\n");
		}
	default:	/* S_INT, S_INT_COND_MET, S_CONFLICT */
		sym_complete_error (np, cp);
		break;
	case S_TERMINATED:
	case S_CHECK_COND:
		/*
		 *  If we get an SCSI error when requesting sense, give up.
		 */
		if (h_flags & HF_SENSE) {
			sym_complete_error (np, cp);
			break;
		}

		/*
		 *  Dequeue all queued CCBs for that device not yet started,
		 *  and restart the SCRIPTS processor immediately.
		 */
		(void) sym_dequeue_from_squeue(np, i, cp->target, cp->lun, -1);
		OUTL_DSP (SCRIPTA_BA (np, start));

 		/*
		 *  Save some info of the actual IO.
		 *  Compute the data residual.
		 */
		cp->sv_scsi_status = cp->ssss_status;
		cp->sv_xerr_status = cp->xerr_status;
		cp->sv_resid = sym_compute_residual(np, cp);

		/*
		 *  Prepare all needed data structures for
		 *  requesting sense data.
		 */

		/*
		 *  identify message
		 */
		cp->scsi_smsg2[0] = M_IDENTIFY | cp->lun;
		msglen = 1;

		/*
		 *  If we are currently using anything different from
		 *  async. 8 bit data transfers with that target,
		 *  start a negotiation, since the device may want
		 *  to report us a UNIT ATTENTION condition due to
		 *  a cause we currently ignore, and we donnot want
		 *  to be stuck with WIDE and/or SYNC data transfer.
		 *
		 *  cp->nego_status is filled by sym_prepare_nego().
		 */
		cp->nego_status = 0;
		nego = 0;
		if	(tp->tinfo.current.options & PPR_OPT_MASK)
			nego = NS_PPR;
		else if	(tp->tinfo.current.width != BUS_8_BIT)
			nego = NS_WIDE;
		else if (tp->tinfo.current.offset != 0)
			nego = NS_SYNC;
		if (nego)
			msglen +=
			sym_prepare_nego (np,cp, nego, &cp->scsi_smsg2[msglen]);
		/*
		 *  Message table indirect structure.
		 */
		cp->phys.smsg.addr	= cpu_to_scr(CCB_BA (cp, scsi_smsg2));
		cp->phys.smsg.size	= cpu_to_scr(msglen);

		/*
		 *  sense command
		 */
		cp->phys.cmd.addr	= cpu_to_scr(CCB_BA (cp, sensecmd));
		cp->phys.cmd.size	= cpu_to_scr(6);

		/*
		 *  patch requested size into sense command
		 */
		cp->sensecmd[0]		= 0x03;
		cp->sensecmd[1]		= cp->lun << 5;
		if (tp->tinfo.current.scsi_version > 2 || cp->lun > 7)
			cp->sensecmd[1]	= 0;
		cp->sensecmd[4]		= SYM_SNS_BBUF_LEN;
		cp->data_len		= SYM_SNS_BBUF_LEN;

		/*
		 *  sense data
		 */
		bzero(cp->sns_bbuf, SYM_SNS_BBUF_LEN);
		cp->phys.sense.addr	= cpu_to_scr(vtobus(cp->sns_bbuf));
		cp->phys.sense.size	= cpu_to_scr(SYM_SNS_BBUF_LEN);

		/*
		 *  requeue the command.
		 */
		startp = SCRIPTB_BA (np, sdata_in);

		cp->phys.head.savep	= cpu_to_scr(startp);
		cp->phys.head.goalp	= cpu_to_scr(startp + 16);
		cp->phys.head.lastp	= cpu_to_scr(startp);
		cp->startp	= cpu_to_scr(startp);

		cp->actualquirks = SYM_QUIRK_AUTOSAVE;
		cp->host_status	= cp->nego_status ? HS_NEGOTIATE : HS_BUSY;
		cp->ssss_status = S_ILLEGAL;
		cp->host_flags	= (HF_SENSE|HF_DATA_IN);
		cp->xerr_status = 0;
		cp->extra_bytes = 0;

		cp->phys.head.go.start = cpu_to_scr(SCRIPTA_BA (np, select));

		/*
		 *  Requeue the command.
		 */
		sym_put_start_queue(np, cp);

		/*
		 *  Give back to upper layer everything we have dequeued.
		 */
		sym_flush_comp_queue(np, 0);
		break;
	}
}