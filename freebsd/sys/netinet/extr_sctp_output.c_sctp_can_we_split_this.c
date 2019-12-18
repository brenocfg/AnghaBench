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
typedef  scalar_t__ uint32_t ;
struct TYPE_2__ {scalar_t__ total_flight; } ;
struct sctp_tcb {int /*<<< orphan*/  sctp_socket; TYPE_1__ asoc; } ;

/* Variables and functions */
 scalar_t__ SCTP_BASE_SYSCTL (int /*<<< orphan*/ ) ; 
 scalar_t__ SCTP_SB_LIMIT_SND (int /*<<< orphan*/ ) ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  sctp_min_residual ; 
 int /*<<< orphan*/  sctp_min_split_point ; 

__attribute__((used)) static uint32_t
sctp_can_we_split_this(struct sctp_tcb *stcb, uint32_t length,
    uint32_t space_left, uint32_t frag_point, int eeor_on)
{
	/*
	 * Make a decision on if I should split a msg into multiple parts.
	 * This is only asked of incomplete messages.
	 */
	if (eeor_on) {
		/*
		 * If we are doing EEOR we need to always send it if its the
		 * entire thing, since it might be all the guy is putting in
		 * the hopper.
		 */
		if (space_left >= length) {
			/*-
			 * If we have data outstanding,
			 * we get another chance when the sack
			 * arrives to transmit - wait for more data
			 */
			if (stcb->asoc.total_flight == 0) {
				/*
				 * If nothing is in flight, we zero the
				 * packet counter.
				 */
				return (length);
			}
			return (0);

		} else {
			/* You can fill the rest */
			return (space_left);
		}
	}
	/*-
	 * For those strange folk that make the send buffer
	 * smaller than our fragmentation point, we can't
	 * get a full msg in so we have to allow splitting.
	 */
	if (SCTP_SB_LIMIT_SND(stcb->sctp_socket) < frag_point) {
		return (length);
	}
	if ((length <= space_left) ||
	    ((length - space_left) < SCTP_BASE_SYSCTL(sctp_min_residual))) {
		/* Sub-optimial residual don't split in non-eeor mode. */
		return (0);
	}
	/*
	 * If we reach here length is larger than the space_left. Do we wish
	 * to split it for the sake of packet putting together?
	 */
	if (space_left >= min(SCTP_BASE_SYSCTL(sctp_min_split_point), frag_point)) {
		/* Its ok to split it */
		return (min(space_left, frag_point));
	}
	/* Nope, can't split */
	return (0);
}