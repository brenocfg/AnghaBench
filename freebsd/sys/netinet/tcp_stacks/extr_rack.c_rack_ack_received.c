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
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ uint16_t ;
struct tcphdr {scalar_t__ th_ack; } ;
struct tcpcb {scalar_t__ snd_cwnd; scalar_t__ snd_wnd; int t_flags; int t_stats_gput_prev; scalar_t__ snd_ssthresh; scalar_t__ t_bytes_acked; scalar_t__ t_peakrate_thr; int /*<<< orphan*/  t_stats; TYPE_2__* ccv; scalar_t__ t_maxpeakrate; scalar_t__ gput_ts; scalar_t__ gput_seq; int /*<<< orphan*/  gput_ack; int /*<<< orphan*/  t_inpcb; } ;
struct TYPE_4__ {scalar_t__ rc_early_recovery_segs; int* rc_gp_history; size_t rc_gp_hist_idx; int rc_gp_hist_filled; scalar_t__ rc_rack_largest_cwnd; } ;
struct tcp_rack {TYPE_1__ r_ctl; } ;
typedef  int int64_t ;
typedef  int int32_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* ack_received ) (TYPE_2__*,scalar_t__) ;} ;
struct TYPE_5__ {scalar_t__ curack; int /*<<< orphan*/  flags; scalar_t__ bytes_this_ack; scalar_t__ nsegs; } ;

/* Variables and functions */
 scalar_t__ BYTES_THIS_ACK (struct tcpcb*,struct tcphdr*) ; 
 int /*<<< orphan*/  CCF_ABC_SENTAWND ; 
 int /*<<< orphan*/  CCF_CWND_LIMITED ; 
 scalar_t__ CC_ACK ; 
 TYPE_3__* CC_ALGO (struct tcpcb*) ; 
 int /*<<< orphan*/  INP_WLOCK_ASSERT (int /*<<< orphan*/ ) ; 
 size_t RACK_GP_HIST ; 
 scalar_t__ SEQ_GEQ (scalar_t__,int /*<<< orphan*/ ) ; 
 int TF_GPUTINPROG ; 
 int /*<<< orphan*/  VOI_TCP_CALCFRWINDIFF ; 
 int /*<<< orphan*/  VOI_TCP_GPUT ; 
 int /*<<< orphan*/  VOI_TCP_GPUT_ND ; 
 int /*<<< orphan*/  VOI_TCP_LCWIN ; 
 scalar_t__ V_tcp_abc_l_var ; 
 scalar_t__ ctf_fixed_maxseg (struct tcpcb*) ; 
 int max (int,scalar_t__) ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  stats_voi_update_abs_s32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stats_voi_update_abs_u32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stats_voi_update_abs_ulong (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,scalar_t__) ; 
 scalar_t__ tcp_ts_getticks () ; 
 int /*<<< orphan*/  tcp_update_peakrate_thr (struct tcpcb*) ; 

__attribute__((used)) static void
rack_ack_received(struct tcpcb *tp, struct tcp_rack *rack, struct tcphdr *th, uint16_t nsegs,
    uint16_t type, int32_t recovery)
{
#ifdef NETFLIX_STATS
	int32_t gput;
#endif

	INP_WLOCK_ASSERT(tp->t_inpcb);
	tp->ccv->nsegs = nsegs;
	tp->ccv->bytes_this_ack = BYTES_THIS_ACK(tp, th);
	if ((recovery) && (rack->r_ctl.rc_early_recovery_segs)) {
		uint32_t max;

		max = rack->r_ctl.rc_early_recovery_segs * ctf_fixed_maxseg(tp);
		if (tp->ccv->bytes_this_ack > max) {
			tp->ccv->bytes_this_ack = max;
		}
	}
	if (tp->snd_cwnd <= tp->snd_wnd)
		tp->ccv->flags |= CCF_CWND_LIMITED;
	else
		tp->ccv->flags &= ~CCF_CWND_LIMITED;

	if (type == CC_ACK) {
#ifdef NETFLIX_STATS
		stats_voi_update_abs_s32(tp->t_stats, VOI_TCP_CALCFRWINDIFF,
		    ((int32_t) tp->snd_cwnd) - tp->snd_wnd);
		if ((tp->t_flags & TF_GPUTINPROG) &&
		    SEQ_GEQ(th->th_ack, tp->gput_ack)) {
			gput = (((int64_t) (th->th_ack - tp->gput_seq)) << 3) /
			    max(1, tcp_ts_getticks() - tp->gput_ts);
			/* We store it in bytes per ms (or kbytes per sec) */
			rack->r_ctl.rc_gp_history[rack->r_ctl.rc_gp_hist_idx] = gput / 8;
			rack->r_ctl.rc_gp_hist_idx++;
			if (rack->r_ctl.rc_gp_hist_idx >= RACK_GP_HIST)
				rack->r_ctl.rc_gp_hist_filled = 1;
			rack->r_ctl.rc_gp_hist_idx %= RACK_GP_HIST;
			stats_voi_update_abs_u32(tp->t_stats, VOI_TCP_GPUT,
			    gput);
			/*
			 * XXXLAS: This is a temporary hack, and should be
			 * chained off VOI_TCP_GPUT when stats(9) grows an
			 * API to deal with chained VOIs.
			 */
			if (tp->t_stats_gput_prev > 0)
				stats_voi_update_abs_s32(tp->t_stats,
				    VOI_TCP_GPUT_ND,
				    ((gput - tp->t_stats_gput_prev) * 100) /
				    tp->t_stats_gput_prev);
			tp->t_flags &= ~TF_GPUTINPROG;
			tp->t_stats_gput_prev = gput;

			if (tp->t_maxpeakrate) {
				/*
				 * We update t_peakrate_thr. This gives us roughly
				 * one update per round trip time.
				 */
				tcp_update_peakrate_thr(tp);
			}
		}
#endif
		if (tp->snd_cwnd > tp->snd_ssthresh) {
			tp->t_bytes_acked += min(tp->ccv->bytes_this_ack,
			    nsegs * V_tcp_abc_l_var * ctf_fixed_maxseg(tp));
			if (tp->t_bytes_acked >= tp->snd_cwnd) {
				tp->t_bytes_acked -= tp->snd_cwnd;
				tp->ccv->flags |= CCF_ABC_SENTAWND;
			}
		} else {
			tp->ccv->flags &= ~CCF_ABC_SENTAWND;
			tp->t_bytes_acked = 0;
		}
	}
	if (CC_ALGO(tp)->ack_received != NULL) {
		/* XXXLAS: Find a way to live without this */
		tp->ccv->curack = th->th_ack;
		CC_ALGO(tp)->ack_received(tp->ccv, type);
	}
#ifdef NETFLIX_STATS
	stats_voi_update_abs_ulong(tp->t_stats, VOI_TCP_LCWIN, tp->snd_cwnd);
#endif
	if (rack->r_ctl.rc_rack_largest_cwnd < tp->snd_cwnd) {
		rack->r_ctl.rc_rack_largest_cwnd = tp->snd_cwnd;
	}
	/* we enforce max peak rate if it is set. */
	if (tp->t_peakrate_thr && tp->snd_cwnd > tp->t_peakrate_thr) {
		tp->snd_cwnd = tp->t_peakrate_thr;
	}
}