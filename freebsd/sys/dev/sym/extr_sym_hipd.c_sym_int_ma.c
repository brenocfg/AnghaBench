#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
typedef  int u_char ;
typedef  int u32 ;
struct TYPE_16__ {int addr; int size; } ;
struct sym_pmc {int ret; TYPE_2__ sg; } ;
typedef  TYPE_5__* hcb_p ;
typedef  TYPE_6__* ccb_p ;
struct TYPE_15__ {void* size; void* addr; } ;
struct TYPE_17__ {int sel_scntl3; } ;
struct TYPE_18__ {TYPE_1__ wresid; TYPE_3__ select; struct sym_pmc pm1; struct sym_pmc pm0; } ;
struct TYPE_20__ {int lun; int /*<<< orphan*/  host_status; int /*<<< orphan*/  tag; TYPE_4__ phys; } ;
struct TYPE_19__ {int features; int rv_ctest3; int scripta_ba; int scripta_sz; int scriptb_ba; int scriptb_sz; int* msgout; scalar_t__ scriptb0; scalar_t__ scripta0; } ;

/* Variables and functions */
 int CLF ; 
 int CSF ; 
 int DEBUG_FLAGS ; 
 int DEBUG_PHASE ; 
 int DEBUG_TINY ; 
 int DFS ; 
 int EWS ; 
 int FE_C10 ; 
 int FE_DFBC ; 
 int HF_ACT_PM ; 
 int HF_DP_SAVED ; 
 int HF_IN_PM0 ; 
 int HF_IN_PM1 ; 
 int /*<<< orphan*/  HF_PRT ; 
 int /*<<< orphan*/  HS_BUSY ; 
 int INB (int /*<<< orphan*/ ) ; 
 int INL (int /*<<< orphan*/ ) ; 
 int INW (int /*<<< orphan*/ ) ; 
 int M_IDENTIFY ; 
 int /*<<< orphan*/  NO_TAG ; 
 int OLF ; 
 int OLF1 ; 
 int ORF ; 
 int ORF1 ; 
 int /*<<< orphan*/  OUTB (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OUTL (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OUTL_DSP (int) ; 
 int /*<<< orphan*/  PRINT_ADDR (TYPE_6__*) ; 
 int SCRIPTA_BA (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int SCRIPTB_BA (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int TE ; 
 int WSR ; 
 int /*<<< orphan*/  clrack ; 
 void* cpu_to_scr (int) ; 
 int /*<<< orphan*/  dispatch ; 
 int /*<<< orphan*/  ident_break ; 
 int /*<<< orphan*/  ident_break_atn ; 
 int /*<<< orphan*/  nc_ctest3 ; 
 int /*<<< orphan*/  nc_dbc ; 
 int /*<<< orphan*/  nc_dfbc ; 
 int /*<<< orphan*/  nc_dfifo ; 
 int /*<<< orphan*/  nc_dsa ; 
 int /*<<< orphan*/  nc_dsp ; 
 int /*<<< orphan*/  nc_sbcl ; 
 int /*<<< orphan*/  nc_scntl2 ; 
 int /*<<< orphan*/  nc_sstat0 ; 
 int /*<<< orphan*/  nc_sstat2 ; 
 int /*<<< orphan*/  nc_stest3 ; 
 int /*<<< orphan*/  nc_temp ; 
 int /*<<< orphan*/  nego_bad_phase ; 
 int /*<<< orphan*/  pm0_data ; 
 int /*<<< orphan*/  pm1_data ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int scr_to_cpu (int) ; 
 int /*<<< orphan*/  send_ident ; 
 int /*<<< orphan*/  send_ppr ; 
 int /*<<< orphan*/  send_sdtr ; 
 int /*<<< orphan*/  send_wdtr ; 
 TYPE_6__* sym_ccb_from_dsa (TYPE_5__*,int) ; 
 char* sym_name (TYPE_5__*) ; 
 int /*<<< orphan*/  sym_start_reset (TYPE_5__*) ; 
 int /*<<< orphan*/  wsr_ma_helper ; 

__attribute__((used)) static void sym_int_ma (hcb_p np)
{
	u32	dbc;
	u32	rest;
	u32	dsp;
	u32	dsa;
	u32	nxtdsp;
	u32	*vdsp;
	u32	oadr, olen;
	u32	*tblp;
        u32	newcmd;
	u_int	delta;
	u_char	cmd;
	u_char	hflags, hflags0;
	struct	sym_pmc *pm;
	ccb_p	cp;

	dsp	= INL (nc_dsp);
	dbc	= INL (nc_dbc);
	dsa	= INL (nc_dsa);

	cmd	= dbc >> 24;
	rest	= dbc & 0xffffff;
	delta	= 0;

	/*
	 *  locate matching cp if any.
	 */
	cp = sym_ccb_from_dsa(np, dsa);

	/*
	 *  Donnot take into account dma fifo and various buffers in
	 *  INPUT phase since the chip flushes everything before
	 *  raising the MA interrupt for interrupted INPUT phases.
	 *  For DATA IN phase, we will check for the SWIDE later.
	 */
	if ((cmd & 7) != 1 && (cmd & 7) != 5) {
		u_char ss0, ss2;

		if (np->features & FE_DFBC)
			delta = INW (nc_dfbc);
		else {
			u32 dfifo;

			/*
			 * Read DFIFO, CTEST[4-6] using 1 PCI bus ownership.
			 */
			dfifo = INL(nc_dfifo);

			/*
			 *  Calculate remaining bytes in DMA fifo.
			 *  (CTEST5 = dfifo >> 16)
			 */
			if (dfifo & (DFS << 16))
				delta = ((((dfifo >> 8) & 0x300) |
				          (dfifo & 0xff)) - rest) & 0x3ff;
			else
				delta = ((dfifo & 0xff) - rest) & 0x7f;
		}

		/*
		 *  The data in the dma fifo has not been transferred to
		 *  the target -> add the amount to the rest
		 *  and clear the data.
		 *  Check the sstat2 register in case of wide transfer.
		 */
		rest += delta;
		ss0  = INB (nc_sstat0);
		if (ss0 & OLF) rest++;
		if (!(np->features & FE_C10))
			if (ss0 & ORF) rest++;
		if (cp && (cp->phys.select.sel_scntl3 & EWS)) {
			ss2 = INB (nc_sstat2);
			if (ss2 & OLF1) rest++;
			if (!(np->features & FE_C10))
				if (ss2 & ORF1) rest++;
		}

		/*
		 *  Clear fifos.
		 */
		OUTB (nc_ctest3, np->rv_ctest3 | CLF);	/* dma fifo  */
		OUTB (nc_stest3, TE|CSF);		/* scsi fifo */
	}

	/*
	 *  log the information
	 */
	if (DEBUG_FLAGS & (DEBUG_TINY|DEBUG_PHASE))
		printf ("P%x%x RL=%d D=%d ", cmd&7, INB(nc_sbcl)&7,
			(unsigned) rest, (unsigned) delta);

	/*
	 *  try to find the interrupted script command,
	 *  and the address at which to continue.
	 */
	vdsp	= NULL;
	nxtdsp	= 0;
	if	(dsp >  np->scripta_ba &&
		 dsp <= np->scripta_ba + np->scripta_sz) {
		vdsp = (u32 *)((char*)np->scripta0 + (dsp-np->scripta_ba-8));
		nxtdsp = dsp;
	}
	else if	(dsp >  np->scriptb_ba &&
		 dsp <= np->scriptb_ba + np->scriptb_sz) {
		vdsp = (u32 *)((char*)np->scriptb0 + (dsp-np->scriptb_ba-8));
		nxtdsp = dsp;
	}

	/*
	 *  log the information
	 */
	if (DEBUG_FLAGS & DEBUG_PHASE) {
		printf ("\nCP=%p DSP=%x NXT=%x VDSP=%p CMD=%x ",
			cp, (unsigned)dsp, (unsigned)nxtdsp, vdsp, cmd);
	}

	if (!vdsp) {
		printf ("%s: interrupted SCRIPT address not found.\n",
			sym_name (np));
		goto reset_all;
	}

	if (!cp) {
		printf ("%s: SCSI phase error fixup: CCB already dequeued.\n",
			sym_name (np));
		goto reset_all;
	}

	/*
	 *  get old startaddress and old length.
	 */
	oadr = scr_to_cpu(vdsp[1]);

	if (cmd & 0x10) {	/* Table indirect */
		tblp = (u32 *) ((char*) &cp->phys + oadr);
		olen = scr_to_cpu(tblp[0]);
		oadr = scr_to_cpu(tblp[1]);
	} else {
		tblp = (u32 *) 0;
		olen = scr_to_cpu(vdsp[0]) & 0xffffff;
	}

	if (DEBUG_FLAGS & DEBUG_PHASE) {
		printf ("OCMD=%x\nTBLP=%p OLEN=%x OADR=%x\n",
			(unsigned) (scr_to_cpu(vdsp[0]) >> 24),
			tblp,
			(unsigned) olen,
			(unsigned) oadr);
	}

	/*
	 *  check cmd against assumed interrupted script command.
	 *  If dt data phase, the MOVE instruction hasn't bit 4 of
	 *  the phase.
	 */
	if (((cmd & 2) ? cmd : (cmd & ~4)) != (scr_to_cpu(vdsp[0]) >> 24)) {
		PRINT_ADDR(cp);
		printf ("internal error: cmd=%02x != %02x=(vdsp[0] >> 24)\n",
			(unsigned)cmd, (unsigned)scr_to_cpu(vdsp[0]) >> 24);

		goto reset_all;
	}

	/*
	 *  if old phase not dataphase, leave here.
	 */
	if (cmd & 2) {
		PRINT_ADDR(cp);
		printf ("phase change %x-%x %d@%08x resid=%d.\n",
			cmd&7, INB(nc_sbcl)&7, (unsigned)olen,
			(unsigned)oadr, (unsigned)rest);
		goto unexpected_phase;
	}

	/*
	 *  Choose the correct PM save area.
	 *
	 *  Look at the PM_SAVE SCRIPT if you want to understand
	 *  this stuff. The equivalent code is implemented in
	 *  SCRIPTS for the 895A, 896 and 1010 that are able to
	 *  handle PM from the SCRIPTS processor.
	 */
	hflags0 = INB (HF_PRT);
	hflags = hflags0;

	if (hflags & (HF_IN_PM0 | HF_IN_PM1 | HF_DP_SAVED)) {
		if (hflags & HF_IN_PM0)
			nxtdsp = scr_to_cpu(cp->phys.pm0.ret);
		else if	(hflags & HF_IN_PM1)
			nxtdsp = scr_to_cpu(cp->phys.pm1.ret);

		if (hflags & HF_DP_SAVED)
			hflags ^= HF_ACT_PM;
	}

	if (!(hflags & HF_ACT_PM)) {
		pm = &cp->phys.pm0;
		newcmd = SCRIPTA_BA (np, pm0_data);
	}
	else {
		pm = &cp->phys.pm1;
		newcmd = SCRIPTA_BA (np, pm1_data);
	}

	hflags &= ~(HF_IN_PM0 | HF_IN_PM1 | HF_DP_SAVED);
	if (hflags != hflags0)
		OUTB (HF_PRT, hflags);

	/*
	 *  fillin the phase mismatch context
	 */
	pm->sg.addr = cpu_to_scr(oadr + olen - rest);
	pm->sg.size = cpu_to_scr(rest);
	pm->ret     = cpu_to_scr(nxtdsp);

	/*
	 *  If we have a SWIDE,
	 *  - prepare the address to write the SWIDE from SCRIPTS,
	 *  - compute the SCRIPTS address to restart from,
	 *  - move current data pointer context by one byte.
	 */
	nxtdsp = SCRIPTA_BA (np, dispatch);
	if ((cmd & 7) == 1 && cp && (cp->phys.select.sel_scntl3 & EWS) &&
	    (INB (nc_scntl2) & WSR)) {
		u32 tmp;

		/*
		 *  Set up the table indirect for the MOVE
		 *  of the residual byte and adjust the data
		 *  pointer context.
		 */
		tmp = scr_to_cpu(pm->sg.addr);
		cp->phys.wresid.addr = cpu_to_scr(tmp);
		pm->sg.addr = cpu_to_scr(tmp + 1);
		tmp = scr_to_cpu(pm->sg.size);
		cp->phys.wresid.size = cpu_to_scr((tmp&0xff000000) | 1);
		pm->sg.size = cpu_to_scr(tmp - 1);

		/*
		 *  If only the residual byte is to be moved,
		 *  no PM context is needed.
		 */
		if ((tmp&0xffffff) == 1)
			newcmd = pm->ret;

		/*
		 *  Prepare the address of SCRIPTS that will
		 *  move the residual byte to memory.
		 */
		nxtdsp = SCRIPTB_BA (np, wsr_ma_helper);
	}

	if (DEBUG_FLAGS & DEBUG_PHASE) {
		PRINT_ADDR(cp);
		printf ("PM %x %x %x / %x %x %x.\n",
			hflags0, hflags, newcmd,
			(unsigned)scr_to_cpu(pm->sg.addr),
			(unsigned)scr_to_cpu(pm->sg.size),
			(unsigned)scr_to_cpu(pm->ret));
	}

	/*
	 *  Restart the SCRIPTS processor.
	 */
	OUTL (nc_temp, newcmd);
	OUTL_DSP (nxtdsp);
	return;

	/*
	 *  Unexpected phase changes that occurs when the current phase
	 *  is not a DATA IN or DATA OUT phase are due to error conditions.
	 *  Such event may only happen when the SCRIPTS is using a
	 *  multibyte SCSI MOVE.
	 *
	 *  Phase change		Some possible cause
	 *
	 *  COMMAND  --> MSG IN	SCSI parity error detected by target.
	 *  COMMAND  --> STATUS	Bad command or refused by target.
	 *  MSG OUT  --> MSG IN     Message rejected by target.
	 *  MSG OUT  --> COMMAND    Bogus target that discards extended
	 *  			negotiation messages.
	 *
	 *  The code below does not care of the new phase and so
	 *  trusts the target. Why to annoy it ?
	 *  If the interrupted phase is COMMAND phase, we restart at
	 *  dispatcher.
	 *  If a target does not get all the messages after selection,
	 *  the code assumes blindly that the target discards extended
	 *  messages and clears the negotiation status.
	 *  If the target does not want all our response to negotiation,
	 *  we force a SIR_NEGO_PROTO interrupt (it is a hack that avoids
	 *  bloat for such a should_not_happen situation).
	 *  In all other situation, we reset the BUS.
	 *  Are these assumptions reasonnable ? (Wait and see ...)
	 */
unexpected_phase:
	dsp -= 8;
	nxtdsp = 0;

	switch (cmd & 7) {
	case 2:	/* COMMAND phase */
		nxtdsp = SCRIPTA_BA (np, dispatch);
		break;
#if 0
	case 3:	/* STATUS  phase */
		nxtdsp = SCRIPTA_BA (np, dispatch);
		break;
#endif
	case 6:	/* MSG OUT phase */
		/*
		 *  If the device may want to use untagged when we want
		 *  tagged, we prepare an IDENTIFY without disc. granted,
		 *  since we will not be able to handle reselect.
		 *  Otherwise, we just don't care.
		 */
		if	(dsp == SCRIPTA_BA (np, send_ident)) {
			if (cp->tag != NO_TAG && olen - rest <= 3) {
				cp->host_status = HS_BUSY;
				np->msgout[0] = M_IDENTIFY | cp->lun;
				nxtdsp = SCRIPTB_BA (np, ident_break_atn);
			}
			else
				nxtdsp = SCRIPTB_BA (np, ident_break);
		}
		else if	(dsp == SCRIPTB_BA (np, send_wdtr) ||
			 dsp == SCRIPTB_BA (np, send_sdtr) ||
			 dsp == SCRIPTB_BA (np, send_ppr)) {
			nxtdsp = SCRIPTB_BA (np, nego_bad_phase);
		}
		break;
#if 0
	case 7:	/* MSG IN  phase */
		nxtdsp = SCRIPTA_BA (np, clrack);
		break;
#endif
	}

	if (nxtdsp) {
		OUTL_DSP (nxtdsp);
		return;
	}

reset_all:
	sym_start_reset(np);
}