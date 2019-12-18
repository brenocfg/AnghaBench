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
typedef  int /*<<< orphan*/  u_int ;
typedef  int /*<<< orphan*/  timeout_t ;
struct tcpcb {int t_flags; TYPE_2__* t_fb; TYPE_1__* t_timers; struct inpcb* t_inpcb; } ;
struct inpcb {int dummy; } ;
struct callout {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* tfb_tcp_timer_activate ) (struct tcpcb*,int,int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {int tt_flags; struct callout tt_2msl; struct callout tt_keep; struct callout tt_persist; struct callout tt_rexmt; struct callout tt_delack; } ;

/* Variables and functions */
 int TF_TOE ; 
#define  TT_2MSL 132 
#define  TT_DELACK 131 
#define  TT_KEEP 130 
#define  TT_PERSIST 129 
#define  TT_REXMT 128 
 int TT_STOPPED ; 
 int /*<<< orphan*/  callout_reset_on (struct callout*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct tcpcb*,int) ; 
 int /*<<< orphan*/  callout_stop (struct callout*) ; 
 int inp_to_cpuid (struct inpcb*) ; 
 int /*<<< orphan*/  panic (char*,struct tcpcb*,int) ; 
 int /*<<< orphan*/  stub1 (struct tcpcb*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * tcp_timer_2msl ; 
 int /*<<< orphan*/ * tcp_timer_delack ; 
 int /*<<< orphan*/ * tcp_timer_keep ; 
 int /*<<< orphan*/ * tcp_timer_persist ; 
 int /*<<< orphan*/ * tcp_timer_rexmt ; 

void
tcp_timer_activate(struct tcpcb *tp, uint32_t timer_type, u_int delta)
{
	struct callout *t_callout;
	timeout_t *f_callout;
	struct inpcb *inp = tp->t_inpcb;
	int cpu = inp_to_cpuid(inp);

#ifdef TCP_OFFLOAD
	if (tp->t_flags & TF_TOE)
		return;
#endif

	if (tp->t_timers->tt_flags & TT_STOPPED)
		return;

	switch (timer_type) {
		case TT_DELACK:
			t_callout = &tp->t_timers->tt_delack;
			f_callout = tcp_timer_delack;
			break;
		case TT_REXMT:
			t_callout = &tp->t_timers->tt_rexmt;
			f_callout = tcp_timer_rexmt;
			break;
		case TT_PERSIST:
			t_callout = &tp->t_timers->tt_persist;
			f_callout = tcp_timer_persist;
			break;
		case TT_KEEP:
			t_callout = &tp->t_timers->tt_keep;
			f_callout = tcp_timer_keep;
			break;
		case TT_2MSL:
			t_callout = &tp->t_timers->tt_2msl;
			f_callout = tcp_timer_2msl;
			break;
		default:
			if (tp->t_fb->tfb_tcp_timer_activate) {
				tp->t_fb->tfb_tcp_timer_activate(tp, timer_type, delta);
				return;
			}
			panic("tp %p bad timer_type %#x", tp, timer_type);
		}
	if (delta == 0) {
		callout_stop(t_callout);
	} else {
		callout_reset_on(t_callout, delta, f_callout, tp, cpu);
	}
}