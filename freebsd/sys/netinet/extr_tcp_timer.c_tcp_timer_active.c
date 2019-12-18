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
struct tcpcb {TYPE_1__* t_fb; TYPE_2__* t_timers; } ;
struct callout {int dummy; } ;
struct TYPE_4__ {struct callout tt_2msl; struct callout tt_keep; struct callout tt_persist; struct callout tt_rexmt; struct callout tt_delack; } ;
struct TYPE_3__ {int (* tfb_tcp_timer_active ) (struct tcpcb*,int) ;} ;

/* Variables and functions */
#define  TT_2MSL 132 
#define  TT_DELACK 131 
#define  TT_KEEP 130 
#define  TT_PERSIST 129 
#define  TT_REXMT 128 
 int callout_active (struct callout*) ; 
 int /*<<< orphan*/  panic (char*,struct tcpcb*,int) ; 
 int stub1 (struct tcpcb*,int) ; 

int
tcp_timer_active(struct tcpcb *tp, uint32_t timer_type)
{
	struct callout *t_callout;

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
			if (tp->t_fb->tfb_tcp_timer_active) {
				return(tp->t_fb->tfb_tcp_timer_active(tp, timer_type));
			}
			panic("tp %p bad timer_type %#x", tp, timer_type);
		}
	return callout_active(t_callout);
}