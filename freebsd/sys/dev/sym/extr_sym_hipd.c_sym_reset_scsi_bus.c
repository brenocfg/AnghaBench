#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_long ;
typedef  int u32 ;
typedef  TYPE_1__* hcb_p ;
struct TYPE_5__ {int rv_dcntl; int features; } ;

/* Variables and functions */
 int CRST ; 
 int FE_WIDE ; 
 int INB (int /*<<< orphan*/ ) ; 
 int INW (int /*<<< orphan*/ ) ; 
 int IRQM ; 
 int /*<<< orphan*/  OUTB (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OUTW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RST ; 
 int SYM_SETUP_SCSI_BUS_CHECK ; 
 int TE ; 
 int /*<<< orphan*/  UDELAY (int) ; 
 int /*<<< orphan*/  nc_dcntl ; 
 int /*<<< orphan*/  nc_sbcl ; 
 int /*<<< orphan*/  nc_sbdl ; 
 int /*<<< orphan*/  nc_scntl1 ; 
 int /*<<< orphan*/  nc_sien ; 
 int /*<<< orphan*/  nc_sstat0 ; 
 int /*<<< orphan*/  nc_sstat2 ; 
 int /*<<< orphan*/  nc_stest3 ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 char* sym_name (TYPE_1__*) ; 
 int /*<<< orphan*/  sym_soft_reset (TYPE_1__*) ; 

__attribute__((used)) static int sym_reset_scsi_bus(hcb_p np, int enab_int)
{
	u32 term;
	int retv = 0;

	sym_soft_reset(np);	/* Soft reset the chip */
	if (enab_int)
		OUTW (nc_sien, RST);
	/*
	 *  Enable Tolerant, reset IRQD if present and
	 *  properly set IRQ mode, prior to resetting the bus.
	 */
	OUTB (nc_stest3, TE);
	OUTB (nc_dcntl, (np->rv_dcntl & IRQM));
	OUTB (nc_scntl1, CRST);
	UDELAY (200);

	if (!SYM_SETUP_SCSI_BUS_CHECK)
		goto out;
	/*
	 *  Check for no terminators or SCSI bus shorts to ground.
	 *  Read SCSI data bus, data parity bits and control signals.
	 *  We are expecting RESET to be TRUE and other signals to be
	 *  FALSE.
	 */
	term =	INB(nc_sstat0);
	term =	((term & 2) << 7) + ((term & 1) << 17);	/* rst sdp0 */
	term |= ((INB(nc_sstat2) & 0x01) << 26) |	/* sdp1     */
		((INW(nc_sbdl) & 0xff)   << 9)  |	/* d7-0     */
		((INW(nc_sbdl) & 0xff00) << 10) |	/* d15-8    */
		INB(nc_sbcl);	/* req ack bsy sel atn msg cd io    */

	if (!(np->features & FE_WIDE))
		term &= 0x3ffff;

	if (term != (2<<7)) {
		printf("%s: suspicious SCSI data while resetting the BUS.\n",
			sym_name(np));
		printf("%s: %sdp0,d7-0,rst,req,ack,bsy,sel,atn,msg,c/d,i/o = "
			"0x%lx, expecting 0x%lx\n",
			sym_name(np),
			(np->features & FE_WIDE) ? "dp1,d15-8," : "",
			(u_long)term, (u_long)(2<<7));
		if (SYM_SETUP_SCSI_BUS_CHECK == 1)
			retv = 1;
	}
out:
	OUTB (nc_scntl1, 0);
	/* MDELAY(100); */
	return retv;
}