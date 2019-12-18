#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct tcpcb {int t_srtt; int t_rttvar; size_t t_rxtshift; int /*<<< orphan*/  t_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCPT_RANGESET (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t TCP_MAXRXTSHIFT ; 
 int /*<<< orphan*/  TF_PREVVALID ; 
 int /*<<< orphan*/  TT_PERSIST ; 
 int /*<<< orphan*/  TT_REXMT ; 
 int /*<<< orphan*/  panic (char*) ; 
 int* tcp_backoff ; 
 int /*<<< orphan*/  tcp_persmax ; 
 int /*<<< orphan*/  tcp_persmin ; 
 int /*<<< orphan*/  tcp_timer_activate (struct tcpcb*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ tcp_timer_active (struct tcpcb*,int /*<<< orphan*/ ) ; 

void
tcp_setpersist(struct tcpcb *tp)
{
	int t = ((tp->t_srtt >> 2) + tp->t_rttvar) >> 1;
	int tt;

	tp->t_flags &= ~TF_PREVVALID;
	if (tcp_timer_active(tp, TT_REXMT))
		panic("tcp_setpersist: retransmit pending");
	/*
	 * Start/restart persistence timer.
	 */
	TCPT_RANGESET(tt, t * tcp_backoff[tp->t_rxtshift],
		      tcp_persmin, tcp_persmax);
	tcp_timer_activate(tp, TT_PERSIST, tt);
	if (tp->t_rxtshift < TCP_MAXRXTSHIFT)
		tp->t_rxtshift++;
}