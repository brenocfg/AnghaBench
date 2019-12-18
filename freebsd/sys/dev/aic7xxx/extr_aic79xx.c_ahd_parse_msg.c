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
struct ahd_tmode_tstate {struct ahd_tmode_lstate** enabled_luns; } ;
struct ahd_tmode_lstate {int dummy; } ;
struct ahd_softc {int* msgin_buf; int msgin_index; int msgout_len; int* msgout_buf; scalar_t__ msgout_index; int /*<<< orphan*/  msg_flags; struct ahd_tmode_tstate** enabled_targets; } ;
struct TYPE_2__ {int width; } ;
struct ahd_initiator_tinfo {TYPE_1__ curr; } ;
struct ahd_devinfo {int channel; size_t our_scsiid; int target; int lun; int /*<<< orphan*/  role; } ;

/* Variables and functions */
 int /*<<< orphan*/  AHDMSG_EXT ; 
 int /*<<< orphan*/  AHD_NEG_ALWAYS ; 
 int AHD_SHOW_MESSAGES ; 
 int AHD_TRANS_ACTIVE ; 
 int AHD_TRANS_GOAL ; 
 int /*<<< orphan*/  CAM_BDR_SENT ; 
 int /*<<< orphan*/  CAM_LUN_WILDCARD ; 
 int /*<<< orphan*/  CAM_REQ_ABORTED ; 
 int FALSE ; 
 int /*<<< orphan*/  INITIATOR_TAG ; 
 int MSGLOOP_IN_PROG ; 
 int MSGLOOP_MSGCOMPLETE ; 
 int MSGLOOP_TERMINATED ; 
#define  MSG_ABORT 144 
#define  MSG_ABORT_TAG 143 
#define  MSG_BUS_DEV_RESET 142 
#define  MSG_CLEAR_QUEUE 141 
#define  MSG_CMDCOMPLETE 140 
#define  MSG_DISCONNECT 139 
#define  MSG_EXTENDED 138 
#define  MSG_EXT_PPR 137 
 int MSG_EXT_PPR_DT_REQ ; 
 int MSG_EXT_PPR_LEN ; 
 int MSG_EXT_PPR_QAS_REQ ; 
#define  MSG_EXT_SDTR 136 
 int MSG_EXT_SDTR_LEN ; 
#define  MSG_EXT_WDTR 135 
 int MSG_EXT_WDTR_LEN ; 
 int /*<<< orphan*/  MSG_FLAG_EXPECT_QASREJ_BUSFREE ; 
#define  MSG_IGN_WIDE_RESIDUE 134 
#define  MSG_MESSAGE_REJECT 133 
#define  MSG_NOOP 132 
#define  MSG_QAS_REQUEST 131 
#define  MSG_RESTOREPOINTERS 130 
#define  MSG_SAVEDATAPOINTER 129 
#define  MSG_TERM_IO_PROC 128 
 int /*<<< orphan*/  ROLE_INITIATOR ; 
 int /*<<< orphan*/  ROLE_TARGET ; 
 int SCB_LIST_NULL ; 
 int /*<<< orphan*/  SCSISIGI ; 
 int TRUE ; 
 int /*<<< orphan*/  ahd_abort_scbs (struct ahd_softc*,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_build_transfer_msg (struct ahd_softc*,struct ahd_devinfo*) ; 
 int /*<<< orphan*/  ahd_construct_ppr (struct ahd_softc*,struct ahd_devinfo*,int,int,int,int) ; 
 int /*<<< orphan*/  ahd_construct_sdtr (struct ahd_softc*,struct ahd_devinfo*,int,int) ; 
 int /*<<< orphan*/  ahd_construct_wdtr (struct ahd_softc*,struct ahd_devinfo*,int) ; 
 int ahd_debug ; 
 int /*<<< orphan*/  ahd_devlimited_syncrate (struct ahd_softc*,struct ahd_initiator_tinfo*,int*,int*,int /*<<< orphan*/ ) ; 
 struct ahd_initiator_tinfo* ahd_fetch_transinfo (struct ahd_softc*,int,size_t,int,struct ahd_tmode_tstate**) ; 
 int /*<<< orphan*/  ahd_handle_devreset (struct ahd_softc*,struct ahd_devinfo*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int ahd_handle_msg_reject (struct ahd_softc*,struct ahd_devinfo*) ; 
 int ahd_inb (struct ahd_softc*,int /*<<< orphan*/ ) ; 
 char* ahd_name (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_queue_lstate_event (struct ahd_softc*,struct ahd_tmode_lstate*,size_t,int const,int) ; 
 int /*<<< orphan*/  ahd_restart (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_send_lstate_events (struct ahd_softc*,struct ahd_tmode_lstate*) ; 
 int /*<<< orphan*/  ahd_sent_msg (struct ahd_softc*,int /*<<< orphan*/ ,int const,int) ; 
 int /*<<< orphan*/  ahd_set_syncrate (struct ahd_softc*,struct ahd_devinfo*,int,int,int,int,int) ; 
 int /*<<< orphan*/  ahd_set_width (struct ahd_softc*,struct ahd_devinfo*,int,int,int) ; 
 int /*<<< orphan*/  ahd_update_neg_request (struct ahd_softc*,struct ahd_devinfo*,struct ahd_tmode_tstate*,struct ahd_initiator_tinfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_validate_offset (struct ahd_softc*,struct ahd_initiator_tinfo*,int,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_validate_width (struct ahd_softc*,struct ahd_initiator_tinfo*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bootverbose ; 
 int /*<<< orphan*/  printf (char*,char*,int,...) ; 

__attribute__((used)) static int
ahd_parse_msg(struct ahd_softc *ahd, struct ahd_devinfo *devinfo)
{
	struct	ahd_initiator_tinfo *tinfo;
	struct	ahd_tmode_tstate *tstate;
	int	reject;
	int	done;
	int	response;

	done = MSGLOOP_IN_PROG;
	response = FALSE;
	reject = FALSE;
	tinfo = ahd_fetch_transinfo(ahd, devinfo->channel, devinfo->our_scsiid,
				    devinfo->target, &tstate);

	/*
	 * Parse as much of the message as is available,
	 * rejecting it if we don't support it.  When
	 * the entire message is available and has been
	 * handled, return MSGLOOP_MSGCOMPLETE, indicating
	 * that we have parsed an entire message.
	 *
	 * In the case of extended messages, we accept the length
	 * byte outright and perform more checking once we know the
	 * extended message type.
	 */
	switch (ahd->msgin_buf[0]) {
	case MSG_DISCONNECT:
	case MSG_SAVEDATAPOINTER:
	case MSG_CMDCOMPLETE:
	case MSG_RESTOREPOINTERS:
	case MSG_IGN_WIDE_RESIDUE:
		/*
		 * End our message loop as these are messages
		 * the sequencer handles on its own.
		 */
		done = MSGLOOP_TERMINATED;
		break;
	case MSG_MESSAGE_REJECT:
		response = ahd_handle_msg_reject(ahd, devinfo);
		/* FALLTHROUGH */
	case MSG_NOOP:
		done = MSGLOOP_MSGCOMPLETE;
		break;
	case MSG_EXTENDED:
	{
		/* Wait for enough of the message to begin validation */
		if (ahd->msgin_index < 2)
			break;
		switch (ahd->msgin_buf[2]) {
		case MSG_EXT_SDTR:
		{
			u_int	 period;
			u_int	 ppr_options;
			u_int	 offset;
			u_int	 saved_offset;
			
			if (ahd->msgin_buf[1] != MSG_EXT_SDTR_LEN) {
				reject = TRUE;
				break;
			}

			/*
			 * Wait until we have both args before validating
			 * and acting on this message.
			 *
			 * Add one to MSG_EXT_SDTR_LEN to account for
			 * the extended message preamble.
			 */
			if (ahd->msgin_index < (MSG_EXT_SDTR_LEN + 1))
				break;

			period = ahd->msgin_buf[3];
			ppr_options = 0;
			saved_offset = offset = ahd->msgin_buf[4];
			ahd_devlimited_syncrate(ahd, tinfo, &period,
						&ppr_options, devinfo->role);
			ahd_validate_offset(ahd, tinfo, period, &offset,
					    tinfo->curr.width, devinfo->role);
			if (bootverbose) {
				printf("(%s:%c:%d:%d): Received "
				       "SDTR period %x, offset %x\n\t"
				       "Filtered to period %x, offset %x\n",
				       ahd_name(ahd), devinfo->channel,
				       devinfo->target, devinfo->lun,
				       ahd->msgin_buf[3], saved_offset,
				       period, offset);
			}
			ahd_set_syncrate(ahd, devinfo, period,
					 offset, ppr_options,
					 AHD_TRANS_ACTIVE|AHD_TRANS_GOAL,
					 /*paused*/TRUE);

			/*
			 * See if we initiated Sync Negotiation
			 * and didn't have to fall down to async
			 * transfers.
			 */
			if (ahd_sent_msg(ahd, AHDMSG_EXT, MSG_EXT_SDTR, TRUE)) {
				/* We started it */
				if (saved_offset != offset) {
					/* Went too low - force async */
					reject = TRUE;
				}
			} else {
				/*
				 * Send our own SDTR in reply
				 */
				if (bootverbose
				 && devinfo->role == ROLE_INITIATOR) {
					printf("(%s:%c:%d:%d): Target "
					       "Initiated SDTR\n",
					       ahd_name(ahd), devinfo->channel,
					       devinfo->target, devinfo->lun);
				}
				ahd->msgout_index = 0;
				ahd->msgout_len = 0;
				ahd_construct_sdtr(ahd, devinfo,
						   period, offset);
				ahd->msgout_index = 0;
				response = TRUE;
			}
			done = MSGLOOP_MSGCOMPLETE;
			break;
		}
		case MSG_EXT_WDTR:
		{
			u_int bus_width;
			u_int saved_width;
			u_int sending_reply;

			sending_reply = FALSE;
			if (ahd->msgin_buf[1] != MSG_EXT_WDTR_LEN) {
				reject = TRUE;
				break;
			}

			/*
			 * Wait until we have our arg before validating
			 * and acting on this message.
			 *
			 * Add one to MSG_EXT_WDTR_LEN to account for
			 * the extended message preamble.
			 */
			if (ahd->msgin_index < (MSG_EXT_WDTR_LEN + 1))
				break;

			bus_width = ahd->msgin_buf[3];
			saved_width = bus_width;
			ahd_validate_width(ahd, tinfo, &bus_width,
					   devinfo->role);
			if (bootverbose) {
				printf("(%s:%c:%d:%d): Received WDTR "
				       "%x filtered to %x\n",
				       ahd_name(ahd), devinfo->channel,
				       devinfo->target, devinfo->lun,
				       saved_width, bus_width);
			}

			if (ahd_sent_msg(ahd, AHDMSG_EXT, MSG_EXT_WDTR, TRUE)) {
				/*
				 * Don't send a WDTR back to the
				 * target, since we asked first.
				 * If the width went higher than our
				 * request, reject it.
				 */
				if (saved_width > bus_width) {
					reject = TRUE;
					printf("(%s:%c:%d:%d): requested %dBit "
					       "transfers.  Rejecting...\n",
					       ahd_name(ahd), devinfo->channel,
					       devinfo->target, devinfo->lun,
					       8 * (0x01 << bus_width));
					bus_width = 0;
				}
			} else {
				/*
				 * Send our own WDTR in reply
				 */
				if (bootverbose
				 && devinfo->role == ROLE_INITIATOR) {
					printf("(%s:%c:%d:%d): Target "
					       "Initiated WDTR\n",
					       ahd_name(ahd), devinfo->channel,
					       devinfo->target, devinfo->lun);
				}
				ahd->msgout_index = 0;
				ahd->msgout_len = 0;
				ahd_construct_wdtr(ahd, devinfo, bus_width);
				ahd->msgout_index = 0;
				response = TRUE;
				sending_reply = TRUE;
			}
			/*
			 * After a wide message, we are async, but
			 * some devices don't seem to honor this portion
			 * of the spec.  Force a renegotiation of the
			 * sync component of our transfer agreement even
			 * if our goal is async.  By updating our width
			 * after forcing the negotiation, we avoid
			 * renegotiating for width.
			 */
			ahd_update_neg_request(ahd, devinfo, tstate,
					       tinfo, AHD_NEG_ALWAYS);
			ahd_set_width(ahd, devinfo, bus_width,
				      AHD_TRANS_ACTIVE|AHD_TRANS_GOAL,
				      /*paused*/TRUE);
			if (sending_reply == FALSE && reject == FALSE) {

				/*
				 * We will always have an SDTR to send.
				 */
				ahd->msgout_index = 0;
				ahd->msgout_len = 0;
				ahd_build_transfer_msg(ahd, devinfo);
				ahd->msgout_index = 0;
				response = TRUE;
			}
			done = MSGLOOP_MSGCOMPLETE;
			break;
		}
		case MSG_EXT_PPR:
		{
			u_int	period;
			u_int	offset;
			u_int	bus_width;
			u_int	ppr_options;
			u_int	saved_width;
			u_int	saved_offset;
			u_int	saved_ppr_options;

			if (ahd->msgin_buf[1] != MSG_EXT_PPR_LEN) {
				reject = TRUE;
				break;
			}

			/*
			 * Wait until we have all args before validating
			 * and acting on this message.
			 *
			 * Add one to MSG_EXT_PPR_LEN to account for
			 * the extended message preamble.
			 */
			if (ahd->msgin_index < (MSG_EXT_PPR_LEN + 1))
				break;

			period = ahd->msgin_buf[3];
			offset = ahd->msgin_buf[5];
			bus_width = ahd->msgin_buf[6];
			saved_width = bus_width;
			ppr_options = ahd->msgin_buf[7];
			/*
			 * According to the spec, a DT only
			 * period factor with no DT option
			 * set implies async.
			 */
			if ((ppr_options & MSG_EXT_PPR_DT_REQ) == 0
			 && period <= 9)
				offset = 0;
			saved_ppr_options = ppr_options;
			saved_offset = offset;

			/*
			 * Transfer options are only available if we
			 * are negotiating wide.
			 */
			if (bus_width == 0)
				ppr_options &= MSG_EXT_PPR_QAS_REQ;

			ahd_validate_width(ahd, tinfo, &bus_width,
					   devinfo->role);
			ahd_devlimited_syncrate(ahd, tinfo, &period,
						&ppr_options, devinfo->role);
			ahd_validate_offset(ahd, tinfo, period, &offset,
					    bus_width, devinfo->role);

			if (ahd_sent_msg(ahd, AHDMSG_EXT, MSG_EXT_PPR, TRUE)) {
				/*
				 * If we are unable to do any of the
				 * requested options (we went too low),
				 * then we'll have to reject the message.
				 */
				if (saved_width > bus_width
				 || saved_offset != offset
				 || saved_ppr_options != ppr_options) {
					reject = TRUE;
					period = 0;
					offset = 0;
					bus_width = 0;
					ppr_options = 0;
				}
			} else {
				if (devinfo->role != ROLE_TARGET)
					printf("(%s:%c:%d:%d): Target "
					       "Initiated PPR\n",
					       ahd_name(ahd), devinfo->channel,
					       devinfo->target, devinfo->lun);
				else
					printf("(%s:%c:%d:%d): Initiator "
					       "Initiated PPR\n",
					       ahd_name(ahd), devinfo->channel,
					       devinfo->target, devinfo->lun);
				ahd->msgout_index = 0;
				ahd->msgout_len = 0;
				ahd_construct_ppr(ahd, devinfo, period, offset,
						  bus_width, ppr_options);
				ahd->msgout_index = 0;
				response = TRUE;
			}
			if (bootverbose) {
				printf("(%s:%c:%d:%d): Received PPR width %x, "
				       "period %x, offset %x,options %x\n"
				       "\tFiltered to width %x, period %x, "
				       "offset %x, options %x\n",
				       ahd_name(ahd), devinfo->channel,
				       devinfo->target, devinfo->lun,
				       saved_width, ahd->msgin_buf[3],
				       saved_offset, saved_ppr_options,
				       bus_width, period, offset, ppr_options);
			}
			ahd_set_width(ahd, devinfo, bus_width,
				      AHD_TRANS_ACTIVE|AHD_TRANS_GOAL,
				      /*paused*/TRUE);
			ahd_set_syncrate(ahd, devinfo, period,
					 offset, ppr_options,
					 AHD_TRANS_ACTIVE|AHD_TRANS_GOAL,
					 /*paused*/TRUE);

			done = MSGLOOP_MSGCOMPLETE;
			break;
		}
		default:
			/* Unknown extended message.  Reject it. */
			reject = TRUE;
			break;
		}
		break;
	}
#ifdef AHD_TARGET_MODE
	case MSG_BUS_DEV_RESET:
		ahd_handle_devreset(ahd, devinfo, CAM_LUN_WILDCARD,
				    CAM_BDR_SENT,
				    "Bus Device Reset Received",
				    /*verbose_level*/0);
		ahd_restart(ahd);
		done = MSGLOOP_TERMINATED;
		break;
	case MSG_ABORT_TAG:
	case MSG_ABORT:
	case MSG_CLEAR_QUEUE:
	{
		int tag;

		/* Target mode messages */
		if (devinfo->role != ROLE_TARGET) {
			reject = TRUE;
			break;
		}
		tag = SCB_LIST_NULL;
		if (ahd->msgin_buf[0] == MSG_ABORT_TAG)
			tag = ahd_inb(ahd, INITIATOR_TAG);
		ahd_abort_scbs(ahd, devinfo->target, devinfo->channel,
			       devinfo->lun, tag, ROLE_TARGET,
			       CAM_REQ_ABORTED);

		tstate = ahd->enabled_targets[devinfo->our_scsiid];
		if (tstate != NULL) {
			struct ahd_tmode_lstate* lstate;

			lstate = tstate->enabled_luns[devinfo->lun];
			if (lstate != NULL) {
				ahd_queue_lstate_event(ahd, lstate,
						       devinfo->our_scsiid,
						       ahd->msgin_buf[0],
						       /*arg*/tag);
				ahd_send_lstate_events(ahd, lstate);
			}
		}
		ahd_restart(ahd);
		done = MSGLOOP_TERMINATED;
		break;
	}
#endif
	case MSG_QAS_REQUEST:
#ifdef AHD_DEBUG
		if ((ahd_debug & AHD_SHOW_MESSAGES) != 0)
			printf("%s: QAS request.  SCSISIGI == 0x%x\n",
			       ahd_name(ahd), ahd_inb(ahd, SCSISIGI));
#endif
		ahd->msg_flags |= MSG_FLAG_EXPECT_QASREJ_BUSFREE;
		/* FALLTHROUGH */
	case MSG_TERM_IO_PROC:
	default:
		reject = TRUE;
		break;
	}

	if (reject) {
		/*
		 * Setup to reject the message.
		 */
		ahd->msgout_index = 0;
		ahd->msgout_len = 1;
		ahd->msgout_buf[0] = MSG_MESSAGE_REJECT;
		done = MSGLOOP_MSGCOMPLETE;
		response = TRUE;
	}

	if (done != MSGLOOP_IN_PROG && !response)
		/* Clear the outgoing message buffer */
		ahd->msgout_len = 0;

	return (done);
}