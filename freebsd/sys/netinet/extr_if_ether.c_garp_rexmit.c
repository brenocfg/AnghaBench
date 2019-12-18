#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* ifa_ifp; } ;
struct in_ifaddr {int ia_garp_count; TYPE_1__ ia_ifa; int /*<<< orphan*/  ia_garp_timer; } ;
struct TYPE_9__ {int /*<<< orphan*/  sin_addr; } ;
struct TYPE_8__ {int /*<<< orphan*/  if_vnet; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURVNET_RESTORE () ; 
 int /*<<< orphan*/  CURVNET_SET (int /*<<< orphan*/ ) ; 
 TYPE_6__* IA_SIN (struct in_ifaddr*) ; 
 int /*<<< orphan*/  IF_ADDR_WLOCK (TYPE_2__*) ; 
 int /*<<< orphan*/  IF_ADDR_WUNLOCK (TYPE_2__*) ; 
 int /*<<< orphan*/  IF_LLADDR (TYPE_2__*) ; 
 int /*<<< orphan*/  arprequest (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_active (int /*<<< orphan*/ *) ; 
 scalar_t__ callout_pending (int /*<<< orphan*/ *) ; 
 int callout_reset (int /*<<< orphan*/ *,int,void (*) (void*),struct in_ifaddr*) ; 
 int garp_rexmit_count ; 
 int hz ; 
 int /*<<< orphan*/  ifa_free (TYPE_1__*) ; 

__attribute__((used)) static void
garp_rexmit(void *arg)
{
	struct in_ifaddr *ia = arg;

	if (callout_pending(&ia->ia_garp_timer) ||
	    !callout_active(&ia->ia_garp_timer)) {
		IF_ADDR_WUNLOCK(ia->ia_ifa.ifa_ifp);
		ifa_free(&ia->ia_ifa);
		return;
	}

	CURVNET_SET(ia->ia_ifa.ifa_ifp->if_vnet);

	/*
	 * Drop lock while the ARP request is generated.
	 */
	IF_ADDR_WUNLOCK(ia->ia_ifa.ifa_ifp);

	arprequest(ia->ia_ifa.ifa_ifp, &IA_SIN(ia)->sin_addr,
	    &IA_SIN(ia)->sin_addr, IF_LLADDR(ia->ia_ifa.ifa_ifp));

	/*
	 * Increment the count of retransmissions. If the count has reached the
	 * maximum value, stop sending the GARP packets. Otherwise, schedule
	 * the callout to retransmit another GARP packet.
	 */
	++ia->ia_garp_count;
	if (ia->ia_garp_count >= garp_rexmit_count) {
		ifa_free(&ia->ia_ifa);
	} else {
		int rescheduled;
		IF_ADDR_WLOCK(ia->ia_ifa.ifa_ifp);
		rescheduled = callout_reset(&ia->ia_garp_timer,
		    (1 << ia->ia_garp_count) * hz,
		    garp_rexmit, ia);
		IF_ADDR_WUNLOCK(ia->ia_ifa.ifa_ifp);
		if (rescheduled) {
			ifa_free(&ia->ia_ifa);
		}
	}

	CURVNET_RESTORE();
}