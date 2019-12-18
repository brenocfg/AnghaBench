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
struct ahd_softc {int tqinfifonext; } ;

/* Variables and functions */
 int /*<<< orphan*/  AHD_MODE_CCHAN ; 
 int /*<<< orphan*/  AHD_MODE_SCSI ; 
 int BITBUCKET ; 
 int /*<<< orphan*/  CLRINT ; 
 int CLRSEQINT ; 
 int ENAUTOATNP ; 
 int ENRSELI ; 
 int ENSELI ; 
 int FASTMODE ; 
 int /*<<< orphan*/  LASTPHASE ; 
 int MSG_NOOP ; 
 int /*<<< orphan*/  MSG_OUT ; 
 int P_BUSFREE ; 
 int /*<<< orphan*/  SAVED_LUN ; 
 int /*<<< orphan*/  SAVED_SCSIID ; 
 int /*<<< orphan*/  SCSISEQ1 ; 
 int /*<<< orphan*/  SCSISEQ_TEMPLATE ; 
 int /*<<< orphan*/  SCSISIGO ; 
 int /*<<< orphan*/  SEQCTL0 ; 
 int /*<<< orphan*/  SEQINTCTL ; 
 int SEQRESET ; 
 int /*<<< orphan*/  SEQ_FLAGS ; 
 int /*<<< orphan*/  SXFRCTL1 ; 
 int /*<<< orphan*/  TQINPOS ; 
 int /*<<< orphan*/  ahd_clear_msg_state (struct ahd_softc*) ; 
 int ahd_inb (struct ahd_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_outb (struct ahd_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ahd_pause (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_set_modes (struct ahd_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_unpause (struct ahd_softc*) ; 

void
ahd_restart(struct ahd_softc *ahd)
{

	ahd_pause(ahd);

	ahd_set_modes(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI);

	/* No more pending messages */
	ahd_clear_msg_state(ahd);
	ahd_outb(ahd, SCSISIGO, 0);		/* De-assert BSY */
	ahd_outb(ahd, MSG_OUT, MSG_NOOP);	/* No message to send */
	ahd_outb(ahd, SXFRCTL1, ahd_inb(ahd, SXFRCTL1) & ~BITBUCKET);
	ahd_outb(ahd, SEQINTCTL, 0);
	ahd_outb(ahd, LASTPHASE, P_BUSFREE);
	ahd_outb(ahd, SEQ_FLAGS, 0);
	ahd_outb(ahd, SAVED_SCSIID, 0xFF);
	ahd_outb(ahd, SAVED_LUN, 0xFF);

	/*
	 * Ensure that the sequencer's idea of TQINPOS
	 * matches our own.  The sequencer increments TQINPOS
	 * only after it sees a DMA complete and a reset could
	 * occur before the increment leaving the kernel to believe
	 * the command arrived but the sequencer to not.
	 */
	ahd_outb(ahd, TQINPOS, ahd->tqinfifonext);

	/* Always allow reselection */
	ahd_outb(ahd, SCSISEQ1,
		 ahd_inb(ahd, SCSISEQ_TEMPLATE) & (ENSELI|ENRSELI|ENAUTOATNP));
	ahd_set_modes(ahd, AHD_MODE_CCHAN, AHD_MODE_CCHAN);

	/*
	 * Clear any pending sequencer interrupt.  It is no
	 * longer relevant since we're resetting the Program
	 * Counter.
	 */
	ahd_outb(ahd, CLRINT, CLRSEQINT);

	ahd_outb(ahd, SEQCTL0, FASTMODE|SEQRESET);
	ahd_unpause(ahd);
}