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
struct rt_spare {scalar_t__ rts_metric; int /*<<< orphan*/  rts_time; int /*<<< orphan*/  rts_router; int /*<<< orphan*/  rts_gate; struct interface* rts_ifp; } ;
struct rt_entry {int rt_state; } ;
struct khash {scalar_t__ k_metric; int /*<<< orphan*/  k_mask; int /*<<< orphan*/  k_dst; int /*<<< orphan*/  k_gate; } ;
struct interface {int /*<<< orphan*/  int_addr; } ;
typedef  int /*<<< orphan*/  new ;
struct TYPE_2__ {int /*<<< orphan*/  tv_sec; } ;

/* Variables and functions */
 int RS_STATIC ; 
 int /*<<< orphan*/  loopaddr ; 
 int /*<<< orphan*/  memset (struct rt_spare*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__ now ; 
 int /*<<< orphan*/  rtadd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct rt_spare*) ; 
 int /*<<< orphan*/  rtchange (struct rt_entry*,int,struct rt_spare*,int /*<<< orphan*/ ) ; 
 struct rt_entry* rtget (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
kern_check_static(struct khash *k,
		  struct interface *ifp)
{
	struct rt_entry *rt;
	struct rt_spare new;

	if (k->k_metric == 0)
		return;

	memset(&new, 0, sizeof(new));
	new.rts_ifp = ifp;
	new.rts_gate = k->k_gate;
	new.rts_router = (ifp != NULL) ? ifp->int_addr : loopaddr;
	new.rts_metric = k->k_metric;
	new.rts_time = now.tv_sec;

	rt = rtget(k->k_dst, k->k_mask);
	if (rt != NULL) {
		if (!(rt->rt_state & RS_STATIC))
			rtchange(rt, rt->rt_state | RS_STATIC, &new, 0);
	} else {
		rtadd(k->k_dst, k->k_mask, RS_STATIC, &new);
	}
}