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
struct tcpcb {TYPE_2__* t_timers; TYPE_1__* t_fb; } ;
struct callout {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  tt_draincnt; struct callout tt_2msl; struct callout tt_keep; struct callout tt_persist; struct callout tt_rexmt; struct callout tt_delack; int /*<<< orphan*/  tt_flags; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* tfb_tcp_timer_stop ) (struct tcpcb*,int) ;} ;

/* Variables and functions */
#define  TT_2MSL 132 
#define  TT_DELACK 131 
#define  TT_KEEP 130 
#define  TT_PERSIST 129 
#define  TT_REXMT 128 
 int /*<<< orphan*/  TT_STOPPED ; 
 scalar_t__ callout_async_drain (struct callout*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,struct tcpcb*,int) ; 
 int /*<<< orphan*/  stub1 (struct tcpcb*,int) ; 
 int /*<<< orphan*/  tcp_timer_discard ; 

void
tcp_timer_stop(struct tcpcb *tp, uint32_t timer_type)
{
	struct callout *t_callout;

	tp->t_timers->tt_flags |= TT_STOPPED;
	switch (timer_type) {
		case TT_DELACK:
			t_callout = &tp->t_timers->tt_delack;
			break;
		case TT_REXMT:
			t_callout = &tp->t_timers->tt_rexmt;
			break;
		case TT_PERSIST:
			t_callout = &tp->t_timers->tt_persist;
			break;
		case TT_KEEP:
			t_callout = &tp->t_timers->tt_keep;
			break;
		case TT_2MSL:
			t_callout = &tp->t_timers->tt_2msl;
			break;
		default:
			if (tp->t_fb->tfb_tcp_timer_stop) {
				/* 
				 * XXXrrs we need to look at this with the
				 * stop case below (flags).
				 */
				tp->t_fb->tfb_tcp_timer_stop(tp, timer_type);
				return;
			}
			panic("tp %p bad timer_type %#x", tp, timer_type);
		}

	if (callout_async_drain(t_callout, tcp_timer_discard) == 0) {
		/*
		 * Can't stop the callout, defer tcpcb actual deletion
		 * to the last one. We do this using the async drain
		 * function and incrementing the count in 
		 */
		tp->t_timers->tt_draincnt++;
	}
}