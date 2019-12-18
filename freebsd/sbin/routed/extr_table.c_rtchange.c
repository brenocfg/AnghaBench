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
typedef  int u_int ;
struct rt_spare {scalar_t__ rts_metric; scalar_t__ rts_time; scalar_t__ rts_gate; int /*<<< orphan*/  rts_ifp; } ;
struct rt_entry {scalar_t__ rt_metric; scalar_t__ rt_gate; int rt_state; struct rt_spare* rt_spares; void* rt_seqno; } ;
struct TYPE_4__ {scalar_t__ tv_sec; } ;
struct TYPE_3__ {scalar_t__ tv_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  AGE_RT (int,int /*<<< orphan*/ ) ; 
 scalar_t__ EXPIRE_TIME ; 
 scalar_t__ HOPCNT_INFINITY ; 
 int RS_SUBNET ; 
 scalar_t__ TRACEACTIONS ; 
 TYPE_2__ need_kern ; 
 TYPE_1__ now ; 
 int /*<<< orphan*/  set_need_flash () ; 
 int /*<<< orphan*/  trace_change (struct rt_entry*,int,struct rt_spare*,char*) ; 
 void* update_seqno ; 

void
rtchange(struct rt_entry *rt,
	 u_int	state,			/* new state bits */
	 struct rt_spare *new,
	 char	*label)
{
	if (rt->rt_metric != new->rts_metric) {
		/* Fix the kernel immediately if it seems the route
		 * has gone bad, since there may be a working route that
		 * aggregates this route.
		 */
		if (new->rts_metric == HOPCNT_INFINITY) {
			need_kern.tv_sec = now.tv_sec;
			if (new->rts_time >= now.tv_sec - EXPIRE_TIME)
				new->rts_time = now.tv_sec - EXPIRE_TIME;
		}
		rt->rt_seqno = update_seqno;
		set_need_flash();
	}

	if (rt->rt_gate != new->rts_gate) {
		need_kern.tv_sec = now.tv_sec;
		rt->rt_seqno = update_seqno;
		set_need_flash();
	}

	state |= (rt->rt_state & RS_SUBNET);

	/* Keep various things from deciding ageless routes are stale.
	 */
	if (!AGE_RT(state, new->rts_ifp))
		new->rts_time = now.tv_sec;

	if (TRACEACTIONS)
		trace_change(rt, state, new,
			     label ? label : "Chg   ");

	rt->rt_state = state;
	rt->rt_spares[0] = *new;
}