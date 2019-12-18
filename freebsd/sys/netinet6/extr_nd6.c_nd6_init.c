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

/* Variables and functions */
 int /*<<< orphan*/  EVENTHANDLER_PRI_ANY ; 
 void* EVENTHANDLER_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_DEFAULT_VNET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int ND6_SLOWTIMER_INTERVAL ; 
 int /*<<< orphan*/  V_nd6_lock ; 
 int /*<<< orphan*/  V_nd6_onlink_mtx ; 
 int /*<<< orphan*/  V_nd6_slowtimo_ch ; 
 int /*<<< orphan*/  V_nd6_timer_ch ; 
 int /*<<< orphan*/  V_nd_prefix ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curvnet ; 
 int hz ; 
 int /*<<< orphan*/  iflladdr_event ; 
 void* iflladdr_event_eh ; 
 int /*<<< orphan*/  ifnet_link_event ; 
 void* ifnet_link_event_eh ; 
 int /*<<< orphan*/  lle_event ; 
 void* lle_event_eh ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nd6_dad_init () ; 
 int /*<<< orphan*/  nd6_defrouter_init () ; 
 int /*<<< orphan*/  nd6_iflladdr ; 
 int /*<<< orphan*/  nd6_ifnet_link_event ; 
 int /*<<< orphan*/  nd6_lle_event ; 
 int /*<<< orphan*/  nd6_slowtimo ; 
 int /*<<< orphan*/  nd6_timer ; 
 int /*<<< orphan*/  rw_init (int /*<<< orphan*/ *,char*) ; 

void
nd6_init(void)
{

	mtx_init(&V_nd6_onlink_mtx, "nd6 onlink", NULL, MTX_DEF);
	rw_init(&V_nd6_lock, "nd6 list");

	LIST_INIT(&V_nd_prefix);
	nd6_defrouter_init();

	/* Start timers. */
	callout_init(&V_nd6_slowtimo_ch, 0);
	callout_reset(&V_nd6_slowtimo_ch, ND6_SLOWTIMER_INTERVAL * hz,
	    nd6_slowtimo, curvnet);

	callout_init(&V_nd6_timer_ch, 0);
	callout_reset(&V_nd6_timer_ch, hz, nd6_timer, curvnet);

	nd6_dad_init();
	if (IS_DEFAULT_VNET(curvnet)) {
		lle_event_eh = EVENTHANDLER_REGISTER(lle_event, nd6_lle_event,
		    NULL, EVENTHANDLER_PRI_ANY);
		iflladdr_event_eh = EVENTHANDLER_REGISTER(iflladdr_event,
		    nd6_iflladdr, NULL, EVENTHANDLER_PRI_ANY);
		ifnet_link_event_eh = EVENTHANDLER_REGISTER(ifnet_link_event,
		    nd6_ifnet_link_event, NULL, EVENTHANDLER_PRI_ANY);
	}
}