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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct tcpcb {scalar_t__ t_state; scalar_t__ snd_una; scalar_t__ snd_max; int t_rxtshift; int snd_cwnd; int snd_cwnd_prev; scalar_t__ snd_recover_prev; scalar_t__ snd_recover; int t_srtt; int t_flags2; scalar_t__ t_pmtud_saved_maxseg; scalar_t__ t_maxseg; int t_rttvar; scalar_t__ t_rtttime; int /*<<< orphan*/  t_flags; struct inpcb* t_inpcb; int /*<<< orphan*/  t_rxtcur; scalar_t__ t_badrxtwin; int /*<<< orphan*/  snd_ssthresh; int /*<<< orphan*/  snd_ssthresh_prev; scalar_t__ t_softerror; TYPE_1__* t_timers; } ;
struct TYPE_6__ {int /*<<< orphan*/  rack_sf; TYPE_2__* rc_resend; int /*<<< orphan*/  rc_hpts_flags; } ;
struct tcp_rack {TYPE_3__ r_ctl; struct inpcb* rc_inp; } ;
struct inpcb {int inp_vflag; } ;
typedef  int int32_t ;
struct TYPE_5__ {int r_flags; } ;
struct TYPE_4__ {int tt_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CC_RTO ; 
 int /*<<< orphan*/  ETIMEDOUT ; 
 int INP_IPV6 ; 
 scalar_t__ IN_CONGRECOVERY (int /*<<< orphan*/ ) ; 
 scalar_t__ IN_FASTRECOVERY (int /*<<< orphan*/ ) ; 
 int MSEC_2_TICKS (int) ; 
 int /*<<< orphan*/  PACE_TMR_RXT ; 
 int RACK_INITIAL_RTO ; 
 int RACK_RWND_COLLAPSED ; 
 int /*<<< orphan*/  TCPSTAT_INC (int /*<<< orphan*/ ) ; 
 scalar_t__ TCPS_ESTABLISHED ; 
 scalar_t__ TCPS_FIN_WAIT_1 ; 
 scalar_t__ TCPS_HAVEESTABLISHED (scalar_t__) ; 
 scalar_t__ TCPS_SYN_RECEIVED ; 
 scalar_t__ TCPS_SYN_SENT ; 
 int /*<<< orphan*/  TCPT_RANGESET (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int TCP_MAXRXTSHIFT ; 
 int TCP_REXMTVAL (struct tcpcb*) ; 
 int TCP_RTT_SHIFT ; 
 int TF2_PLPMTU_BLACKHOLE ; 
 int TF2_PLPMTU_MAXSEGSNT ; 
 int TF2_PLPMTU_PMTUD ; 
 int /*<<< orphan*/  TF_ACKNOW ; 
 int /*<<< orphan*/  TF_PREVVALID ; 
 int /*<<< orphan*/  TF_WASCRECOVERY ; 
 int /*<<< orphan*/  TF_WASFRECOVERY ; 
 int TT_STOPPED ; 
 scalar_t__ V_tcp_mssdflt ; 
 scalar_t__ V_tcp_pmtud_blackhole_detect ; 
 scalar_t__ V_tcp_pmtud_blackhole_mss ; 
 scalar_t__ V_tcp_v6mssdflt ; 
 scalar_t__ V_tcp_v6pmtud_blackhole_mss ; 
 int /*<<< orphan*/  in6_losing (struct inpcb*) ; 
 int /*<<< orphan*/  in_losing (struct inpcb*) ; 
 int /*<<< orphan*/  max (int,int) ; 
 int /*<<< orphan*/  rack_cong_signal (struct tcpcb*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ rack_progress_timeout_check (struct tcpcb*) ; 
 int /*<<< orphan*/  rack_remxt_tmr (struct tcpcb*) ; 
 int rack_rto_max ; 
 int rack_rto_min ; 
 scalar_t__ rack_use_sack_filter ; 
 int /*<<< orphan*/  sack_filter_clear (int /*<<< orphan*/ *,scalar_t__) ; 
 int* tcp_backoff ; 
 int /*<<< orphan*/  tcp_set_inp_to_drop (struct inpcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcps_pmtud_blackhole_activated ; 
 int /*<<< orphan*/  tcps_pmtud_blackhole_activated_min_mss ; 
 int /*<<< orphan*/  tcps_pmtud_blackhole_failed ; 
 int /*<<< orphan*/  tcps_rexmttimeo ; 
 int /*<<< orphan*/  tcps_timeoutdrop ; 
 scalar_t__ ticks ; 

__attribute__((used)) static int
rack_timeout_rxt(struct tcpcb *tp, struct tcp_rack *rack, uint32_t cts)
{
	int32_t rexmt;
	struct inpcb *inp;
	int32_t retval = 0;

	inp = tp->t_inpcb;
	if (tp->t_timers->tt_flags & TT_STOPPED) {
		return (1);
	}
	if (rack_progress_timeout_check(tp)) {
		tcp_set_inp_to_drop(inp, ETIMEDOUT);
		return (1);
	}
	rack->r_ctl.rc_hpts_flags &= ~PACE_TMR_RXT;
	if (TCPS_HAVEESTABLISHED(tp->t_state) &&
	    (tp->snd_una == tp->snd_max)) {
		/* Nothing outstanding .. nothing to do */
		return (0);
	}
	/*
	 * Retransmission timer went off.  Message has not been acked within
	 * retransmit interval.  Back off to a longer retransmit interval
	 * and retransmit one segment.
	 */
	rack_remxt_tmr(tp);
	if ((rack->r_ctl.rc_resend == NULL) ||
	    ((rack->r_ctl.rc_resend->r_flags & RACK_RWND_COLLAPSED) == 0)) {
		/*
		 * If the rwnd collapsed on
		 * the one we are retransmitting
		 * it does not count against the
		 * rxt count.
		 */
		tp->t_rxtshift++;
	}
	if (tp->t_rxtshift > TCP_MAXRXTSHIFT) {
		tp->t_rxtshift = TCP_MAXRXTSHIFT;
		TCPSTAT_INC(tcps_timeoutdrop);
		retval = 1;
		tcp_set_inp_to_drop(rack->rc_inp,
		    (tp->t_softerror ? (uint16_t) tp->t_softerror : ETIMEDOUT));
		goto out;
	}
	if (tp->t_state == TCPS_SYN_SENT) {
		/*
		 * If the SYN was retransmitted, indicate CWND to be limited
		 * to 1 segment in cc_conn_init().
		 */
		tp->snd_cwnd = 1;
	} else if (tp->t_rxtshift == 1) {
		/*
		 * first retransmit; record ssthresh and cwnd so they can be
		 * recovered if this turns out to be a "bad" retransmit. A
		 * retransmit is considered "bad" if an ACK for this segment
		 * is received within RTT/2 interval; the assumption here is
		 * that the ACK was already in flight.  See "On Estimating
		 * End-to-End Network Path Properties" by Allman and Paxson
		 * for more details.
		 */
		tp->snd_cwnd_prev = tp->snd_cwnd;
		tp->snd_ssthresh_prev = tp->snd_ssthresh;
		tp->snd_recover_prev = tp->snd_recover;
		if (IN_FASTRECOVERY(tp->t_flags))
			tp->t_flags |= TF_WASFRECOVERY;
		else
			tp->t_flags &= ~TF_WASFRECOVERY;
		if (IN_CONGRECOVERY(tp->t_flags))
			tp->t_flags |= TF_WASCRECOVERY;
		else
			tp->t_flags &= ~TF_WASCRECOVERY;
		tp->t_badrxtwin = ticks + (tp->t_srtt >> (TCP_RTT_SHIFT + 1));
		tp->t_flags |= TF_PREVVALID;
	} else
		tp->t_flags &= ~TF_PREVVALID;
	TCPSTAT_INC(tcps_rexmttimeo);
	if ((tp->t_state == TCPS_SYN_SENT) ||
	    (tp->t_state == TCPS_SYN_RECEIVED))
		rexmt = MSEC_2_TICKS(RACK_INITIAL_RTO * tcp_backoff[tp->t_rxtshift]);
	else
		rexmt = TCP_REXMTVAL(tp) * tcp_backoff[tp->t_rxtshift];
	TCPT_RANGESET(tp->t_rxtcur, rexmt,
	   max(MSEC_2_TICKS(rack_rto_min), rexmt),
	   MSEC_2_TICKS(rack_rto_max));
	/*
	 * We enter the path for PLMTUD if connection is established or, if
	 * connection is FIN_WAIT_1 status, reason for the last is that if
	 * amount of data we send is very small, we could send it in couple
	 * of packets and process straight to FIN. In that case we won't
	 * catch ESTABLISHED state.
	 */
	if (V_tcp_pmtud_blackhole_detect && (((tp->t_state == TCPS_ESTABLISHED))
	    || (tp->t_state == TCPS_FIN_WAIT_1))) {
#ifdef INET6
		int32_t isipv6;
#endif

		/*
		 * Idea here is that at each stage of mtu probe (usually,
		 * 1448 -> 1188 -> 524) should be given 2 chances to recover
		 * before further clamping down. 'tp->t_rxtshift % 2 == 0'
		 * should take care of that.
		 */
		if (((tp->t_flags2 & (TF2_PLPMTU_PMTUD | TF2_PLPMTU_MAXSEGSNT)) ==
		    (TF2_PLPMTU_PMTUD | TF2_PLPMTU_MAXSEGSNT)) &&
		    (tp->t_rxtshift >= 2 && tp->t_rxtshift < 6 &&
		    tp->t_rxtshift % 2 == 0)) {
			/*
			 * Enter Path MTU Black-hole Detection mechanism: -
			 * Disable Path MTU Discovery (IP "DF" bit). -
			 * Reduce MTU to lower value than what we negotiated
			 * with peer.
			 */
			if ((tp->t_flags2 & TF2_PLPMTU_BLACKHOLE) == 0) {
				/* Record that we may have found a black hole. */
				tp->t_flags2 |= TF2_PLPMTU_BLACKHOLE;
				/* Keep track of previous MSS. */
				tp->t_pmtud_saved_maxseg = tp->t_maxseg;
			}

			/*
			 * Reduce the MSS to blackhole value or to the
			 * default in an attempt to retransmit.
			 */
#ifdef INET6
			isipv6 = (tp->t_inpcb->inp_vflag & INP_IPV6) ? 1 : 0;
			if (isipv6 &&
			    tp->t_maxseg > V_tcp_v6pmtud_blackhole_mss) {
				/* Use the sysctl tuneable blackhole MSS. */
				tp->t_maxseg = V_tcp_v6pmtud_blackhole_mss;
				TCPSTAT_INC(tcps_pmtud_blackhole_activated);
			} else if (isipv6) {
				/* Use the default MSS. */
				tp->t_maxseg = V_tcp_v6mssdflt;
				/*
				 * Disable Path MTU Discovery when we switch
				 * to minmss.
				 */
				tp->t_flags2 &= ~TF2_PLPMTU_PMTUD;
				TCPSTAT_INC(tcps_pmtud_blackhole_activated_min_mss);
			}
#endif
#if defined(INET6) && defined(INET)
			else
#endif
#ifdef INET
			if (tp->t_maxseg > V_tcp_pmtud_blackhole_mss) {
				/* Use the sysctl tuneable blackhole MSS. */
				tp->t_maxseg = V_tcp_pmtud_blackhole_mss;
				TCPSTAT_INC(tcps_pmtud_blackhole_activated);
			} else {
				/* Use the default MSS. */
				tp->t_maxseg = V_tcp_mssdflt;
				/*
				 * Disable Path MTU Discovery when we switch
				 * to minmss.
				 */
				tp->t_flags2 &= ~TF2_PLPMTU_PMTUD;
				TCPSTAT_INC(tcps_pmtud_blackhole_activated_min_mss);
			}
#endif
		} else {
			/*
			 * If further retransmissions are still unsuccessful
			 * with a lowered MTU, maybe this isn't a blackhole
			 * and we restore the previous MSS and blackhole
			 * detection flags. The limit '6' is determined by
			 * giving each probe stage (1448, 1188, 524) 2
			 * chances to recover.
			 */
			if ((tp->t_flags2 & TF2_PLPMTU_BLACKHOLE) &&
			    (tp->t_rxtshift >= 6)) {
				tp->t_flags2 |= TF2_PLPMTU_PMTUD;
				tp->t_flags2 &= ~TF2_PLPMTU_BLACKHOLE;
				tp->t_maxseg = tp->t_pmtud_saved_maxseg;
				TCPSTAT_INC(tcps_pmtud_blackhole_failed);
			}
		}
	}
	/*
	 * If we backed off this far, our srtt estimate is probably bogus.
	 * Clobber it so we'll take the next rtt measurement as our srtt;
	 * move the current srtt into rttvar to keep the current retransmit
	 * times until then.
	 */
	if (tp->t_rxtshift > TCP_MAXRXTSHIFT / 4) {
#ifdef INET6
		if ((tp->t_inpcb->inp_vflag & INP_IPV6) != 0)
			in6_losing(tp->t_inpcb);
		else
#endif
			in_losing(tp->t_inpcb);
		tp->t_rttvar += (tp->t_srtt >> TCP_RTT_SHIFT);
		tp->t_srtt = 0;
	}
	if (rack_use_sack_filter)
		sack_filter_clear(&rack->r_ctl.rack_sf, tp->snd_una);
	tp->snd_recover = tp->snd_max;
	tp->t_flags |= TF_ACKNOW;
	tp->t_rtttime = 0;
	rack_cong_signal(tp, NULL, CC_RTO);
out:
	return (retval);
}