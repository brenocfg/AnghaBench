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
struct tcphdr {int dummy; } ;
struct TYPE_3__ {scalar_t__ sack_bytes_rexmit; } ;
struct tcpcb {int t_maxseg; scalar_t__ snd_cwnd; scalar_t__ snd_nxt; scalar_t__ sack_newdata; scalar_t__ snd_ssthresh; TYPE_2__* t_fb; int /*<<< orphan*/  t_flags; TYPE_1__ sackhint; scalar_t__ t_rtttime; int /*<<< orphan*/  t_inpcb; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* tfb_tcp_output ) (struct tcpcb*) ;} ;

/* Variables and functions */
 int BYTES_THIS_ACK (struct tcpcb*,struct tcphdr*) ; 
 int /*<<< orphan*/  INP_WLOCK_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TF_ACKNOW ; 
 int /*<<< orphan*/  TT_REXMT ; 
 int /*<<< orphan*/  stub1 (struct tcpcb*) ; 
 int /*<<< orphan*/  tcp_timer_activate (struct tcpcb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
tcp_sack_partialack(struct tcpcb *tp, struct tcphdr *th)
{
	int num_segs = 1;

	INP_WLOCK_ASSERT(tp->t_inpcb);
	tcp_timer_activate(tp, TT_REXMT, 0);
	tp->t_rtttime = 0;
	/* Send one or 2 segments based on how much new data was acked. */
	if ((BYTES_THIS_ACK(tp, th) / tp->t_maxseg) >= 2)
		num_segs = 2;
	tp->snd_cwnd = (tp->sackhint.sack_bytes_rexmit +
	    (tp->snd_nxt - tp->sack_newdata) + num_segs * tp->t_maxseg);
	if (tp->snd_cwnd > tp->snd_ssthresh)
		tp->snd_cwnd = tp->snd_ssthresh;
	tp->t_flags |= TF_ACKNOW;
	(void) tp->t_fb->tfb_tcp_output(tp);
}