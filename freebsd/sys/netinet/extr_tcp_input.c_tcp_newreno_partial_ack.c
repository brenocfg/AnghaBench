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
typedef  scalar_t__ u_int ;
typedef  int /*<<< orphan*/  tcp_seq ;
struct tcphdr {int /*<<< orphan*/  th_ack; } ;
struct tcpcb {scalar_t__ snd_cwnd; int /*<<< orphan*/  snd_nxt; TYPE_1__* t_fb; int /*<<< orphan*/  t_flags; scalar_t__ t_rtttime; int /*<<< orphan*/  t_inpcb; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* tfb_tcp_output ) (struct tcpcb*) ;} ;

/* Variables and functions */
 scalar_t__ BYTES_THIS_ACK (struct tcpcb*,struct tcphdr*) ; 
 int /*<<< orphan*/  INP_WLOCK_ASSERT (int /*<<< orphan*/ ) ; 
 scalar_t__ SEQ_GT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TF_ACKNOW ; 
 int /*<<< orphan*/  TT_REXMT ; 
 int /*<<< orphan*/  stub1 (struct tcpcb*) ; 
 scalar_t__ tcp_maxseg (struct tcpcb*) ; 
 int /*<<< orphan*/  tcp_timer_activate (struct tcpcb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
tcp_newreno_partial_ack(struct tcpcb *tp, struct tcphdr *th)
{
	tcp_seq onxt = tp->snd_nxt;
	uint32_t ocwnd = tp->snd_cwnd;
	u_int maxseg = tcp_maxseg(tp);

	INP_WLOCK_ASSERT(tp->t_inpcb);

	tcp_timer_activate(tp, TT_REXMT, 0);
	tp->t_rtttime = 0;
	tp->snd_nxt = th->th_ack;
	/*
	 * Set snd_cwnd to one segment beyond acknowledged offset.
	 * (tp->snd_una has not yet been updated when this function is called.)
	 */
	tp->snd_cwnd = maxseg + BYTES_THIS_ACK(tp, th);
	tp->t_flags |= TF_ACKNOW;
	(void) tp->t_fb->tfb_tcp_output(tp);
	tp->snd_cwnd = ocwnd;
	if (SEQ_GT(onxt, tp->snd_nxt))
		tp->snd_nxt = onxt;
	/*
	 * Partial window deflation.  Relies on fact that tp->snd_una
	 * not updated yet.
	 */
	if (tp->snd_cwnd > BYTES_THIS_ACK(tp, th))
		tp->snd_cwnd -= BYTES_THIS_ACK(tp, th);
	else
		tp->snd_cwnd = 0;
	tp->snd_cwnd += maxseg;
}