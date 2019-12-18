#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int u_short ;
typedef  int u_char ;
typedef  TYPE_1__* hcb_p ;
struct TYPE_14__ {int istat_sem; int rv_ctest3; int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int ABRT ; 
 int BF ; 
 int CABRT ; 
 int CLF ; 
 int CSF ; 
 int DEBUG_FLAGS ; 
 int DEBUG_TINY ; 
 int DIP ; 
 int GEN ; 
 int HTH ; 
 int IID ; 
 int INB (int /*<<< orphan*/ ) ; 
 scalar_t__ INL (int /*<<< orphan*/ ) ; 
 int INTF ; 
 int INW (int /*<<< orphan*/ ) ; 
 int MA ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int MDPE ; 
 int /*<<< orphan*/  MEMORY_BARRIER () ; 
 int /*<<< orphan*/  OUTB (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OUTONB_STD () ; 
 int PAR ; 
 int RST ; 
 int SBMC ; 
 int SGE ; 
 int SIGP ; 
 int SIP ; 
 int SIR ; 
 int SSI ; 
 int STO ; 
 int /*<<< orphan*/  SYM_LOCK_ASSERT (int /*<<< orphan*/ ) ; 
 int TE ; 
 int UDC ; 
 int /*<<< orphan*/  nc_ctest3 ; 
 int /*<<< orphan*/  nc_dbc ; 
 int /*<<< orphan*/  nc_dsp ; 
 int /*<<< orphan*/  nc_dstat ; 
 int /*<<< orphan*/  nc_istat ; 
 int /*<<< orphan*/  nc_scr0 ; 
 int /*<<< orphan*/  nc_sist ; 
 int /*<<< orphan*/  nc_stest3 ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  sym_init (TYPE_1__*,int) ; 
 int /*<<< orphan*/  sym_int_ma (TYPE_1__*) ; 
 int /*<<< orphan*/  sym_int_par (TYPE_1__*,int) ; 
 int /*<<< orphan*/  sym_int_sbmc (TYPE_1__*) ; 
 int /*<<< orphan*/  sym_int_sir (TYPE_1__*) ; 
 int /*<<< orphan*/  sym_int_sto (TYPE_1__*) ; 
 int /*<<< orphan*/  sym_int_udc (TYPE_1__*) ; 
 int /*<<< orphan*/  sym_log_hard_error (TYPE_1__*,int,int) ; 
 char* sym_name (TYPE_1__*) ; 
 int /*<<< orphan*/  sym_start_reset (TYPE_1__*) ; 
 int /*<<< orphan*/  sym_wakeup_done (TYPE_1__*) ; 
 int /*<<< orphan*/  xpt_print_path (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sym_intr1 (hcb_p np)
{
	u_char	istat, istatc;
	u_char	dstat;
	u_short	sist;

	SYM_LOCK_ASSERT(MA_OWNED);

	/*
	 *  interrupt on the fly ?
	 *
	 *  A `dummy read' is needed to ensure that the
	 *  clear of the INTF flag reaches the device
	 *  before the scanning of the DONE queue.
	 */
	istat = INB (nc_istat);
	if (istat & INTF) {
		OUTB (nc_istat, (istat & SIGP) | INTF | np->istat_sem);
		istat = INB (nc_istat);		/* DUMMY READ */
		if (DEBUG_FLAGS & DEBUG_TINY) printf ("F ");
		(void)sym_wakeup_done (np);
	}

	if (!(istat & (SIP|DIP)))
		return;

#if 0	/* We should never get this one */
	if (istat & CABRT)
		OUTB (nc_istat, CABRT);
#endif

	/*
	 *  PAR and MA interrupts may occur at the same time,
	 *  and we need to know of both in order to handle
	 *  this situation properly. We try to unstack SCSI
	 *  interrupts for that reason. BTW, I dislike a LOT
	 *  such a loop inside the interrupt routine.
	 *  Even if DMA interrupt stacking is very unlikely to
	 *  happen, we also try unstacking these ones, since
	 *  this has no performance impact.
	 */
	sist	= 0;
	dstat	= 0;
	istatc	= istat;
	do {
		if (istatc & SIP)
			sist  |= INW (nc_sist);
		if (istatc & DIP)
			dstat |= INB (nc_dstat);
		istatc = INB (nc_istat);
		istat |= istatc;
	} while (istatc & (SIP|DIP));

	if (DEBUG_FLAGS & DEBUG_TINY)
		printf ("<%d|%x:%x|%x:%x>",
			(int)INB(nc_scr0),
			dstat,sist,
			(unsigned)INL(nc_dsp),
			(unsigned)INL(nc_dbc));
	/*
	 *  On paper, a memory barrier may be needed here.
	 *  And since we are paranoid ... :)
	 */
	MEMORY_BARRIER();

	/*
	 *  First, interrupts we want to service cleanly.
	 *
	 *  Phase mismatch (MA) is the most frequent interrupt
	 *  for chip earlier than the 896 and so we have to service
	 *  it as quickly as possible.
	 *  A SCSI parity error (PAR) may be combined with a phase
	 *  mismatch condition (MA).
	 *  Programmed interrupts (SIR) are used to call the C code
	 *  from SCRIPTS.
	 *  The single step interrupt (SSI) is not used in this
	 *  driver.
	 */
	if (!(sist  & (STO|GEN|HTH|SGE|UDC|SBMC|RST)) &&
	    !(dstat & (MDPE|BF|ABRT|IID))) {
		if	(sist & PAR)	sym_int_par (np, sist);
		else if (sist & MA)	sym_int_ma (np);
		else if (dstat & SIR)	sym_int_sir (np);
		else if (dstat & SSI)	OUTONB_STD ();
		else			goto unknown_int;
		return;
	}

	/*
	 *  Now, interrupts that donnot happen in normal
	 *  situations and that we may need to recover from.
	 *
	 *  On SCSI RESET (RST), we reset everything.
	 *  On SCSI BUS MODE CHANGE (SBMC), we complete all
	 *  active CCBs with RESET status, prepare all devices
	 *  for negotiating again and restart the SCRIPTS.
	 *  On STO and UDC, we complete the CCB with the corres-
	 *  ponding status and restart the SCRIPTS.
	 */
	if (sist & RST) {
		xpt_print_path(np->path);
		printf("SCSI BUS reset detected.\n");
		sym_init (np, 1);
		return;
	}

	OUTB (nc_ctest3, np->rv_ctest3 | CLF);	/* clear dma fifo  */
	OUTB (nc_stest3, TE|CSF);		/* clear scsi fifo */

	if (!(sist  & (GEN|HTH|SGE)) &&
	    !(dstat & (MDPE|BF|ABRT|IID))) {
		if	(sist & SBMC)	sym_int_sbmc (np);
		else if (sist & STO)	sym_int_sto (np);
		else if (sist & UDC)	sym_int_udc (np);
		else			goto unknown_int;
		return;
	}

	/*
	 *  Now, interrupts we are not able to recover cleanly.
	 *
	 *  Log message for hard errors.
	 *  Reset everything.
	 */

	sym_log_hard_error(np, sist, dstat);

	if ((sist & (GEN|HTH|SGE)) ||
		(dstat & (MDPE|BF|ABRT|IID))) {
		sym_start_reset(np);
		return;
	}

unknown_int:
	/*
	 *  We just miss the cause of the interrupt. :(
	 *  Print a message. The timeout will do the real work.
	 */
	printf(	"%s: unknown interrupt(s) ignored, "
		"ISTAT=0x%x DSTAT=0x%x SIST=0x%x\n",
		sym_name(np), istat, dstat, sist);
}