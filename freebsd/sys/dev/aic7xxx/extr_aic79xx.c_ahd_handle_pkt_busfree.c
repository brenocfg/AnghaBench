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
typedef  scalar_t__ u_int ;
struct scb {scalar_t__ crc_retry_count; } ;
struct ahd_softc {int bugs; scalar_t__ src_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  AHD_ASSERT_MODES (struct ahd_softc*,int,int) ; 
 int AHD_CLRLQO_AUTOCLR_BUG ; 
 int /*<<< orphan*/  AHD_CORRECTABLE_ERROR (struct ahd_softc*) ; 
 scalar_t__ AHD_MAX_LQ_CRC_ERRORS ; 
 int AHD_MODE_CFG_MSK ; 
 scalar_t__ AHD_MODE_SCSI ; 
 int AHD_MODE_UNKNOWN_MSK ; 
 int AHD_SHOW_MASKED_ERRORS ; 
 int /*<<< orphan*/  AHD_UNCORRECTABLE_ERROR (struct ahd_softc*) ; 
 int /*<<< orphan*/  CAM_UNCOR_PARITY ; 
 int /*<<< orphan*/  CAM_UNEXP_BUSFREE ; 
 scalar_t__ CLRBUSFREE ; 
 scalar_t__ CLRLQOBUSFREE ; 
 int /*<<< orphan*/  CLRLQOINT1 ; 
 scalar_t__ CLRSCSIPERR ; 
 scalar_t__ CLRSELDO ; 
 int /*<<< orphan*/  CLRSINT0 ; 
 int /*<<< orphan*/  CLRSINT1 ; 
 int /*<<< orphan*/  CURRSCB ; 
 scalar_t__ ENSELO ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  LQCTL2 ; 
 scalar_t__ LQOBUSFREE ; 
 int /*<<< orphan*/  LQOSTAT1 ; 
 scalar_t__ LQOTOIDLE ; 
 scalar_t__ PARITYERR ; 
 int /*<<< orphan*/  PERRDIAG ; 
 int /*<<< orphan*/  ROLE_INITIATOR ; 
 int /*<<< orphan*/  SCB_GET_LUN (struct scb*) ; 
 int /*<<< orphan*/  SCB_GET_TAG (struct scb*) ; 
 int /*<<< orphan*/  SCB_GET_TARGET (struct ahd_softc*,struct scb*) ; 
 scalar_t__ SCB_IS_SILENT (struct scb*) ; 
 scalar_t__ SCB_LIST_NULL ; 
 int /*<<< orphan*/  SCB_NEXT2 ; 
 int /*<<< orphan*/  SCSISEQ0 ; 
 int /*<<< orphan*/  WAITING_TID_HEAD ; 
 int /*<<< orphan*/  WAITING_TID_TAIL ; 
 int /*<<< orphan*/  ahd_abort_scbs (struct ahd_softc*,int /*<<< orphan*/ ,char,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ahd_debug ; 
 int /*<<< orphan*/  ahd_dump_card_state (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_flush_device_writes (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_freeze_devq (struct ahd_softc*,struct scb*) ; 
 scalar_t__ ahd_get_scbptr (struct ahd_softc*) ; 
 scalar_t__ ahd_inb (struct ahd_softc*,int /*<<< orphan*/ ) ; 
 scalar_t__ ahd_inw (struct ahd_softc*,int /*<<< orphan*/ ) ; 
 scalar_t__ ahd_inw_scbram (struct ahd_softc*,int /*<<< orphan*/ ) ; 
 struct scb* ahd_lookup_scb (struct ahd_softc*,scalar_t__) ; 
 char* ahd_name (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_outb (struct ahd_softc*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ahd_outw (struct ahd_softc*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ahd_print_path (struct ahd_softc*,struct scb*) ; 
 int /*<<< orphan*/  ahd_set_modes (struct ahd_softc*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ahd_set_scbptr (struct ahd_softc*,scalar_t__) ; 
 int /*<<< orphan*/  aic_freeze_scb (struct scb*) ; 
 int /*<<< orphan*/  aic_set_transaction_status (struct scb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static int
ahd_handle_pkt_busfree(struct ahd_softc *ahd, u_int busfreetime)
{
	u_int lqostat1;

	AHD_ASSERT_MODES(ahd, ~(AHD_MODE_UNKNOWN_MSK|AHD_MODE_CFG_MSK),
			 ~(AHD_MODE_UNKNOWN_MSK|AHD_MODE_CFG_MSK));
	lqostat1 = ahd_inb(ahd, LQOSTAT1);
	if ((lqostat1 & LQOBUSFREE) != 0) {
		struct scb *scb;
		u_int scbid;
		u_int saved_scbptr;
		u_int waiting_h;
		u_int waiting_t;
		u_int next;

		/*
		 * The LQO manager detected an unexpected busfree
		 * either:
		 *
		 * 1) During an outgoing LQ.
		 * 2) After an outgoing LQ but before the first
		 *    REQ of the command packet.
		 * 3) During an outgoing command packet.
		 *
		 * In all cases, CURRSCB is pointing to the
		 * SCB that encountered the failure.  Clean
		 * up the queue, clear SELDO and LQOBUSFREE,
		 * and allow the sequencer to restart the select
		 * out at its lesure.
		 */
		ahd_set_modes(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI);
		scbid = ahd_inw(ahd, CURRSCB);
		scb = ahd_lookup_scb(ahd, scbid);
		if (scb == NULL)
		       panic("SCB not valid during LQOBUSFREE");
		/*
		 * Clear the status.
		 */
		ahd_outb(ahd, CLRLQOINT1, CLRLQOBUSFREE);
		if ((ahd->bugs & AHD_CLRLQO_AUTOCLR_BUG) != 0)
			ahd_outb(ahd, CLRLQOINT1, 0);
		ahd_outb(ahd, SCSISEQ0, ahd_inb(ahd, SCSISEQ0) & ~ENSELO);
		ahd_flush_device_writes(ahd);
		ahd_outb(ahd, CLRSINT0, CLRSELDO);

		/*
		 * Return the LQO manager to its idle loop.  It will
		 * not do this automatically if the busfree occurs
		 * after the first REQ of either the LQ or command
		 * packet or between the LQ and command packet.
		 */
		ahd_outb(ahd, LQCTL2, ahd_inb(ahd, LQCTL2) | LQOTOIDLE);

		/*
		 * Update the waiting for selection queue so
		 * we restart on the correct SCB.
		 */
		waiting_h = ahd_inw(ahd, WAITING_TID_HEAD);
		saved_scbptr = ahd_get_scbptr(ahd);
		if (waiting_h != scbid) {

			ahd_outw(ahd, WAITING_TID_HEAD, scbid);
			waiting_t = ahd_inw(ahd, WAITING_TID_TAIL);
			if (waiting_t == waiting_h) {
				ahd_outw(ahd, WAITING_TID_TAIL, scbid);
				next = SCB_LIST_NULL;
			} else {
				ahd_set_scbptr(ahd, waiting_h);
				next = ahd_inw_scbram(ahd, SCB_NEXT2);
			}
			ahd_set_scbptr(ahd, scbid);
			ahd_outw(ahd, SCB_NEXT2, next);
		}
		ahd_set_scbptr(ahd, saved_scbptr);
		if (scb->crc_retry_count < AHD_MAX_LQ_CRC_ERRORS) {
			if (SCB_IS_SILENT(scb) == FALSE) {
				ahd_print_path(ahd, scb);
				printf("Probable outgoing LQ CRC error.  "
				       "Retrying command\n");
				AHD_CORRECTABLE_ERROR(ahd);
			}
			scb->crc_retry_count++;
		} else {
			aic_set_transaction_status(scb, CAM_UNCOR_PARITY);
			aic_freeze_scb(scb);
			ahd_freeze_devq(ahd, scb);
		}
		/* Return unpausing the sequencer. */
		return (0);
	} else if ((ahd_inb(ahd, PERRDIAG) & PARITYERR) != 0) {
		/*
		 * Ignore what are really parity errors that
		 * occur on the last REQ of a free running
		 * clock prior to going busfree.  Some drives
		 * do not properly active negate just before
		 * going busfree resulting in a parity glitch.
		 */
		ahd_outb(ahd, CLRSINT1, CLRSCSIPERR|CLRBUSFREE);
#ifdef AHD_DEBUG
		if ((ahd_debug & AHD_SHOW_MASKED_ERRORS) != 0)
			printf("%s: Parity on last REQ detected "
			       "during busfree phase.\n",
			       ahd_name(ahd));
#endif
		/* Return unpausing the sequencer. */
		return (0);
	}
	if (ahd->src_mode != AHD_MODE_SCSI) {
		u_int	scbid;
		struct	scb *scb;

		scbid = ahd_get_scbptr(ahd);
		scb = ahd_lookup_scb(ahd, scbid);
		ahd_print_path(ahd, scb);
		printf("Unexpected PKT busfree condition\n");
		AHD_UNCORRECTABLE_ERROR(ahd);
		ahd_dump_card_state(ahd);
		ahd_abort_scbs(ahd, SCB_GET_TARGET(ahd, scb), 'A',
			       SCB_GET_LUN(scb), SCB_GET_TAG(scb),
			       ROLE_INITIATOR, CAM_UNEXP_BUSFREE);

		/* Return restarting the sequencer. */
		return (1);
	}
	printf("%s: Unexpected PKT busfree condition\n", ahd_name(ahd));
	AHD_UNCORRECTABLE_ERROR(ahd);
	ahd_dump_card_state(ahd);
	/* Restart the sequencer. */
	return (1);
}