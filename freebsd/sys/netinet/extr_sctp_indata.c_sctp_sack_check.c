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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  timer; } ;
struct sctp_association {int send_sack; scalar_t__ numduptsns; scalar_t__ delayed_ack; scalar_t__ data_pkts_seen; scalar_t__ sack_freq; scalar_t__ sctp_cmt_on_off; TYPE_1__ dack_timer; int /*<<< orphan*/  cmt_dac_pkts_rcvd; scalar_t__ primary_destination; scalar_t__ alternate; int /*<<< orphan*/  cumulative_tsn; int /*<<< orphan*/  highest_tsn_inside_map; int /*<<< orphan*/  highest_tsn_inside_nr_map; } ;
struct sctp_tcb {int /*<<< orphan*/  sctp_ep; struct sctp_association asoc; } ;

/* Variables and functions */
 scalar_t__ SCTP_BASE_SYSCTL (int /*<<< orphan*/ ) ; 
 scalar_t__ SCTP_FROM_SCTP_INDATA ; 
 scalar_t__ SCTP_GET_STATE (struct sctp_tcb*) ; 
 scalar_t__ SCTP_LOC_17 ; 
 scalar_t__ SCTP_OS_TIMER_PENDING (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SCTP_OS_TIMER_STOP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SCTP_SO_NOT_LOCKED ; 
 scalar_t__ SCTP_STATE_SHUTDOWN_SENT ; 
 int /*<<< orphan*/  SCTP_TIMER_TYPE_RECV ; 
 int SCTP_TSN_GT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_cmt_use_dac ; 
 int /*<<< orphan*/  sctp_send_sack (struct sctp_tcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_send_shutdown (struct sctp_tcb*,scalar_t__) ; 
 int /*<<< orphan*/  sctp_slide_mapping_arrays (struct sctp_tcb*) ; 
 int /*<<< orphan*/  sctp_timer_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sctp_tcb*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sctp_timer_stop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sctp_tcb*,int /*<<< orphan*/ *,scalar_t__) ; 

void
sctp_sack_check(struct sctp_tcb *stcb, int was_a_gap)
{
	struct sctp_association *asoc;
	uint32_t highest_tsn;
	int is_a_gap;

	sctp_slide_mapping_arrays(stcb);
	asoc = &stcb->asoc;
	if (SCTP_TSN_GT(asoc->highest_tsn_inside_nr_map, asoc->highest_tsn_inside_map)) {
		highest_tsn = asoc->highest_tsn_inside_nr_map;
	} else {
		highest_tsn = asoc->highest_tsn_inside_map;
	}
	/* Is there a gap now? */
	is_a_gap = SCTP_TSN_GT(highest_tsn, stcb->asoc.cumulative_tsn);

	/*
	 * Now we need to see if we need to queue a sack or just start the
	 * timer (if allowed).
	 */
	if (SCTP_GET_STATE(stcb) == SCTP_STATE_SHUTDOWN_SENT) {
		/*
		 * Ok special case, in SHUTDOWN-SENT case. here we maker
		 * sure SACK timer is off and instead send a SHUTDOWN and a
		 * SACK
		 */
		if (SCTP_OS_TIMER_PENDING(&stcb->asoc.dack_timer.timer)) {
			sctp_timer_stop(SCTP_TIMER_TYPE_RECV,
			    stcb->sctp_ep, stcb, NULL,
			    SCTP_FROM_SCTP_INDATA + SCTP_LOC_17);
		}
		sctp_send_shutdown(stcb,
		    ((stcb->asoc.alternate) ? stcb->asoc.alternate : stcb->asoc.primary_destination));
		if (is_a_gap) {
			sctp_send_sack(stcb, SCTP_SO_NOT_LOCKED);
		}
	} else {
		/*
		 * CMT DAC algorithm: increase number of packets received
		 * since last ack
		 */
		stcb->asoc.cmt_dac_pkts_rcvd++;

		if ((stcb->asoc.send_sack == 1) ||	/* We need to send a
							 * SACK */
		    ((was_a_gap) && (is_a_gap == 0)) ||	/* was a gap, but no
							 * longer is one */
		    (stcb->asoc.numduptsns) ||	/* we have dup's */
		    (is_a_gap) ||	/* is still a gap */
		    (stcb->asoc.delayed_ack == 0) ||	/* Delayed sack disabled */
		    (stcb->asoc.data_pkts_seen >= stcb->asoc.sack_freq)	/* hit limit of pkts */
		    ) {

			if ((stcb->asoc.sctp_cmt_on_off > 0) &&
			    (SCTP_BASE_SYSCTL(sctp_cmt_use_dac)) &&
			    (stcb->asoc.send_sack == 0) &&
			    (stcb->asoc.numduptsns == 0) &&
			    (stcb->asoc.delayed_ack) &&
			    (!SCTP_OS_TIMER_PENDING(&stcb->asoc.dack_timer.timer))) {

				/*
				 * CMT DAC algorithm: With CMT, delay acks
				 * even in the face of
				 *
				 * reordering. Therefore, if acks that do
				 * not have to be sent because of the above
				 * reasons, will be delayed. That is, acks
				 * that would have been sent due to gap
				 * reports will be delayed with DAC. Start
				 * the delayed ack timer.
				 */
				sctp_timer_start(SCTP_TIMER_TYPE_RECV,
				    stcb->sctp_ep, stcb, NULL);
			} else {
				/*
				 * Ok we must build a SACK since the timer
				 * is pending, we got our first packet OR
				 * there are gaps or duplicates.
				 */
				(void)SCTP_OS_TIMER_STOP(&stcb->asoc.dack_timer.timer);
				sctp_send_sack(stcb, SCTP_SO_NOT_LOCKED);
			}
		} else {
			if (!SCTP_OS_TIMER_PENDING(&stcb->asoc.dack_timer.timer)) {
				sctp_timer_start(SCTP_TIMER_TYPE_RECV,
				    stcb->sctp_ep, stcb, NULL);
			}
		}
	}
}