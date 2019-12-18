#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
struct scb {int flags; TYPE_1__* hscb; } ;
struct ahd_softc {int /*<<< orphan*/  timedout_scbs; } ;
struct TYPE_2__ {int task_management; int control; scalar_t__ task_attribute; scalar_t__ cdb_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  AHD_CORRECTABLE_ERROR (struct ahd_softc*) ; 
 int /*<<< orphan*/  AHD_MODE_SCSI ; 
 int ATNO ; 
 int /*<<< orphan*/  CAM_CMD_TIMEOUT ; 
 int /*<<< orphan*/  CAM_REQUEUE_REQ ; 
 int DISCONNECTED ; 
 int HOST_MSG ; 
 int /*<<< orphan*/  LASTPHASE ; 
 scalar_t__ LIST_EMPTY (int /*<<< orphan*/ *) ; 
 struct scb* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct scb*,int /*<<< orphan*/ ) ; 
 int MK_MESSAGE ; 
 int /*<<< orphan*/  MSG_OUT ; 
 int NOT_IDENTIFIED ; 
 int P_BUSFREE ; 
 int /*<<< orphan*/  ROLE_INITIATOR ; 
 int SCB_ABORT ; 
 int /*<<< orphan*/  SCB_CONTROL ; 
 int SCB_DEVICE_RESET ; 
 char SCB_GET_CHANNEL (struct ahd_softc*,struct scb*) ; 
 int SCB_GET_LUN (struct scb*) ; 
 int SCB_GET_TAG (struct scb*) ; 
 int SCB_GET_TARGET (struct ahd_softc*,struct scb*) ; 
 int SCB_LIST_NULL ; 
 int SCB_PACKETIZED ; 
 int SCB_RECOVERY_SCB ; 
 int /*<<< orphan*/  SCB_TASK_MANAGEMENT ; 
 int SCB_TIMEDOUT ; 
 int /*<<< orphan*/  SCSIPHASE ; 
 int /*<<< orphan*/  SCSISIGO ; 
 int /*<<< orphan*/  SEARCH_COMPLETE ; 
 int /*<<< orphan*/  SEARCH_COUNT ; 
 int /*<<< orphan*/  SEQ_FLAGS ; 
 int SIU_TASKMGMT_ABORT_TASK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ahd_dump_card_state (struct ahd_softc*) ; 
 int ahd_get_scbptr (struct ahd_softc*) ; 
 int ahd_inb (struct ahd_softc*,int /*<<< orphan*/ ) ; 
 int ahd_is_paused (struct ahd_softc*) ; 
 struct scb* ahd_lookup_scb (struct ahd_softc*,int) ; 
 char* ahd_name (struct ahd_softc*) ; 
 scalar_t__ ahd_other_scb_timeout (struct ahd_softc*,struct scb*,struct scb*) ; 
 int /*<<< orphan*/  ahd_outb (struct ahd_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ahd_pause_and_flushwork (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_print_path (struct ahd_softc*,struct scb*) ; 
 int /*<<< orphan*/  ahd_qinfifo_requeue_tail (struct ahd_softc*,struct scb*) ; 
 int ahd_reset_channel (struct ahd_softc*,char,int /*<<< orphan*/ ) ; 
 scalar_t__ ahd_search_qinfifo (struct ahd_softc*,int,char,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_set_modes (struct ahd_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_set_recoveryscb (struct ahd_softc*,struct scb*) ; 
 int /*<<< orphan*/  ahd_set_scbptr (struct ahd_softc*,int) ; 
 int /*<<< orphan*/  ahd_unpause (struct ahd_softc*) ; 
 int /*<<< orphan*/  aic_scb_timer_reset (struct scb*,int) ; 
 int /*<<< orphan*/  aic_set_transaction_status (struct scb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  timedout_links ; 

void
ahd_recover_commands(struct ahd_softc *ahd)
{
	struct	scb *scb;
	struct	scb *active_scb;
	int	found;
	int	was_paused;
	u_int	active_scbptr;
	u_int	last_phase;

	/*
	 * Pause the controller and manually flush any
	 * commands that have just completed but that our
	 * interrupt handler has yet to see.
	 */
	was_paused = ahd_is_paused(ahd);

	printf("%s: Recovery Initiated - Card was %spaused\n", ahd_name(ahd),
	       was_paused ? "" : "not ");
	AHD_CORRECTABLE_ERROR(ahd);
	ahd_dump_card_state(ahd);

	ahd_pause_and_flushwork(ahd);

	if (LIST_EMPTY(&ahd->timedout_scbs) != 0) {
		/*
		 * The timedout commands have already
		 * completed.  This typically means
		 * that either the timeout value was on
		 * the hairy edge of what the device
		 * requires or - more likely - interrupts
		 * are not happening.
		 */
		printf("%s: Timedout SCBs already complete. "
		       "Interrupts may not be functioning.\n", ahd_name(ahd));
		ahd_unpause(ahd);
		return;
	}

	/*
	 * Determine identity of SCB acting on the bus.
	 * This test only catches non-packetized transactions.
	 * Due to the fleeting nature of packetized operations,
	 * we can't easily determine that a packetized operation
	 * is on the bus.
	 */
	ahd_set_modes(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI);
	last_phase = ahd_inb(ahd, LASTPHASE);
	active_scbptr = ahd_get_scbptr(ahd);
	active_scb = NULL;
	if (last_phase != P_BUSFREE
	 || (ahd_inb(ahd, SEQ_FLAGS) & NOT_IDENTIFIED) == 0)
		active_scb = ahd_lookup_scb(ahd, active_scbptr);

	while ((scb = LIST_FIRST(&ahd->timedout_scbs)) != NULL) {
		int	target;
		int	lun;
		char	channel;

		target = SCB_GET_TARGET(ahd, scb);
		channel = SCB_GET_CHANNEL(ahd, scb);
		lun = SCB_GET_LUN(scb);

		ahd_print_path(ahd, scb);
		printf("SCB %d - timed out\n", SCB_GET_TAG(scb));

		if (scb->flags & (SCB_DEVICE_RESET|SCB_ABORT)) {
			/*
			 * Been down this road before.
			 * Do a full bus reset.
			 */
			aic_set_transaction_status(scb, CAM_CMD_TIMEOUT);
bus_reset:
			found = ahd_reset_channel(ahd, channel,
						  /*Initiate Reset*/TRUE);
			printf("%s: Issued Channel %c Bus Reset. "
			       "%d SCBs aborted\n", ahd_name(ahd), channel,
			       found);
			continue;
		}

		/*
		 * Remove the command from the timedout list in
		 * preparation for requeing it.
		 */
		LIST_REMOVE(scb, timedout_links);
		scb->flags &= ~SCB_TIMEDOUT;

		if (active_scb != NULL) {

			if (active_scb != scb) {

				/*
				 * If the active SCB is not us, assume that
				 * the active SCB has a longer timeout than
				 * the timedout SCB, and wait for the active
				 * SCB to timeout.  As a safeguard, only
				 * allow this deferral to continue if some
				 * untimed-out command is outstanding.
				 */ 
				if (ahd_other_scb_timeout(ahd, scb,
							  active_scb) == 0)
					goto bus_reset;
				continue;
			} 

			/*
			 * We're active on the bus, so assert ATN
			 * and hope that the target responds.
			 */
			ahd_set_recoveryscb(ahd, active_scb);
                	active_scb->flags |= SCB_RECOVERY_SCB|SCB_DEVICE_RESET;
			ahd_outb(ahd, MSG_OUT, HOST_MSG);
			ahd_outb(ahd, SCSISIGO, last_phase|ATNO);
			ahd_print_path(ahd, active_scb);
			printf("BDR message in message buffer\n");
			aic_scb_timer_reset(scb, 2 * 1000);
			break;
		} else if (last_phase != P_BUSFREE
			&& ahd_inb(ahd, SCSIPHASE) == 0) {
			/*
			 * SCB is not identified, there
			 * is no pending REQ, and the sequencer
			 * has not seen a busfree.  Looks like
			 * a stuck connection waiting to
			 * go busfree.  Reset the bus.
			 */
			printf("%s: Connection stuck awaiting busfree or "
			       "Identify Msg.\n", ahd_name(ahd));
			goto bus_reset;
		} else if (ahd_search_qinfifo(ahd, target, channel, lun,
					      SCB_GET_TAG(scb),
					      ROLE_INITIATOR, /*status*/0,
					      SEARCH_COUNT) > 0) {

			/*
			 * We haven't even gone out on the bus
			 * yet, so the timeout must be due to
			 * some other command.  Reset the timer
			 * and go on.
			 */
			if (ahd_other_scb_timeout(ahd, scb, NULL) == 0)
				goto bus_reset;
		} else {
			/*
			 * This SCB is for a disconnected transaction
			 * and we haven't found a better candidate on
			 * the bus to explain this timeout.
			 */
			ahd_set_recoveryscb(ahd, scb);

			/*
			 * Actually re-queue this SCB in an attempt
			 * to select the device before it reconnects.
			 * In either case (selection or reselection),
			 * we will now issue a target reset to the
			 * timed-out device.
			 */
			scb->flags |= SCB_DEVICE_RESET;
			scb->hscb->cdb_len = 0;
			scb->hscb->task_attribute = 0;
			scb->hscb->task_management = SIU_TASKMGMT_ABORT_TASK;

			ahd_set_scbptr(ahd, SCB_GET_TAG(scb));
			if ((scb->flags & SCB_PACKETIZED) != 0) {
				/*
				 * Mark the SCB has having an outstanding
				 * task management function.  Should the command
				 * complete normally before the task management
				 * function can be sent, the host will be
				 * notified to abort our requeued SCB.
				 */
				ahd_outb(ahd, SCB_TASK_MANAGEMENT,
					 scb->hscb->task_management);
			} else {
				/*
				 * If non-packetized, set the MK_MESSAGE control
				 * bit indicating that we desire to send a
				 * message.  We also set the disconnected flag
				 * since there is no guarantee that our SCB
				 * control byte matches the version on the
				 * card.  We don't want the sequencer to abort
				 * the command thinking an unsolicited
				 * reselection occurred.
				 */
				scb->hscb->control |= MK_MESSAGE|DISCONNECTED;

				/*
				 * The sequencer will never re-reference the
				 * in-core SCB.  To make sure we are notified
				 * during reslection, set the MK_MESSAGE flag in
				 * the card's copy of the SCB.
				 */
				ahd_outb(ahd, SCB_CONTROL,
					 ahd_inb(ahd, SCB_CONTROL)|MK_MESSAGE);
			}

			/*
			 * Clear out any entries in the QINFIFO first
			 * so we are the next SCB for this target
			 * to run.
			 */
			ahd_search_qinfifo(ahd, target, channel, lun,
					   SCB_LIST_NULL, ROLE_INITIATOR,
					   CAM_REQUEUE_REQ, SEARCH_COMPLETE);
			ahd_qinfifo_requeue_tail(ahd, scb);
			ahd_set_scbptr(ahd, active_scbptr);
			ahd_print_path(ahd, scb);
			printf("Queuing a BDR SCB\n");
			aic_scb_timer_reset(scb, 2 * 1000);
			break;
		}
	}
	
	/*
	 * Any remaining SCBs were not the "culprit", so remove
	 * them from the timeout list.  The timer for these commands
	 * will be reset once the recovery SCB completes.
	 */
	while ((scb = LIST_FIRST(&ahd->timedout_scbs)) != NULL) {

		LIST_REMOVE(scb, timedout_links);
		scb->flags &= ~SCB_TIMEDOUT;
	}

	ahd_unpause(ahd);
}