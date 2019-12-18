#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
struct scb {TYPE_3__* hscb; } ;
struct ahd_tmode_tstate {int dummy; } ;
struct ahd_softc {int msg_flags; scalar_t__ msgout_index; scalar_t__ msgout_len; } ;
struct TYPE_5__ {int transport_version; scalar_t__ offset; } ;
struct TYPE_4__ {scalar_t__ period; int ppr_options; int transport_version; scalar_t__ offset; } ;
struct ahd_initiator_tinfo {TYPE_2__ curr; TYPE_1__ goal; } ;
struct ahd_devinfo {int channel; int target; int lun; int /*<<< orphan*/  our_scsiid; } ;
struct TYPE_6__ {int control; int /*<<< orphan*/  scsiid; } ;

/* Variables and functions */
 int /*<<< orphan*/  AHDMSG_1B ; 
 int /*<<< orphan*/  AHDMSG_EXT ; 
 int /*<<< orphan*/  AHD_QUEUE_BASIC ; 
 int /*<<< orphan*/  AHD_QUEUE_NONE ; 
 scalar_t__ AHD_SYNCRATE_DT ; 
 scalar_t__ AHD_SYNCRATE_PACED ; 
 int AHD_TRANS_ACTIVE ; 
 int AHD_TRANS_GOAL ; 
 int /*<<< orphan*/  BUILD_TCL (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CAM_REQUEUE_REQ ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LAST_MSG ; 
 int MSG_EXT_PPR ; 
 int MSG_EXT_PPR_DT_REQ ; 
 int MSG_EXT_PPR_IU_REQ ; 
 int MSG_EXT_PPR_QAS_REQ ; 
 int MSG_EXT_SDTR ; 
 int MSG_EXT_WDTR ; 
 int /*<<< orphan*/  MSG_EXT_WDTR_BUS_8_BIT ; 
 int MSG_FLAG_EXPECT_PPR_BUSFREE ; 
 int MSG_FLAG_IU_REQ_CHANGED ; 
 int MSG_IDENTIFYFLAG ; 
 int MSG_ORDERED_TASK ; 
 int /*<<< orphan*/  MSG_OUT ; 
 int MSG_SIMPLE_TASK ; 
 int /*<<< orphan*/  ROLE_INITIATOR ; 
 int /*<<< orphan*/  SCB_CONTROL ; 
 int /*<<< orphan*/  SCB_GET_CHANNEL (struct ahd_softc*,struct scb*) ; 
 int /*<<< orphan*/  SCB_GET_LUN (struct scb*) ; 
 int /*<<< orphan*/  SCB_GET_TAG (struct scb*) ; 
 int /*<<< orphan*/  SCB_GET_TARGET (struct ahd_softc*,struct scb*) ; 
 int /*<<< orphan*/  SCB_LIST_NULL ; 
 int /*<<< orphan*/  SEARCH_COMPLETE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ahd_assert_atn (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_build_transfer_msg (struct ahd_softc*,struct ahd_devinfo*) ; 
 int /*<<< orphan*/  ahd_busy_tcl (struct ahd_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ahd_initiator_tinfo* ahd_fetch_transinfo (struct ahd_softc*,int,int /*<<< orphan*/ ,int,struct ahd_tmode_tstate**) ; 
 int /*<<< orphan*/  ahd_force_renegotiation (struct ahd_softc*,struct ahd_devinfo*) ; 
 int ahd_get_scbptr (struct ahd_softc*) ; 
 int ahd_inb (struct ahd_softc*,int /*<<< orphan*/ ) ; 
 int ahd_inb_scbram (struct ahd_softc*,int /*<<< orphan*/ ) ; 
 struct scb* ahd_lookup_scb (struct ahd_softc*,int) ; 
 char* ahd_name (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_outb (struct ahd_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ahd_search_qinfifo (struct ahd_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ahd_sent_msg (struct ahd_softc*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_set_syncrate (struct ahd_softc*,struct ahd_devinfo*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_set_tags (struct ahd_softc*,struct ahd_devinfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_set_width (struct ahd_softc*,struct ahd_devinfo*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aic_set_transaction_tag (struct scb*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  printf (char*,char*,int,int,int,...) ; 

__attribute__((used)) static int
ahd_handle_msg_reject(struct ahd_softc *ahd, struct ahd_devinfo *devinfo)
{
	/*
	 * What we care about here is if we had an
	 * outstanding SDTR or WDTR message for this
	 * target.  If we did, this is a signal that
	 * the target is refusing negotiation.
	 */
	struct scb *scb;
	struct ahd_initiator_tinfo *tinfo;
	struct ahd_tmode_tstate *tstate;
	u_int scb_index;
	u_int last_msg;
	int   response = 0;

	scb_index = ahd_get_scbptr(ahd);
	scb = ahd_lookup_scb(ahd, scb_index);
	tinfo = ahd_fetch_transinfo(ahd, devinfo->channel,
				    devinfo->our_scsiid,
				    devinfo->target, &tstate);
	/* Might be necessary */
	last_msg = ahd_inb(ahd, LAST_MSG);

	if (ahd_sent_msg(ahd, AHDMSG_EXT, MSG_EXT_PPR, /*full*/FALSE)) {
		if (ahd_sent_msg(ahd, AHDMSG_EXT, MSG_EXT_PPR, /*full*/TRUE)
		 && tinfo->goal.period <= AHD_SYNCRATE_PACED) {
			/*
			 * Target may not like our SPI-4 PPR Options.
			 * Attempt to negotiate 80MHz which will turn
			 * off these options.
			 */
			if (bootverbose) {
				printf("(%s:%c:%d:%d): PPR Rejected. "
				       "Trying simple U160 PPR\n",
				       ahd_name(ahd), devinfo->channel,
				       devinfo->target, devinfo->lun);
			}
			tinfo->goal.period = AHD_SYNCRATE_DT;
			tinfo->goal.ppr_options &= MSG_EXT_PPR_IU_REQ
						|  MSG_EXT_PPR_QAS_REQ
						|  MSG_EXT_PPR_DT_REQ;
		} else {
			/*
			 * Target does not support the PPR message.
			 * Attempt to negotiate SPI-2 style.
			 */
			if (bootverbose) {
				printf("(%s:%c:%d:%d): PPR Rejected. "
				       "Trying WDTR/SDTR\n",
				       ahd_name(ahd), devinfo->channel,
				       devinfo->target, devinfo->lun);
			}
			tinfo->goal.ppr_options = 0;
			tinfo->curr.transport_version = 2;
			tinfo->goal.transport_version = 2;
		}
		ahd->msgout_index = 0;
		ahd->msgout_len = 0;
		ahd_build_transfer_msg(ahd, devinfo);
		ahd->msgout_index = 0;
		response = 1;
	} else if (ahd_sent_msg(ahd, AHDMSG_EXT, MSG_EXT_WDTR, /*full*/FALSE)) {

		/* note 8bit xfers */
		printf("(%s:%c:%d:%d): refuses WIDE negotiation.  Using "
		       "8bit transfers\n", ahd_name(ahd),
		       devinfo->channel, devinfo->target, devinfo->lun);
		ahd_set_width(ahd, devinfo, MSG_EXT_WDTR_BUS_8_BIT,
			      AHD_TRANS_ACTIVE|AHD_TRANS_GOAL,
			      /*paused*/TRUE);
		/*
		 * No need to clear the sync rate.  If the target
		 * did not accept the command, our syncrate is
		 * unaffected.  If the target started the negotiation,
		 * but rejected our response, we already cleared the
		 * sync rate before sending our WDTR.
		 */
		if (tinfo->goal.offset != tinfo->curr.offset) {

			/* Start the sync negotiation */
			ahd->msgout_index = 0;
			ahd->msgout_len = 0;
			ahd_build_transfer_msg(ahd, devinfo);
			ahd->msgout_index = 0;
			response = 1;
		}
	} else if (ahd_sent_msg(ahd, AHDMSG_EXT, MSG_EXT_SDTR, /*full*/FALSE)) {
		/* note asynch xfers and clear flag */
		ahd_set_syncrate(ahd, devinfo, /*period*/0,
				 /*offset*/0, /*ppr_options*/0,
				 AHD_TRANS_ACTIVE|AHD_TRANS_GOAL,
				 /*paused*/TRUE);
		printf("(%s:%c:%d:%d): refuses synchronous negotiation. "
		       "Using asynchronous transfers\n",
		       ahd_name(ahd), devinfo->channel,
		       devinfo->target, devinfo->lun);
	} else if ((scb->hscb->control & MSG_SIMPLE_TASK) != 0) {
		int tag_type;
		int mask;

		tag_type = (scb->hscb->control & MSG_SIMPLE_TASK);

		if (tag_type == MSG_SIMPLE_TASK) {
			printf("(%s:%c:%d:%d): refuses tagged commands.  "
			       "Performing non-tagged I/O\n", ahd_name(ahd),
			       devinfo->channel, devinfo->target, devinfo->lun);
			ahd_set_tags(ahd, devinfo, AHD_QUEUE_NONE);
			mask = ~0x23;
		} else {
			printf("(%s:%c:%d:%d): refuses %s tagged commands.  "
			       "Performing simple queue tagged I/O only\n",
			       ahd_name(ahd), devinfo->channel, devinfo->target,
			       devinfo->lun, tag_type == MSG_ORDERED_TASK
			       ? "ordered" : "head of queue");
			ahd_set_tags(ahd, devinfo, AHD_QUEUE_BASIC);
			mask = ~0x03;
		}

		/*
		 * Resend the identify for this CCB as the target
		 * may believe that the selection is invalid otherwise.
		 */
		ahd_outb(ahd, SCB_CONTROL,
			 ahd_inb_scbram(ahd, SCB_CONTROL) & mask);
	 	scb->hscb->control &= mask;
		aic_set_transaction_tag(scb, /*enabled*/FALSE,
					/*type*/MSG_SIMPLE_TASK);
		ahd_outb(ahd, MSG_OUT, MSG_IDENTIFYFLAG);
		ahd_assert_atn(ahd);
		ahd_busy_tcl(ahd, BUILD_TCL(scb->hscb->scsiid, devinfo->lun),
			     SCB_GET_TAG(scb));

		/*
		 * Requeue all tagged commands for this target
		 * currently in our possession so they can be
		 * converted to untagged commands.
		 */
		ahd_search_qinfifo(ahd, SCB_GET_TARGET(ahd, scb),
				   SCB_GET_CHANNEL(ahd, scb),
				   SCB_GET_LUN(scb), /*tag*/SCB_LIST_NULL,
				   ROLE_INITIATOR, CAM_REQUEUE_REQ,
				   SEARCH_COMPLETE);
	} else if (ahd_sent_msg(ahd, AHDMSG_1B, MSG_IDENTIFYFLAG, TRUE)) {
		/*
		 * Most likely the device believes that we had
		 * previously negotiated packetized.
		 */
		ahd->msg_flags |= MSG_FLAG_EXPECT_PPR_BUSFREE
			       |  MSG_FLAG_IU_REQ_CHANGED;

		ahd_force_renegotiation(ahd, devinfo);
		ahd->msgout_index = 0;
		ahd->msgout_len = 0;
		ahd_build_transfer_msg(ahd, devinfo);
		ahd->msgout_index = 0;
		response = 1;
	} else {
		/*
		 * Otherwise, we ignore it.
		 */
		printf("%s:%c:%d: Message reject for %x -- ignored\n",
		       ahd_name(ahd), devinfo->channel, devinfo->target,
		       last_msg);
	}
	return (response);
}