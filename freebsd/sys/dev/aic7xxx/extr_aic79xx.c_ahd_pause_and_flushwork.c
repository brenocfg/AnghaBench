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
struct ahd_softc {int features; int /*<<< orphan*/  flags; int /*<<< orphan*/  qfreeze_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  AHD_ALL_INTERRUPTS ; 
 int /*<<< orphan*/  AHD_FATAL_ERROR (struct ahd_softc*) ; 
 int AHD_REMOVABLE ; 
 int ENSELO ; 
 int /*<<< orphan*/  INTSTAT ; 
 int INT_PEND ; 
 int /*<<< orphan*/  KERNEL_QFREEZE_COUNT ; 
 int /*<<< orphan*/  SCSISEQ0 ; 
 int SELDO ; 
 int SELECTOUT_QFROZEN ; 
 int SELINGO ; 
 int /*<<< orphan*/  SEQ_FLAGS2 ; 
 int /*<<< orphan*/  SSTAT0 ; 
 int /*<<< orphan*/  ahd_clear_critical_section (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_flush_qoutfifo (struct ahd_softc*) ; 
 int ahd_inb (struct ahd_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_intr (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_outb (struct ahd_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ahd_outw (struct ahd_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_pause (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_platform_flushwork (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_unpause (struct ahd_softc*) ; 
 int /*<<< orphan*/  aic_delay (int) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

void
ahd_pause_and_flushwork(struct ahd_softc *ahd)
{
	u_int intstat;
	u_int maxloops;

	maxloops = 1000;
	ahd->flags |= AHD_ALL_INTERRUPTS;
	ahd_pause(ahd);
	/*
	 * Freeze the outgoing selections.  We do this only
	 * until we are safely paused without further selections
	 * pending.
	 */
	ahd->qfreeze_cnt--;
	ahd_outw(ahd, KERNEL_QFREEZE_COUNT, ahd->qfreeze_cnt);
	ahd_outb(ahd, SEQ_FLAGS2, ahd_inb(ahd, SEQ_FLAGS2) | SELECTOUT_QFROZEN);
	do {

		ahd_unpause(ahd);
		/*
		 * Give the sequencer some time to service
		 * any active selections.
		 */
		aic_delay(500);

		ahd_intr(ahd);
		ahd_pause(ahd);
		intstat = ahd_inb(ahd, INTSTAT);
		if ((intstat & INT_PEND) == 0) {
			ahd_clear_critical_section(ahd);
			intstat = ahd_inb(ahd, INTSTAT);
		}
	} while (--maxloops
	      && (intstat != 0xFF || (ahd->features & AHD_REMOVABLE) == 0)
	      && ((intstat & INT_PEND) != 0
	       || (ahd_inb(ahd, SCSISEQ0) & ENSELO) != 0
	       || (ahd_inb(ahd, SSTAT0) & (SELDO|SELINGO)) != 0));

	if (maxloops == 0) {
		printf("Infinite interrupt loop, INTSTAT = %x",
		      ahd_inb(ahd, INTSTAT));
		AHD_FATAL_ERROR(ahd);
	}
	ahd->qfreeze_cnt++;
	ahd_outw(ahd, KERNEL_QFREEZE_COUNT, ahd->qfreeze_cnt);

	ahd_flush_qoutfifo(ahd);

	ahd_platform_flushwork(ahd);
	ahd->flags &= ~AHD_ALL_INTERRUPTS;
}