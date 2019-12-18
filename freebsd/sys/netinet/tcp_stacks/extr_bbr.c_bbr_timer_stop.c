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
typedef  int /*<<< orphan*/  uint32_t ;
struct tcpcb {scalar_t__ t_fb_ptr; } ;
struct tcp_bbr {int rc_all_timers_stopped; } ;

/* Variables and functions */

__attribute__((used)) static void
bbr_timer_stop(struct tcpcb *tp, uint32_t timer_type)
{
	struct tcp_bbr *bbr;

	bbr = (struct tcp_bbr *)tp->t_fb_ptr;
	bbr->rc_all_timers_stopped = 1;
	return;
}