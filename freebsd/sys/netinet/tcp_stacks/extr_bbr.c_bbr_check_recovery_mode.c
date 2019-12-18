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
struct tcpcb {int t_flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  rc_lost_bytes; int /*<<< orphan*/  rc_lost; int /*<<< orphan*/  rc_tmap; int /*<<< orphan*/  rc_map; } ;
struct tcp_bbr {TYPE_1__ r_ctl; } ;
struct bbr_sendmap {int r_flags; size_t r_rtr_cnt; scalar_t__ r_dupack; scalar_t__ r_end; scalar_t__ r_start; int /*<<< orphan*/ * r_tim_lastsent; } ;
typedef  size_t int32_t ;

/* Variables and functions */
 int BBR_ACKED ; 
 int BBR_MARKED_LOST ; 
 int BBR_SACK_PASSED ; 
 int /*<<< orphan*/  CC_NDUPACK ; 
 scalar_t__ DUP_ACK_THRESHOLD ; 
 scalar_t__ SEQ_LEQ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 struct bbr_sendmap* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int TF_SENTFIN ; 
 int /*<<< orphan*/  bbr_cong_signal (struct tcpcb*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct bbr_sendmap*) ; 
 struct bbr_sendmap* bbr_find_lowest_rsm (struct tcp_bbr*) ; 
 scalar_t__ bbr_is_lost (struct tcp_bbr*,struct bbr_sendmap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,struct tcpcb*,struct tcp_bbr*,struct bbr_sendmap*) ; 

__attribute__((used)) static struct bbr_sendmap *
bbr_check_recovery_mode(struct tcpcb *tp, struct tcp_bbr *bbr, uint32_t cts)
{
	/*
	 * Check to see that we don't need to fall into recovery. We will
	 * need to do so if our oldest transmit is past the time we should
	 * have had an ack.
	 */

	struct bbr_sendmap *rsm;
	int32_t idx;

	if (TAILQ_EMPTY(&bbr->r_ctl.rc_map)) {
		/* Nothing outstanding that we know of */
		return (NULL);
	}
	rsm = TAILQ_FIRST(&bbr->r_ctl.rc_tmap);
	if (rsm == NULL) {
		/* Nothing in the transmit map */
		return (NULL);
	}
	if (tp->t_flags & TF_SENTFIN) {
		/* Fin restricted, don't find anything once a fin is sent */
		return (NULL);
	}
	if (rsm->r_flags & BBR_ACKED) {
		/*
		 * Ok the first one is acked (this really should not happen
		 * since we remove the from the tmap once they are acked)
		 */
		rsm = bbr_find_lowest_rsm(bbr);
		if (rsm == NULL)
			return (NULL);
	}
	idx = rsm->r_rtr_cnt - 1;
	if (SEQ_LEQ(cts, rsm->r_tim_lastsent[idx])) {
		/* Send timestamp is the same or less? can't be ready */
		return (NULL);
	}
	/* Get our RTT time */
	if (bbr_is_lost(bbr, rsm, cts) &&
	    ((rsm->r_dupack >= DUP_ACK_THRESHOLD) ||
	     (rsm->r_flags & BBR_SACK_PASSED))) {
		if ((rsm->r_flags & BBR_MARKED_LOST) == 0) {
			rsm->r_flags |= BBR_MARKED_LOST;
			bbr->r_ctl.rc_lost += rsm->r_end - rsm->r_start;
			bbr->r_ctl.rc_lost_bytes += rsm->r_end - rsm->r_start;
		}
		bbr_cong_signal(tp, NULL, CC_NDUPACK, rsm);
#ifdef BBR_INVARIANTS
		if ((rsm->r_end - rsm->r_start) == 0)
			panic("tp:%p bbr:%p rsm:%p length is 0?", tp, bbr, rsm);
#endif
		return (rsm);
	}
	return (NULL);
}