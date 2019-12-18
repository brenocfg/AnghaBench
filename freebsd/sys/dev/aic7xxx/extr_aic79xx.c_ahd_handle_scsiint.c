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
struct scb {int flags; } ;
struct ahd_softc {int bugs; } ;
struct ahd_devinfo {int dummy; } ;

/* Variables and functions */
 int AHD_BUSFREEREV_BUG ; 
 int AHD_CLRLQO_AUTOCLR_BUG ; 
 int /*<<< orphan*/  AHD_CORRECTABLE_ERROR (struct ahd_softc*) ; 
 int AHD_MODE_CFG ; 
 int AHD_MODE_DFF0 ; 
 int AHD_MODE_DFF1 ; 
 int AHD_MODE_SCSI ; 
 int AHD_SHOW_MISC ; 
 int AHD_SHOW_SELTO ; 
 int /*<<< orphan*/  AHD_UNCORRECTABLE_ERROR (struct ahd_softc*) ; 
 int BUSFREE ; 
 int BUSFREETIME ; 
#define  BUSFREE_DFF0 130 
#define  BUSFREE_DFF1 129 
#define  BUSFREE_LQO 128 
 int /*<<< orphan*/  CAM_LUN_WILDCARD ; 
 int /*<<< orphan*/  CAM_SEL_TIMEOUT ; 
 int CLRBUSFREE ; 
 int /*<<< orphan*/  CLRINT ; 
 int CLRIOERR ; 
 int CLRLQICRCI_NLQ ; 
 int /*<<< orphan*/  CLRLQIINT1 ; 
 int /*<<< orphan*/  CLRLQOINT0 ; 
 int /*<<< orphan*/  CLRLQOINT1 ; 
 int CLRSCSIINT ; 
 int CLRSCSIPERR ; 
 int CLRSELINGO ; 
 int CLRSELTIMEO ; 
 int /*<<< orphan*/  CLRSINT0 ; 
 int /*<<< orphan*/  CLRSINT1 ; 
 int /*<<< orphan*/  CLRSINT3 ; 
 int ENAB40 ; 
 int ENBUSFREE ; 
 int ENSELO ; 
 int /*<<< orphan*/  FALSE ; 
 int IOERR ; 
 int /*<<< orphan*/  LASTPHASE ; 
 int LQICRCI_NLQ ; 
 int LQIPHASE_LQ ; 
 int LQIPHASE_NLQ ; 
 int /*<<< orphan*/  LQISTAT1 ; 
 int LQOBUSFREE ; 
 int /*<<< orphan*/  LQOSTAT0 ; 
 int /*<<< orphan*/  LQOSTAT1 ; 
 int NOT_IDENTIFIED ; 
 int NTRAMPERR ; 
 int OSRAMPERR ; 
 int OVERRUN ; 
 int P_BUSFREE ; 
 int /*<<< orphan*/  SBLKCTL ; 
 int SCB_PACKETIZED ; 
 int SCSIPERR ; 
 int SCSIRSTI ; 
 int /*<<< orphan*/  SCSISEQ0 ; 
 int SELDI ; 
 int SELDO ; 
 int SELTO ; 
 int /*<<< orphan*/  SEQ_FLAGS ; 
 int /*<<< orphan*/  SIMODE0 ; 
 int /*<<< orphan*/  SIMODE1 ; 
 int /*<<< orphan*/  SSTAT0 ; 
 int /*<<< orphan*/  SSTAT1 ; 
 int /*<<< orphan*/  SSTAT2 ; 
 int /*<<< orphan*/  SSTAT3 ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WAITING_TID_HEAD ; 
 int /*<<< orphan*/  ahd_clear_critical_section (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_clear_fifo (struct ahd_softc*,int) ; 
 int /*<<< orphan*/  ahd_clear_intstat (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_clear_msg_state (struct ahd_softc*) ; 
 int ahd_debug ; 
 int /*<<< orphan*/  ahd_dump_card_state (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_freeze_devq (struct ahd_softc*,struct scb*) ; 
 int ahd_get_scbptr (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_handle_devreset (struct ahd_softc*,struct ahd_devinfo*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ahd_handle_lqiphase_error (struct ahd_softc*,int) ; 
 int ahd_handle_nonpkt_busfree (struct ahd_softc*) ; 
 int ahd_handle_pkt_busfree (struct ahd_softc*,int) ; 
 int /*<<< orphan*/  ahd_handle_transmission_error (struct ahd_softc*) ; 
 int ahd_inb (struct ahd_softc*,int /*<<< orphan*/ ) ; 
 int ahd_inw (struct ahd_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_iocell_first_selection (struct ahd_softc*) ; 
 struct scb* ahd_lookup_scb (struct ahd_softc*,int) ; 
 char* ahd_name (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_outb (struct ahd_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ahd_pause (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_print_path (struct ahd_softc*,struct scb*) ; 
 int /*<<< orphan*/  ahd_reset_channel (struct ahd_softc*,char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_restart (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_scb_devinfo (struct ahd_softc*,struct ahd_devinfo*,struct scb*) ; 
 int /*<<< orphan*/  ahd_set_modes (struct ahd_softc*,int,int) ; 
 int /*<<< orphan*/  ahd_setup_iocell_workaround (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_unpause (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_update_modes (struct ahd_softc*) ; 
 int /*<<< orphan*/  aic_set_transaction_status (struct scb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void
ahd_handle_scsiint(struct ahd_softc *ahd, u_int intstat)
{
	struct scb	*scb;
	u_int		 status0;
	u_int		 status3;
	u_int		 status;
	u_int		 lqistat1;
	u_int		 lqostat0;
	u_int		 scbid;
	u_int		 busfreetime;

	ahd_update_modes(ahd);
	ahd_set_modes(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI);

	status3 = ahd_inb(ahd, SSTAT3) & (NTRAMPERR|OSRAMPERR);
	status0 = ahd_inb(ahd, SSTAT0) & (IOERR|OVERRUN|SELDI|SELDO);
	status = ahd_inb(ahd, SSTAT1) & (SELTO|SCSIRSTI|BUSFREE|SCSIPERR);
	lqistat1 = ahd_inb(ahd, LQISTAT1);
	lqostat0 = ahd_inb(ahd, LQOSTAT0);
	busfreetime = ahd_inb(ahd, SSTAT2) & BUSFREETIME;
	if ((status0 & (SELDI|SELDO)) != 0) {
		u_int simode0;

		ahd_set_modes(ahd, AHD_MODE_CFG, AHD_MODE_CFG);
		simode0 = ahd_inb(ahd, SIMODE0);
		status0 &= simode0 & (IOERR|OVERRUN|SELDI|SELDO);
		ahd_set_modes(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI);
	}
	scbid = ahd_get_scbptr(ahd);
	scb = ahd_lookup_scb(ahd, scbid);
	if (scb != NULL
	 && (ahd_inb(ahd, SEQ_FLAGS) & NOT_IDENTIFIED) != 0)
		scb = NULL;

	if ((status0 & IOERR) != 0) {
		u_int now_lvd;

		now_lvd = ahd_inb(ahd, SBLKCTL) & ENAB40;
		printf("%s: Transceiver State Has Changed to %s mode\n",
		       ahd_name(ahd), now_lvd ? "LVD" : "SE");
		ahd_outb(ahd, CLRSINT0, CLRIOERR);
		/*
		 * A change in I/O mode is equivalent to a bus reset.
		 */
		ahd_reset_channel(ahd, 'A', /*Initiate Reset*/TRUE);
		ahd_pause(ahd);
		ahd_setup_iocell_workaround(ahd);
		ahd_unpause(ahd);
	} else if ((status0 & OVERRUN) != 0) {

		printf("%s: SCSI offset overrun detected.  Resetting bus.\n",
		       ahd_name(ahd));
		AHD_CORRECTABLE_ERROR(ahd);
		ahd_reset_channel(ahd, 'A', /*Initiate Reset*/TRUE);
	} else if ((status & SCSIRSTI) != 0) {

		printf("%s: Someone reset channel A\n", ahd_name(ahd));
		ahd_reset_channel(ahd, 'A', /*Initiate Reset*/FALSE);
		AHD_UNCORRECTABLE_ERROR(ahd);
	} else if ((status & SCSIPERR) != 0) {

		/* Make sure the sequencer is in a safe location. */
		ahd_clear_critical_section(ahd);

		ahd_handle_transmission_error(ahd);
	} else if (lqostat0 != 0) {

		printf("%s: lqostat0 == 0x%x!\n", ahd_name(ahd), lqostat0);
		ahd_outb(ahd, CLRLQOINT0, lqostat0);
		if ((ahd->bugs & AHD_CLRLQO_AUTOCLR_BUG) != 0)
			ahd_outb(ahd, CLRLQOINT1, 0);
	} else if ((status & SELTO) != 0) {
		u_int  scbid;

		/* Stop the selection */
		ahd_outb(ahd, SCSISEQ0, 0);

		/* Make sure the sequencer is in a safe location. */
		ahd_clear_critical_section(ahd);

		/* No more pending messages */
		ahd_clear_msg_state(ahd);

		/* Clear interrupt state */
		ahd_outb(ahd, CLRSINT1, CLRSELTIMEO|CLRBUSFREE|CLRSCSIPERR);

		/*
		 * Although the driver does not care about the
		 * 'Selection in Progress' status bit, the busy
		 * LED does.  SELINGO is only cleared by a successful
		 * selection, so we must manually clear it to insure
		 * the LED turns off just incase no future successful
		 * selections occur (e.g. no devices on the bus).
		 */
		ahd_outb(ahd, CLRSINT0, CLRSELINGO);

		scbid = ahd_inw(ahd, WAITING_TID_HEAD);
		scb = ahd_lookup_scb(ahd, scbid);
		if (scb == NULL) {
			printf("%s: ahd_intr - referenced scb not "
			       "valid during SELTO scb(0x%x)\n",
			       ahd_name(ahd), scbid);
			ahd_dump_card_state(ahd);
			AHD_UNCORRECTABLE_ERROR(ahd);
		} else {
			struct ahd_devinfo devinfo;
#ifdef AHD_DEBUG
			if ((ahd_debug & AHD_SHOW_SELTO) != 0) {
				ahd_print_path(ahd, scb);
				printf("Saw Selection Timeout for SCB 0x%x\n",
				       scbid);
			}
#endif
			ahd_scb_devinfo(ahd, &devinfo, scb);
			aic_set_transaction_status(scb, CAM_SEL_TIMEOUT);
			ahd_freeze_devq(ahd, scb);

			/*
			 * Cancel any pending transactions on the device
			 * now that it seems to be missing.  This will
			 * also revert us to async/narrow transfers until
			 * we can renegotiate with the device.
			 */
			ahd_handle_devreset(ahd, &devinfo,
					    CAM_LUN_WILDCARD,
					    CAM_SEL_TIMEOUT,
					    "Selection Timeout",
					    /*verbose_level*/1);
		}
		ahd_outb(ahd, CLRINT, CLRSCSIINT);
		ahd_iocell_first_selection(ahd);
		ahd_unpause(ahd);
	} else if ((status0 & (SELDI|SELDO)) != 0) {

		ahd_iocell_first_selection(ahd);
		ahd_unpause(ahd);
	} else if (status3 != 0) {
		printf("%s: SCSI Cell parity error SSTAT3 == 0x%x\n",
		       ahd_name(ahd), status3);
		AHD_CORRECTABLE_ERROR(ahd);
		ahd_outb(ahd, CLRSINT3, status3);
	} else if ((lqistat1 & (LQIPHASE_LQ|LQIPHASE_NLQ)) != 0) {

		/* Make sure the sequencer is in a safe location. */
		ahd_clear_critical_section(ahd);

		ahd_handle_lqiphase_error(ahd, lqistat1);
	} else if ((lqistat1 & LQICRCI_NLQ) != 0) {
		/*
		 * This status can be delayed during some
		 * streaming operations.  The SCSIPHASE
		 * handler has already dealt with this case
		 * so just clear the error.
		 */
		ahd_outb(ahd, CLRLQIINT1, CLRLQICRCI_NLQ);
	} else if ((status & BUSFREE) != 0
		|| (lqistat1 & LQOBUSFREE) != 0) {
		u_int lqostat1;
		int   restart;
		int   clear_fifo;
		int   packetized;
		u_int mode;

		/*
		 * Clear our selection hardware as soon as possible.
		 * We may have an entry in the waiting Q for this target,
		 * that is affected by this busfree and we don't want to
		 * go about selecting the target while we handle the event.
		 */
		ahd_outb(ahd, SCSISEQ0, 0);

		/* Make sure the sequencer is in a safe location. */
		ahd_clear_critical_section(ahd);

		/*
		 * Determine what we were up to at the time of
		 * the busfree.
		 */
		mode = AHD_MODE_SCSI;
		busfreetime = ahd_inb(ahd, SSTAT2) & BUSFREETIME;
		lqostat1 = ahd_inb(ahd, LQOSTAT1);
		switch (busfreetime) {
		case BUSFREE_DFF0:
		case BUSFREE_DFF1:
		{
			u_int	scbid;
			struct	scb *scb;

			mode = busfreetime == BUSFREE_DFF0
			     ? AHD_MODE_DFF0 : AHD_MODE_DFF1;
			ahd_set_modes(ahd, mode, mode);
			scbid = ahd_get_scbptr(ahd);
			scb = ahd_lookup_scb(ahd, scbid);
			if (scb == NULL) {
				printf("%s: Invalid SCB %d in DFF%d "
				       "during unexpected busfree\n",
				       ahd_name(ahd), scbid, mode);
				packetized = 0;
				AHD_CORRECTABLE_ERROR(ahd);
			} else
				packetized = (scb->flags & SCB_PACKETIZED) != 0;
			clear_fifo = 1;
			break;
		}
		case BUSFREE_LQO:
			clear_fifo = 0;
			packetized = 1;
			break;
		default:
			clear_fifo = 0;
			packetized =  (lqostat1 & LQOBUSFREE) != 0;
			if (!packetized
			 && ahd_inb(ahd, LASTPHASE) == P_BUSFREE
			 && (ahd_inb(ahd, SSTAT0) & SELDI) == 0
			 && ((ahd_inb(ahd, SSTAT0) & SELDO) == 0
			  || (ahd_inb(ahd, SCSISEQ0) & ENSELO) == 0))
				/*
				 * Assume packetized if we are not
				 * on the bus in a non-packetized
				 * capacity and any pending selection
				 * was a packetized selection.
				 */
				packetized = 1;
			break;
		}

#ifdef AHD_DEBUG
		if ((ahd_debug & AHD_SHOW_MISC) != 0)
			printf("Saw Busfree.  Busfreetime = 0x%x.\n",
			       busfreetime);
#endif
		/*
		 * Busfrees that occur in non-packetized phases are
		 * handled by the nonpkt_busfree handler.
		 */
		if (packetized && ahd_inb(ahd, LASTPHASE) == P_BUSFREE) {
			restart = ahd_handle_pkt_busfree(ahd, busfreetime);
		} else {
			packetized = 0;
			restart = ahd_handle_nonpkt_busfree(ahd);
		}
		/*
		 * Clear the busfree interrupt status.  The setting of
		 * the interrupt is a pulse, so in a perfect world, we
		 * would not need to muck with the ENBUSFREE logic.  This
		 * would ensure that if the bus moves on to another
		 * connection, busfree protection is still in force.  If
		 * BUSFREEREV is broken, however, we must manually clear
		 * the ENBUSFREE if the busfree occurred during a non-pack
		 * connection so that we don't get false positives during
		 * future, packetized, connections.
		 */
		ahd_outb(ahd, CLRSINT1, CLRBUSFREE);
		if (packetized == 0
		 && (ahd->bugs & AHD_BUSFREEREV_BUG) != 0)
			ahd_outb(ahd, SIMODE1,
				 ahd_inb(ahd, SIMODE1) & ~ENBUSFREE);

		if (clear_fifo)
			ahd_clear_fifo(ahd, mode);

		ahd_clear_msg_state(ahd);
		ahd_outb(ahd, CLRINT, CLRSCSIINT);
		if (restart) {
			ahd_restart(ahd);
		} else {
			ahd_unpause(ahd);
		}
	} else {
		printf("%s: Missing case in ahd_handle_scsiint. status = %x\n",
		       ahd_name(ahd), status);
		ahd_dump_card_state(ahd);
		ahd_clear_intstat(ahd);
		ahd_unpause(ahd);
	}
}