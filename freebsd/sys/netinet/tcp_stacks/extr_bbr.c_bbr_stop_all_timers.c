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
struct tcpcb {scalar_t__ t_fb_ptr; } ;
struct tcp_bbr {int rc_in_persist; } ;

/* Variables and functions */
 int /*<<< orphan*/  TT_DELACK ; 
 int /*<<< orphan*/  TT_KEEP ; 
 int /*<<< orphan*/  TT_PERSIST ; 
 int /*<<< orphan*/  TT_REXMT ; 
 scalar_t__ tcp_timer_active (struct tcpcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_timer_suspend (struct tcpcb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bbr_stop_all_timers(struct tcpcb *tp)
{
	struct tcp_bbr *bbr;

	/*
	 * Assure no timers are running.
	 */
	if (tcp_timer_active(tp, TT_PERSIST)) {
		/* We enter in persists, set the flag appropriately */
		bbr = (struct tcp_bbr *)tp->t_fb_ptr;
		bbr->rc_in_persist = 1;
	}
	tcp_timer_suspend(tp, TT_PERSIST);
	tcp_timer_suspend(tp, TT_REXMT);
	tcp_timer_suspend(tp, TT_KEEP);
	tcp_timer_suspend(tp, TT_DELACK);
}