#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  scalar_t__ u_short ;
struct tcptw {int rcv_nxt; int /*<<< orphan*/  tw_cred; int /*<<< orphan*/  tw_so_options; scalar_t__ tw_time; int /*<<< orphan*/  t_starttime; int /*<<< orphan*/  irs; int /*<<< orphan*/  iss; int /*<<< orphan*/  snd_nxt; scalar_t__ ts_offset; scalar_t__ t_recent; scalar_t__ last_win; struct inpcb* tw_inpcb; } ;
struct tcpcb {long rcv_scale; int t_maxseg; int rcv_adv; int rcv_nxt; int t_flags; int /*<<< orphan*/  t_starttime; int /*<<< orphan*/  irs; int /*<<< orphan*/  iss; int /*<<< orphan*/  snd_nxt; scalar_t__ ts_offset; scalar_t__ ts_recent; struct inpcb* t_inpcb; } ;
struct TYPE_4__ {int sb_hiwat; } ;
struct socket {int so_state; int /*<<< orphan*/  so_cred; int /*<<< orphan*/  so_options; TYPE_2__ so_rcv; } ;
struct TYPE_3__ {int inc_flags; } ;
struct inpcb {int inp_flags; struct tcptw* inp_ppcb; struct socket* inp_socket; int /*<<< orphan*/  inp_faddr; int /*<<< orphan*/  in6p_faddr; TYPE_1__ inp_inc; } ;

/* Variables and functions */
 int INC_ISIPV6 ; 
 int INP_DROPPED ; 
 int INP_SOCKREF ; 
 int INP_TIMEWAIT ; 
 int /*<<< orphan*/  INP_WLOCK_ASSERT (struct inpcb*) ; 
 int /*<<< orphan*/  INP_WUNLOCK (struct inpcb*) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  NET_EPOCH_ASSERT () ; 
 scalar_t__ SEQ_GT (int,int) ; 
 int /*<<< orphan*/  SOCK_LOCK (struct socket*) ; 
 int SS_PROTOREF ; 
 int /*<<< orphan*/  TCPSTATES_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCPS_TIME_WAIT ; 
 scalar_t__ TCP_MAXWIN ; 
 int TF_ACKNOW ; 
 int TF_NOOPT ; 
 int TF_RCVD_TSTMP ; 
 int TF_REQ_TSTMP ; 
 int /*<<< orphan*/  TH_ACK ; 
 scalar_t__ V_nolocaltimewait ; 
 int /*<<< orphan*/  V_tcptw_zone ; 
 int /*<<< orphan*/  crhold (int /*<<< orphan*/ ) ; 
 int in6_localaddr (int /*<<< orphan*/ *) ; 
 int in_localip (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_pcbdrop (struct inpcb*) ; 
 int /*<<< orphan*/  in_pcbref (struct inpcb*) ; 
 int /*<<< orphan*/  lmax (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int lmin (int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  sbspace (TYPE_2__*) ; 
 int /*<<< orphan*/  sofree (struct socket*) ; 
 int /*<<< orphan*/  soisdisconnected (struct socket*) ; 
 struct tcpcb* tcp_close (struct tcpcb*) ; 
 int /*<<< orphan*/  tcp_discardcb (struct tcpcb*) ; 
 int /*<<< orphan*/  tcp_state_change (struct tcpcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_tw_2msl_reset (struct tcptw*,int /*<<< orphan*/ ) ; 
 struct tcptw* tcp_tw_2msl_scan (int) ; 
 int /*<<< orphan*/  tcp_twrespond (struct tcptw*,int /*<<< orphan*/ ) ; 
 struct tcptw* uma_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
tcp_twstart(struct tcpcb *tp)
{
	struct tcptw twlocal, *tw;
	struct inpcb *inp = tp->t_inpcb;
	struct socket *so;
	uint32_t recwin;
	bool acknow, local;
#ifdef INET6
	bool isipv6 = inp->inp_inc.inc_flags & INC_ISIPV6;
#endif

	NET_EPOCH_ASSERT();
	INP_WLOCK_ASSERT(inp);

	/* A dropped inp should never transition to TIME_WAIT state. */
	KASSERT((inp->inp_flags & INP_DROPPED) == 0, ("tcp_twstart: "
	    "(inp->inp_flags & INP_DROPPED) != 0"));

	if (V_nolocaltimewait) {
#ifdef INET6
		if (isipv6)
			local = in6_localaddr(&inp->in6p_faddr);
		else
#endif
#ifdef INET
			local = in_localip(inp->inp_faddr);
#else
			local = false;
#endif
	} else
		local = false;

	/*
	 * For use only by DTrace.  We do not reference the state
	 * after this point so modifying it in place is not a problem.
	 */
	tcp_state_change(tp, TCPS_TIME_WAIT);

	if (local)
		tw = &twlocal;
	else
		tw = uma_zalloc(V_tcptw_zone, M_NOWAIT);
	if (tw == NULL) {
		/*
		 * Reached limit on total number of TIMEWAIT connections
		 * allowed. Remove a connection from TIMEWAIT queue in LRU
		 * fashion to make room for this connection.
		 *
		 * XXX:  Check if it possible to always have enough room
		 * in advance based on guarantees provided by uma_zalloc().
		 */
		tw = tcp_tw_2msl_scan(1);
		if (tw == NULL) {
			tp = tcp_close(tp);
			if (tp != NULL)
				INP_WUNLOCK(inp);
			return;
		}
	}
	/*
	 * For !local case the tcptw will hold a reference on its inpcb
	 * until tcp_twclose is called.
	 */
	tw->tw_inpcb = inp;

	/*
	 * Recover last window size sent.
	 */
	so = inp->inp_socket;
	recwin = lmin(lmax(sbspace(&so->so_rcv), 0),
	    (long)TCP_MAXWIN << tp->rcv_scale);
	if (recwin < (so->so_rcv.sb_hiwat / 4) &&
	    recwin < tp->t_maxseg)
		recwin = 0;
	if (SEQ_GT(tp->rcv_adv, tp->rcv_nxt) &&
	    recwin < (tp->rcv_adv - tp->rcv_nxt))
		recwin = (tp->rcv_adv - tp->rcv_nxt);
	tw->last_win = (u_short)(recwin >> tp->rcv_scale);

	/*
	 * Set t_recent if timestamps are used on the connection.
	 */
	if ((tp->t_flags & (TF_REQ_TSTMP|TF_RCVD_TSTMP|TF_NOOPT)) ==
	    (TF_REQ_TSTMP|TF_RCVD_TSTMP)) {
		tw->t_recent = tp->ts_recent;
		tw->ts_offset = tp->ts_offset;
	} else {
		tw->t_recent = 0;
		tw->ts_offset = 0;
	}

	tw->snd_nxt = tp->snd_nxt;
	tw->rcv_nxt = tp->rcv_nxt;
	tw->iss     = tp->iss;
	tw->irs     = tp->irs;
	tw->t_starttime = tp->t_starttime;
	tw->tw_time = 0;

/* XXX
 * If this code will
 * be used for fin-wait-2 state also, then we may need
 * a ts_recent from the last segment.
 */
	acknow = tp->t_flags & TF_ACKNOW;

	/*
	 * First, discard tcpcb state, which includes stopping its timers and
	 * freeing it.  tcp_discardcb() used to also release the inpcb, but
	 * that work is now done in the caller.
	 *
	 * Note: soisdisconnected() call used to be made in tcp_discardcb(),
	 * and might not be needed here any longer.
	 */
	tcp_discardcb(tp);
	soisdisconnected(so);
	tw->tw_so_options = so->so_options;
	inp->inp_flags |= INP_TIMEWAIT;
	if (acknow)
		tcp_twrespond(tw, TH_ACK);
	if (local)
		in_pcbdrop(inp);
	else {
		in_pcbref(inp);	/* Reference from tw */
		tw->tw_cred = crhold(so->so_cred);
		inp->inp_ppcb = tw;
		TCPSTATES_INC(TCPS_TIME_WAIT);
		tcp_tw_2msl_reset(tw, 0);
	}

	/*
	 * If the inpcb owns the sole reference to the socket, then we can
	 * detach and free the socket as it is not needed in time wait.
	 */
	if (inp->inp_flags & INP_SOCKREF) {
		KASSERT(so->so_state & SS_PROTOREF,
		    ("tcp_twstart: !SS_PROTOREF"));
		inp->inp_flags &= ~INP_SOCKREF;
		INP_WUNLOCK(inp);
		SOCK_LOCK(so);
		so->so_state &= ~SS_PROTOREF;
		sofree(so);
	} else
		INP_WUNLOCK(inp);
}