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
struct tcpcb {scalar_t__ snd_cwnd; scalar_t__ snd_ssthresh; int /*<<< orphan*/  snd_una; int /*<<< orphan*/  snd_recover; int /*<<< orphan*/  t_flags; scalar_t__ t_fb_ptr; } ;
struct TYPE_2__ {scalar_t__ rc_rsm_start; scalar_t__ rc_cwnd_at; scalar_t__ rc_ssthresh_at; int /*<<< orphan*/  rc_reorder_ts; } ;
struct tcp_rack {TYPE_1__ r_ctl; } ;
struct rack_sendmap {int r_flags; scalar_t__ r_start; int r_end; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_RECOVERY (int /*<<< orphan*/ ) ; 
 scalar_t__ IN_RECOVERY (int /*<<< orphan*/ ) ; 
 int RACK_HAS_FIN ; 
 int RACK_TLP ; 
 int RACK_WAS_SACKPASS ; 
 int /*<<< orphan*/  counter_u64_add (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rack_badfr ; 
 int /*<<< orphan*/  rack_badfr_bytes ; 
 int /*<<< orphan*/  rack_reorder_seen ; 

__attribute__((used)) static void
rack_earlier_retran(struct tcpcb *tp, struct rack_sendmap *rsm,
    uint32_t t, uint32_t cts)
{
	/*
	 * For this RSM, we acknowledged the data from a previous
	 * transmission, not the last one we made. This means we did a false
	 * retransmit.
	 */
	struct tcp_rack *rack;

	if (rsm->r_flags & RACK_HAS_FIN) {
		/*
		 * The sending of the FIN often is multiple sent when we
		 * have everything outstanding ack'd. We ignore this case
		 * since its over now.
		 */
		return;
	}
	if (rsm->r_flags & RACK_TLP) {
		/*
		 * We expect TLP's to have this occur.
		 */
		return;
	}
	rack = (struct tcp_rack *)tp->t_fb_ptr;
	/* should we undo cc changes and exit recovery? */
	if (IN_RECOVERY(tp->t_flags)) {
		if (rack->r_ctl.rc_rsm_start == rsm->r_start) {
			/*
			 * Undo what we ratched down and exit recovery if
			 * possible
			 */
			EXIT_RECOVERY(tp->t_flags);
			tp->snd_recover = tp->snd_una;
			if (rack->r_ctl.rc_cwnd_at > tp->snd_cwnd)
				tp->snd_cwnd = rack->r_ctl.rc_cwnd_at;
			if (rack->r_ctl.rc_ssthresh_at > tp->snd_ssthresh)
				tp->snd_ssthresh = rack->r_ctl.rc_ssthresh_at;
		}
	}
	if (rsm->r_flags & RACK_WAS_SACKPASS) {
		/*
		 * We retransmitted based on a sack and the earlier
		 * retransmission ack'd it - re-ordering is occuring.
		 */
		counter_u64_add(rack_reorder_seen, 1);
		rack->r_ctl.rc_reorder_ts = cts;
	}
	counter_u64_add(rack_badfr, 1);
	counter_u64_add(rack_badfr_bytes, (rsm->r_end - rsm->r_start));
}