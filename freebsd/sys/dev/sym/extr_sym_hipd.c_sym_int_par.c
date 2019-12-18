#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int u_short ;
typedef  int u_char ;
typedef  int u32 ;
typedef  TYPE_1__* hcb_p ;
typedef  TYPE_2__* ccb_p ;
struct TYPE_13__ {int /*<<< orphan*/  xerr_status; } ;
struct TYPE_12__ {int /*<<< orphan*/ * msgout; } ;

/* Variables and functions */
 int /*<<< orphan*/  HF_EXT_ERR ; 
 int /*<<< orphan*/  HF_PRT ; 
 int /*<<< orphan*/  HS_PRT ; 
 int /*<<< orphan*/  HS_UNEXPECTED ; 
 int INB (int /*<<< orphan*/ ) ; 
 int INL (int /*<<< orphan*/ ) ; 
 int ISCON ; 
 int MA ; 
 int /*<<< orphan*/  M_ID_ERROR ; 
 int /*<<< orphan*/  M_PARITY ; 
 int /*<<< orphan*/  OUTL (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OUTL_DSP (int) ; 
 int /*<<< orphan*/  OUTONB (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SCRIPTA_BA (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int SCRIPTB_BA (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XE_PARITY_ERR ; 
 int /*<<< orphan*/  clrack ; 
 int /*<<< orphan*/  dispatch ; 
 int /*<<< orphan*/  nc_dbc ; 
 int /*<<< orphan*/  nc_dsa ; 
 int /*<<< orphan*/  nc_dsp ; 
 int /*<<< orphan*/  nc_sbcl ; 
 int /*<<< orphan*/  nc_scntl1 ; 
 int /*<<< orphan*/  nc_temp ; 
 int /*<<< orphan*/  pm_handle ; 
 int /*<<< orphan*/  printf (char*,char*,int,int,int) ; 
 TYPE_2__* sym_ccb_from_dsa (TYPE_1__*,int) ; 
 int /*<<< orphan*/  sym_int_ma (TYPE_1__*) ; 
 char* sym_name (TYPE_1__*) ; 
 int /*<<< orphan*/  sym_recover_scsi_int (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sym_start_reset (TYPE_1__*) ; 

__attribute__((used)) static void sym_int_par (hcb_p np, u_short sist)
{
	u_char	hsts	= INB (HS_PRT);
	u32	dsp	= INL (nc_dsp);
	u32	dbc	= INL (nc_dbc);
	u32	dsa	= INL (nc_dsa);
	u_char	sbcl	= INB (nc_sbcl);
	u_char	cmd	= dbc >> 24;
	int phase	= cmd & 7;
	ccb_p	cp	= sym_ccb_from_dsa(np, dsa);

	printf("%s: SCSI parity error detected: SCR1=%d DBC=%x SBCL=%x\n",
		sym_name(np), hsts, dbc, sbcl);

	/*
	 *  Check that the chip is connected to the SCSI BUS.
	 */
	if (!(INB (nc_scntl1) & ISCON)) {
		sym_recover_scsi_int(np, HS_UNEXPECTED);
		return;
	}

	/*
	 *  If the nexus is not clearly identified, reset the bus.
	 *  We will try to do better later.
	 */
	if (!cp)
		goto reset_all;

	/*
	 *  Check instruction was a MOV, direction was INPUT and
	 *  ATN is asserted.
	 */
	if ((cmd & 0xc0) || !(phase & 1) || !(sbcl & 0x8))
		goto reset_all;

	/*
	 *  Keep track of the parity error.
	 */
	OUTONB (HF_PRT, HF_EXT_ERR);
	cp->xerr_status |= XE_PARITY_ERR;

	/*
	 *  Prepare the message to send to the device.
	 */
	np->msgout[0] = (phase == 7) ? M_PARITY : M_ID_ERROR;

	/*
	 *  If the old phase was DATA IN phase, we have to deal with
	 *  the 3 situations described above.
	 *  For other input phases (MSG IN and STATUS), the device
	 *  must resend the whole thing that failed parity checking
	 *  or signal error. So, jumping to dispatcher should be OK.
	 */
	if (phase == 1 || phase == 5) {
		/* Phase mismatch handled by SCRIPTS */
		if (dsp == SCRIPTB_BA (np, pm_handle))
			OUTL_DSP (dsp);
		/* Phase mismatch handled by the C code */
		else if (sist & MA)
			sym_int_ma (np);
		/* No phase mismatch occurred */
		else {
			OUTL (nc_temp, dsp);
			OUTL_DSP (SCRIPTA_BA (np, dispatch));
		}
	}
	else
		OUTL_DSP (SCRIPTA_BA (np, clrack));
	return;

reset_all:
	sym_start_reset(np);
}