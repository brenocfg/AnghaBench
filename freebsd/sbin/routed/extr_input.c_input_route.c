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
struct rt_spare {scalar_t__ rts_metric; scalar_t__ rts_router; scalar_t__ rts_de_ag; scalar_t__ rts_time; scalar_t__ rts_gate; scalar_t__ rts_tag; } ;
struct rt_entry {int /*<<< orphan*/  rt_state; struct rt_spare* rt_spares; } ;
struct netinfo {scalar_t__ n_nhop; } ;
struct interface {int int_state; } ;
typedef  scalar_t__ naddr ;

/* Variables and functions */
 scalar_t__ BETTER_LINK (struct rt_entry*,struct rt_spare*,struct rt_spare*) ; 
 scalar_t__ HOPCNT_INFINITY ; 
 int IS_BROKE ; 
 int IS_PASSIVE ; 
 scalar_t__ MAX_ROUTES ; 
 int NUM_SPARES ; 
 struct interface* ifwithaddr (scalar_t__,int,int) ; 
 scalar_t__ now_stale ; 
 int /*<<< orphan*/  rtadd (scalar_t__,scalar_t__,int /*<<< orphan*/ ,struct rt_spare*) ; 
 int /*<<< orphan*/  rtchange (struct rt_entry*,int /*<<< orphan*/ ,struct rt_spare*,int /*<<< orphan*/ ) ; 
 struct rt_entry* rtget (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  rts_delete (struct rt_entry*,struct rt_spare*) ; 
 int /*<<< orphan*/  rtswitch (struct rt_entry*,struct rt_spare*) ; 
 scalar_t__ total_routes ; 
 int /*<<< orphan*/  trace_upslot (struct rt_entry*,struct rt_spare*,struct rt_spare*) ; 

__attribute__((used)) static void
input_route(naddr dst,			/* network order */
	    naddr mask,
	    struct rt_spare *new,
	    struct netinfo *n)
{
	int i;
	struct rt_entry *rt;
	struct rt_spare *rts, *rts0;
	struct interface *ifp1;


	/* See if the other guy is telling us to send our packets to him.
	 * Sometimes network routes arrive over a point-to-point link for
	 * the network containing the address(es) of the link.
	 *
	 * If our interface is broken, switch to using the other guy.
	 */
	ifp1 = ifwithaddr(dst, 1, 1);
	if (ifp1 != NULL
	    && (!(ifp1->int_state & IS_BROKE)
		|| (ifp1->int_state & IS_PASSIVE)))
		return;

	/* Look for the route in our table.
	 */
	rt = rtget(dst, mask);

	/* Consider adding the route if we do not already have it.
	 */
	if (rt == NULL) {
		/* Ignore unknown routes being poisoned.
		 */
		if (new->rts_metric == HOPCNT_INFINITY)
			return;

		/* Ignore the route if it points to us */
		if (n->n_nhop != 0
		    && ifwithaddr(n->n_nhop, 1, 0) != NULL)
			return;

		/* If something has not gone crazy and tried to fill
		 * our memory, accept the new route.
		 */
		if (total_routes < MAX_ROUTES)
			rtadd(dst, mask, 0, new);
		return;
	}

	/* We already know about the route.  Consider this update.
	 *
	 * If (rt->rt_state & RS_NET_SYN), then this route
	 * is the same as a network route we have inferred
	 * for subnets we know, in order to tell RIPv1 routers
	 * about the subnets.
	 *
	 * It is impossible to tell if the route is coming
	 * from a distant RIPv2 router with the standard
	 * netmask because that router knows about the entire
	 * network, or if it is a round-about echo of a
	 * synthetic, RIPv1 network route of our own.
	 * The worst is that both kinds of routes might be
	 * received, and the bad one might have the smaller
	 * metric.  Partly solve this problem by never
	 * aggregating into such a route.  Also keep it
	 * around as long as the interface exists.
	 */

	rts0 = rt->rt_spares;
	for (rts = rts0, i = NUM_SPARES; i != 0; i--, rts++) {
		if (rts->rts_router == new->rts_router)
			break;
		/* Note the worst slot to reuse,
		 * other than the current slot.
		 */
		if (rts0 == rt->rt_spares
		    || BETTER_LINK(rt, rts0, rts))
			rts0 = rts;
	}
	if (i != 0) {
		/* Found a route from the router already in the table.
		 */

		/* If the new route is a route broken down from an
		 * aggregated route, and if the previous route is either
		 * not a broken down route or was broken down from a finer
		 * netmask, and if the previous route is current,
		 * then forget this one.
		 */
		if (new->rts_de_ag > rts->rts_de_ag
		    && now_stale <= rts->rts_time)
			return;

		/* Keep poisoned routes around only long enough to pass
		 * the poison on.  Use a new timestamp for good routes.
		 */
		if (rts->rts_metric == HOPCNT_INFINITY
		    && new->rts_metric == HOPCNT_INFINITY)
			new->rts_time = rts->rts_time;

		/* If this is an update for the router we currently prefer,
		 * then note it.
		 */
		if (i == NUM_SPARES) {
			rtchange(rt, rt->rt_state, new, 0);
			/* If the route got worse, check for something better.
			 */
			if (new->rts_metric > rts->rts_metric)
				rtswitch(rt, 0);
			return;
		}

		/* This is an update for a spare route.
		 * Finished if the route is unchanged.
		 */
		if (rts->rts_gate == new->rts_gate
		    && rts->rts_metric == new->rts_metric
		    && rts->rts_tag == new->rts_tag) {
			trace_upslot(rt, rts, new);
			*rts = *new;
			return;
		}
		/* Forget it if it has gone bad.
		 */
		if (new->rts_metric == HOPCNT_INFINITY) {
			rts_delete(rt, rts);
			return;
		}

	} else {
		/* The update is for a route we know about,
		 * but not from a familiar router.
		 *
		 * Ignore the route if it points to us.
		 */
		if (n->n_nhop != 0
		    && NULL != ifwithaddr(n->n_nhop, 1, 0))
			return;

		/* the loop above set rts0=worst spare */
		rts = rts0;

		/* Save the route as a spare only if it has
		 * a better metric than our worst spare.
		 * This also ignores poisoned routes (those
		 * received with metric HOPCNT_INFINITY).
		 */
		if (new->rts_metric >= rts->rts_metric)
			return;
	}

	trace_upslot(rt, rts, new);
	*rts = *new;

	/* try to switch to a better route */
	rtswitch(rt, rts);
}