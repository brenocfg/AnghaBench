#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct tcpcb {int t_flags; TYPE_4__* t_inpcb; int /*<<< orphan*/  t_state; TYPE_1__* t_timers; int /*<<< orphan*/  t_rxtshift; int /*<<< orphan*/  snd_wnd; int /*<<< orphan*/  t_rxtcur; int /*<<< orphan*/  snd_una; int /*<<< orphan*/  snd_max; } ;
struct TYPE_8__ {TYPE_3__* inp_socket; } ;
struct TYPE_6__ {int sb_state; } ;
struct TYPE_7__ {TYPE_2__ so_rcv; } ;
struct TYPE_5__ {int tt_flags; } ;

/* Variables and functions */
 int SBS_CANTRCVMORE ; 
 int /*<<< orphan*/  SEQ_GT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCPS_FIN_WAIT_2 ; 
 int /*<<< orphan*/  TCPS_HAVEESTABLISHED (int /*<<< orphan*/ ) ; 
 int TF_DELACK ; 
 int /*<<< orphan*/  TP_KEEPIDLE (struct tcpcb*) ; 
 int /*<<< orphan*/  TP_KEEPINIT (struct tcpcb*) ; 
 int /*<<< orphan*/  TP_MAXIDLE (struct tcpcb*) ; 
#define  TT_2MSL 132 
 int TT_2MSL_SUS ; 
#define  TT_DELACK 131 
 int TT_DELACK_SUS ; 
#define  TT_KEEP 130 
 int TT_KEEP_SUS ; 
#define  TT_PERSIST 129 
 int TT_PERSIST_SUS ; 
#define  TT_REXMT 128 
 int TT_REXMT_SUS ; 
 int /*<<< orphan*/  panic (char*,struct tcpcb*,int) ; 
 int /*<<< orphan*/  tcp_delacktime ; 
 int /*<<< orphan*/  tcp_fast_finwait2_recycle ; 
 int /*<<< orphan*/  tcp_finwait2_timeout ; 
 int /*<<< orphan*/  tcp_setpersist (struct tcpcb*) ; 
 int /*<<< orphan*/  tcp_timer_activate (struct tcpcb*,int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_timer_active (struct tcpcb*,int) ; 

void
tcp_timers_unsuspend(struct tcpcb *tp, uint32_t timer_type)
{
	switch (timer_type) {
		case TT_DELACK:
			if (tp->t_timers->tt_flags & TT_DELACK_SUS) {
				tp->t_timers->tt_flags &= ~TT_DELACK_SUS;
				if (tp->t_flags & TF_DELACK) {
					/* Delayed ack timer should be up activate a timer */
					tp->t_flags &= ~TF_DELACK;
					tcp_timer_activate(tp, TT_DELACK,
					    tcp_delacktime);
				}
			}
			break;
		case TT_REXMT:
			if (tp->t_timers->tt_flags & TT_REXMT_SUS) {
				tp->t_timers->tt_flags &= ~TT_REXMT_SUS;
				if (SEQ_GT(tp->snd_max, tp->snd_una) &&
				    (tcp_timer_active((tp), TT_PERSIST) == 0) &&
				    tp->snd_wnd) {
					/* We have outstanding data activate a timer */
					tcp_timer_activate(tp, TT_REXMT, 
                                            tp->t_rxtcur);
				}
			}
			break;
		case TT_PERSIST:
			if (tp->t_timers->tt_flags & TT_PERSIST_SUS) {
				tp->t_timers->tt_flags &= ~TT_PERSIST_SUS;
				if (tp->snd_wnd == 0) {
					/* Activate the persists timer */
					tp->t_rxtshift = 0;
					tcp_setpersist(tp);
				}
			}
			break;
		case TT_KEEP:
			if (tp->t_timers->tt_flags & TT_KEEP_SUS) {
				tp->t_timers->tt_flags &= ~TT_KEEP_SUS;
				tcp_timer_activate(tp, TT_KEEP,
					    TCPS_HAVEESTABLISHED(tp->t_state) ?
					    TP_KEEPIDLE(tp) : TP_KEEPINIT(tp));
			}
			break;
		case TT_2MSL:
			if (tp->t_timers->tt_flags &= TT_2MSL_SUS) {
				tp->t_timers->tt_flags &= ~TT_2MSL_SUS;
				if ((tp->t_state == TCPS_FIN_WAIT_2) &&
				    ((tp->t_inpcb->inp_socket == NULL) ||
				     (tp->t_inpcb->inp_socket->so_rcv.sb_state & SBS_CANTRCVMORE))) {
					/* Star the 2MSL timer */
					tcp_timer_activate(tp, TT_2MSL,
					    (tcp_fast_finwait2_recycle) ?
					    tcp_finwait2_timeout : TP_MAXIDLE(tp));
				}
			}
			break;
		default:
			panic("tp:%p bad timer_type 0x%x", tp, timer_type);
	}
}