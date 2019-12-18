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
struct tcpopt {int to_flags; scalar_t__ to_tsval; } ;
struct tcphdr {scalar_t__ th_seq; } ;
struct tcpcb {scalar_t__ rcv_nxt; scalar_t__ last_ack_sent; int t_flags; int /*<<< orphan*/  t_inpcb; scalar_t__ t_fb_ptr; scalar_t__ ts_recent; int /*<<< orphan*/  ts_recent_age; scalar_t__ t_fin_is_rst; } ;
struct TYPE_2__ {int /*<<< orphan*/  rc_rcvtime; } ;
struct tcp_rack {int /*<<< orphan*/  r_wanted_output; TYPE_1__ r_ctl; } ;
struct socket {int /*<<< orphan*/  so_snd; } ;
struct mbuf {int dummy; } ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  BANDLIM_RST_OPENPORT ; 
 int /*<<< orphan*/  ETIMEDOUT ; 
 int SEGQ_EMPTY (struct tcpcb*) ; 
 scalar_t__ SEQ_LEQ (scalar_t__,scalar_t__) ; 
 int TF_ACKNOW ; 
 int TF_NEEDSYN ; 
 scalar_t__ TH_ACK ; 
 scalar_t__ TH_FIN ; 
 scalar_t__ TH_RST ; 
 scalar_t__ TH_SYN ; 
 scalar_t__ TH_URG ; 
 int TOF_SACK ; 
 int TOF_TS ; 
 scalar_t__ TSTMP_LT (scalar_t__,scalar_t__) ; 
 scalar_t__ __predict_true (int) ; 
 int /*<<< orphan*/  ctf_calc_rwin (struct socket*,struct tcpcb*) ; 
 int /*<<< orphan*/  ctf_challenge_ack (struct mbuf*,struct tcphdr*,struct tcpcb*,scalar_t__*) ; 
 int /*<<< orphan*/  ctf_do_drop (struct mbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ctf_do_dropafterack (struct mbuf*,struct tcpcb*,struct tcphdr*,scalar_t__,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  ctf_do_dropwithreset (struct mbuf*,struct tcpcb*,struct tcphdr*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ ctf_drop_checks (struct tcpopt*,struct mbuf*,struct tcphdr*,struct tcpcb*,scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*) ; 
 int ctf_process_rst (struct mbuf*,struct tcphdr*,struct socket*,struct tcpcb*) ; 
 scalar_t__ ctf_ts_check (struct mbuf*,struct tcphdr*,struct tcpcb*,scalar_t__,scalar_t__,scalar_t__*) ; 
 scalar_t__ rack_do_fastnewdata (struct mbuf*,struct tcphdr*,struct socket*,struct tcpcb*,struct tcpopt*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ rack_fastack (struct mbuf*,struct tcphdr*,struct socket*,struct tcpcb*,struct tcpopt*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ rack_process_ack (struct mbuf*,struct tcphdr*,struct socket*,struct tcpcb*,struct tcpopt*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,scalar_t__,scalar_t__*) ; 
 int rack_process_data (struct mbuf*,struct tcphdr*,struct socket*,struct tcpcb*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ rack_progress_timeout_check (struct tcpcb*) ; 
 scalar_t__ sbavail (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcp_set_inp_to_drop (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_ts_getticks () ; 

__attribute__((used)) static int
rack_do_established(struct mbuf *m, struct tcphdr *th, struct socket *so,
    struct tcpcb *tp, struct tcpopt *to, int32_t drop_hdrlen, int32_t tlen,
    uint32_t tiwin, int32_t thflags, int32_t nxt_pkt)
{
	int32_t ret_val = 0;

	/*
	 * Header prediction: check for the two common cases of a
	 * uni-directional data xfer.  If the packet has no control flags,
	 * is in-sequence, the window didn't change and we're not
	 * retransmitting, it's a candidate.  If the length is zero and the
	 * ack moved forward, we're the sender side of the xfer.  Just free
	 * the data acked & wake any higher level process that was blocked
	 * waiting for space.  If the length is non-zero and the ack didn't
	 * move, we're the receiver side.  If we're getting packets in-order
	 * (the reassembly queue is empty), add the data toc The socket
	 * buffer and note that we need a delayed ack. Make sure that the
	 * hidden state-flags are also off. Since we check for
	 * TCPS_ESTABLISHED first, it can only be TH_NEEDSYN.
	 */
	if (__predict_true(((to->to_flags & TOF_SACK) == 0)) &&
	    __predict_true((thflags & (TH_SYN | TH_FIN | TH_RST | TH_URG | TH_ACK)) == TH_ACK) &&
	    __predict_true(SEGQ_EMPTY(tp)) &&
	    __predict_true(th->th_seq == tp->rcv_nxt)) {
		struct tcp_rack *rack;

		rack = (struct tcp_rack *)tp->t_fb_ptr;
		if (tlen == 0) {
			if (rack_fastack(m, th, so, tp, to, drop_hdrlen, tlen,
			    tiwin, nxt_pkt, rack->r_ctl.rc_rcvtime)) {
				return (0);
			}
		} else {
			if (rack_do_fastnewdata(m, th, so, tp, to, drop_hdrlen, tlen,
			    tiwin, nxt_pkt)) {
				return (0);
			}
		}
	}
	ctf_calc_rwin(so, tp);

	if ((thflags & TH_RST) ||
	    (tp->t_fin_is_rst && (thflags & TH_FIN)))
		return (ctf_process_rst(m, th, so, tp));

	/*
	 * RFC5961 Section 4.2 Send challenge ACK for any SYN in
	 * synchronized state.
	 */
	if (thflags & TH_SYN) {
		ctf_challenge_ack(m, th, tp, &ret_val);
		return (ret_val);
	}
	/*
	 * RFC 1323 PAWS: If we have a timestamp reply on this segment and
	 * it's less than ts_recent, drop it.
	 */
	if ((to->to_flags & TOF_TS) != 0 && tp->ts_recent &&
	    TSTMP_LT(to->to_tsval, tp->ts_recent)) {
		if (ctf_ts_check(m, th, tp, tlen, thflags, &ret_val))
			return (ret_val);
	}
	if (ctf_drop_checks(to, m, th, tp, &tlen, &thflags, &drop_hdrlen, &ret_val)) {
		return (ret_val);
	}
	/*
	 * If last ACK falls within this segment's sequence numbers, record
	 * its timestamp. NOTE: 1) That the test incorporates suggestions
	 * from the latest proposal of the tcplw@cray.com list (Braden
	 * 1993/04/26). 2) That updating only on newer timestamps interferes
	 * with our earlier PAWS tests, so this check should be solely
	 * predicated on the sequence space of this segment. 3) That we
	 * modify the segment boundary check to be Last.ACK.Sent <= SEG.SEQ
	 * + SEG.Len  instead of RFC1323's Last.ACK.Sent < SEG.SEQ +
	 * SEG.Len, This modified check allows us to overcome RFC1323's
	 * limitations as described in Stevens TCP/IP Illustrated Vol. 2
	 * p.869. In such cases, we can still calculate the RTT correctly
	 * when RCV.NXT == Last.ACK.Sent.
	 */
	if ((to->to_flags & TOF_TS) != 0 &&
	    SEQ_LEQ(th->th_seq, tp->last_ack_sent) &&
	    SEQ_LEQ(tp->last_ack_sent, th->th_seq + tlen +
	    ((thflags & (TH_SYN | TH_FIN)) != 0))) {
		tp->ts_recent_age = tcp_ts_getticks();
		tp->ts_recent = to->to_tsval;
	}
	/*
	 * If the ACK bit is off:  if in SYN-RECEIVED state or SENDSYN flag
	 * is on (half-synchronized state), then queue data for later
	 * processing; else drop segment and return.
	 */
	if ((thflags & TH_ACK) == 0) {
		if (tp->t_flags & TF_NEEDSYN) {

			return (rack_process_data(m, th, so, tp, drop_hdrlen, tlen,
			    tiwin, thflags, nxt_pkt));

		} else if (tp->t_flags & TF_ACKNOW) {
			ctf_do_dropafterack(m, tp, th, thflags, tlen, &ret_val);
			((struct tcp_rack *)tp->t_fb_ptr)->r_wanted_output++;
			return (ret_val);
		} else {
			ctf_do_drop(m, NULL);
			return (0);
		}
	}
	/*
	 * Ack processing.
	 */
	if (rack_process_ack(m, th, so, tp, to, tiwin, tlen, NULL, thflags, &ret_val)) {
		return (ret_val);
	}
	if (sbavail(&so->so_snd)) {
		if (rack_progress_timeout_check(tp)) {
			tcp_set_inp_to_drop(tp->t_inpcb, ETIMEDOUT);
			ctf_do_dropwithreset(m, tp, th, BANDLIM_RST_OPENPORT, tlen);
			return (1);
		}
	}
	/* State changes only happen in rack_process_data() */
	return (rack_process_data(m, th, so, tp, drop_hdrlen, tlen,
	    tiwin, thflags, nxt_pkt));
}