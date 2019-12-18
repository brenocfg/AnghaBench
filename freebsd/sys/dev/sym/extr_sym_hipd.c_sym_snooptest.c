#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_long ;
typedef  int u32 ;
typedef  TYPE_1__* hcb_p ;
struct TYPE_6__ {int rv_ctest4; int hcb_ba; int /*<<< orphan*/  cache; } ;

/* Variables and functions */
 int BF ; 
 int DIP ; 
 int IID ; 
 int INB (int /*<<< orphan*/ ) ; 
 int INL (int /*<<< orphan*/ ) ; 
 int INTF ; 
 int MDPE ; 
 int MPEE ; 
 int /*<<< orphan*/  OUTB (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OUTL (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OUTL_DSP (int) ; 
 int SCRIPTB0_BA (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int SIP ; 
 int SYM_SNOOP_TIMEOUT ; 
 int /*<<< orphan*/  cpu_to_scr (int) ; 
 int /*<<< orphan*/  nc_ctest4 ; 
 int /*<<< orphan*/  nc_dsa ; 
 int /*<<< orphan*/  nc_dsp ; 
 int /*<<< orphan*/  nc_dstat ; 
 int /*<<< orphan*/  nc_istat ; 
 int /*<<< orphan*/  nc_scratcha ; 
 int /*<<< orphan*/  nc_temp ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int scr_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snoopend ; 
 int /*<<< orphan*/  snooptest ; 
 char* sym_name (TYPE_1__*) ; 
 int sym_regtest (TYPE_1__*) ; 

__attribute__((used)) static int sym_snooptest (hcb_p np)
{
	u32	sym_rd, sym_wr, sym_bk, host_rd, host_wr, pc, dstat;
	int	i, err=0;
#ifndef SYM_CONF_IOMAPPED
	err |= sym_regtest (np);
	if (err) return (err);
#endif
restart_test:
	/*
	 *  Enable Master Parity Checking as we intend
	 *  to enable it for normal operations.
	 */
	OUTB (nc_ctest4, (np->rv_ctest4 & MPEE));
	/*
	 *  init
	 */
	pc  = SCRIPTB0_BA (np, snooptest);
	host_wr = 1;
	sym_wr  = 2;
	/*
	 *  Set memory and register.
	 */
	np->cache = cpu_to_scr(host_wr);
	OUTL (nc_temp, sym_wr);
	/*
	 *  Start script (exchange values)
	 */
	OUTL (nc_dsa, np->hcb_ba);
	OUTL_DSP (pc);
	/*
	 *  Wait 'til done (with timeout)
	 */
	for (i=0; i<SYM_SNOOP_TIMEOUT; i++)
		if (INB(nc_istat) & (INTF|SIP|DIP))
			break;
	if (i>=SYM_SNOOP_TIMEOUT) {
		printf ("CACHE TEST FAILED: timeout.\n");
		return (0x20);
	}
	/*
	 *  Check for fatal DMA errors.
	 */
	dstat = INB (nc_dstat);
#if 1	/* Band aiding for broken hardwares that fail PCI parity */
	if ((dstat & MDPE) && (np->rv_ctest4 & MPEE)) {
		printf ("%s: PCI DATA PARITY ERROR DETECTED - "
			"DISABLING MASTER DATA PARITY CHECKING.\n",
			sym_name(np));
		np->rv_ctest4 &= ~MPEE;
		goto restart_test;
	}
#endif
	if (dstat & (MDPE|BF|IID)) {
		printf ("CACHE TEST FAILED: DMA error (dstat=0x%02x).", dstat);
		return (0x80);
	}
	/*
	 *  Save termination position.
	 */
	pc = INL (nc_dsp);
	/*
	 *  Read memory and register.
	 */
	host_rd = scr_to_cpu(np->cache);
	sym_rd  = INL (nc_scratcha);
	sym_bk  = INL (nc_temp);

	/*
	 *  Check termination position.
	 */
	if (pc != SCRIPTB0_BA (np, snoopend)+8) {
		printf ("CACHE TEST FAILED: script execution failed.\n");
		printf ("start=%08lx, pc=%08lx, end=%08lx\n",
			(u_long) SCRIPTB0_BA (np, snooptest), (u_long) pc,
			(u_long) SCRIPTB0_BA (np, snoopend) +8);
		return (0x40);
	}
	/*
	 *  Show results.
	 */
	if (host_wr != sym_rd) {
		printf ("CACHE TEST FAILED: host wrote %d, chip read %d.\n",
			(int) host_wr, (int) sym_rd);
		err |= 1;
	}
	if (host_rd != sym_wr) {
		printf ("CACHE TEST FAILED: chip wrote %d, host read %d.\n",
			(int) sym_wr, (int) host_rd);
		err |= 2;
	}
	if (sym_bk != sym_wr) {
		printf ("CACHE TEST FAILED: chip wrote %d, read back %d.\n",
			(int) sym_wr, (int) sym_bk);
		err |= 4;
	}

	return (err);
}