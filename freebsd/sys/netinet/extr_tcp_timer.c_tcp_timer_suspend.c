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
typedef  int uint32_t ;
struct tcpcb {TYPE_1__* t_timers; } ;
struct callout {int dummy; } ;
struct TYPE_2__ {int tt_flags; struct callout tt_2msl; struct callout tt_keep; struct callout tt_persist; struct callout tt_rexmt; struct callout tt_delack; } ;

/* Variables and functions */
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
 int callout_stop (struct callout*) ; 
 int /*<<< orphan*/  panic (char*,struct tcpcb*,int) ; 

int
tcp_timer_suspend(struct tcpcb *tp, uint32_t timer_type)
{
	struct callout *t_callout;
	uint32_t t_flags;

	switch (timer_type) {
		case TT_DELACK:
			t_flags = TT_DELACK_SUS;
			t_callout = &tp->t_timers->tt_delack;
			break;
		case TT_REXMT:
			t_flags = TT_REXMT_SUS;
			t_callout = &tp->t_timers->tt_rexmt;
			break;
		case TT_PERSIST:
			t_flags = TT_PERSIST_SUS;
			t_callout = &tp->t_timers->tt_persist;
			break;
		case TT_KEEP:
			t_flags = TT_KEEP_SUS;
			t_callout = &tp->t_timers->tt_keep;
			break;
		case TT_2MSL:
			t_flags = TT_2MSL_SUS;
			t_callout = &tp->t_timers->tt_2msl;
			break;
		default:
			panic("tp:%p bad timer_type 0x%x", tp, timer_type);
	}
	tp->t_timers->tt_flags |= t_flags;
	return (callout_stop(t_callout));
}