#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u_int ;
struct ahc_softc {int pause; int flags; int unsolicited_ints; int chip; int features; int /*<<< orphan*/  (* bus_intr ) (struct ahc_softc*) ;} ;

/* Variables and functions */
 int AHC_ALL_INTERRUPTS ; 
 int AHC_EDGE_INTERRUPT ; 
 int AHC_PCI ; 
 int AHC_REMOVABLE ; 
 int AHC_TARGETROLE ; 
 int BRKADRINT ; 
 int /*<<< orphan*/  CLRCMDINT ; 
 int /*<<< orphan*/  CLRINT ; 
 int CMDCMPLT ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FALSE ; 
 int INTEN ; 
 int /*<<< orphan*/  INTSTAT ; 
 int INT_PEND ; 
 int PCIERRSTAT ; 
 int SCSIINT ; 
 int SEQINT ; 
 scalar_t__ ahc_check_cmdcmpltqueues (struct ahc_softc*) ; 
 int /*<<< orphan*/  ahc_flush_device_writes (struct ahc_softc*) ; 
 int /*<<< orphan*/  ahc_handle_brkadrint (struct ahc_softc*) ; 
 int /*<<< orphan*/  ahc_handle_scsiint (struct ahc_softc*,int) ; 
 int /*<<< orphan*/  ahc_handle_seqint (struct ahc_softc*,int) ; 
 int ahc_inb (struct ahc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahc_outb (struct ahc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahc_pause_bug_fix (struct ahc_softc*) ; 
 int /*<<< orphan*/  ahc_run_qoutfifo (struct ahc_softc*) ; 
 int /*<<< orphan*/  ahc_run_tqinfifo (struct ahc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct ahc_softc*) ; 

__attribute__((used)) static __inline int
ahc_intr(struct ahc_softc *ahc)
{
	u_int	intstat;

	if ((ahc->pause & INTEN) == 0) {
		/*
		 * Our interrupt is not enabled on the chip
		 * and may be disabled for re-entrancy reasons,
		 * so just return.  This is likely just a shared
		 * interrupt.
		 */
		return (0);
	}
	/*
	 * Instead of directly reading the interrupt status register,
	 * infer the cause of the interrupt by checking our in-core
	 * completion queues.  This avoids a costly PCI bus read in
	 * most cases.
	 */
	if ((ahc->flags & (AHC_ALL_INTERRUPTS|AHC_EDGE_INTERRUPT)) == 0
	 && (ahc_check_cmdcmpltqueues(ahc) != 0))
		intstat = CMDCMPLT;
	else {
		intstat = ahc_inb(ahc, INTSTAT);
	}

	if ((intstat & INT_PEND) == 0) {
#if AIC_PCI_CONFIG > 0
		if (ahc->unsolicited_ints > 500) {
			ahc->unsolicited_ints = 0;
			if ((ahc->chip & AHC_PCI) != 0
			 && (ahc_inb(ahc, ERROR) & PCIERRSTAT) != 0)
				ahc->bus_intr(ahc);
		}
#endif
		ahc->unsolicited_ints++;
		return (0);
	}
	ahc->unsolicited_ints = 0;

	if (intstat & CMDCMPLT) {
		ahc_outb(ahc, CLRINT, CLRCMDINT);

		/*
		 * Ensure that the chip sees that we've cleared
		 * this interrupt before we walk the output fifo.
		 * Otherwise, we may, due to posted bus writes,
		 * clear the interrupt after we finish the scan,
		 * and after the sequencer has added new entries
		 * and asserted the interrupt again.
		 */
		ahc_flush_device_writes(ahc);
		ahc_run_qoutfifo(ahc);
#ifdef AHC_TARGET_MODE
		if ((ahc->flags & AHC_TARGETROLE) != 0)
			ahc_run_tqinfifo(ahc, /*paused*/FALSE);
#endif
	}

	/*
	 * Handle statuses that may invalidate our cached
	 * copy of INTSTAT separately.
	 */
	if (intstat == 0xFF && (ahc->features & AHC_REMOVABLE) != 0) {
		/* Hot eject.  Do nothing */
	} else if (intstat & BRKADRINT) {
		ahc_handle_brkadrint(ahc);
	} else if ((intstat & (SEQINT|SCSIINT)) != 0) {

		ahc_pause_bug_fix(ahc);

		if ((intstat & SEQINT) != 0)
			ahc_handle_seqint(ahc, intstat);

		if ((intstat & SCSIINT) != 0)
			ahc_handle_scsiint(ahc, intstat);
	}
	return (1);
}