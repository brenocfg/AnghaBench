#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct peer {int cast_flags; } ;
typedef  int /*<<< orphan*/  sockaddr_u ;
struct TYPE_8__ {int flags; int /*<<< orphan*/  sin; } ;
typedef  TYPE_1__ endpt ;

/* Variables and functions */
 TYPE_1__* ANY_INTERFACE_CHOOSE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DPRINTF (int,char*) ; 
 int INT_WILDCARD ; 
 scalar_t__ ISREFCLOCKADR (int /*<<< orphan*/ *) ; 
 int MDF_ACAST ; 
 int MDF_BCAST ; 
 int MDF_BCLNT ; 
 int MDF_MCAST ; 
 int /*<<< orphan*/  accept_wildcard_if_for_winnt ; 
 TYPE_1__* findbcastinter (int /*<<< orphan*/ *) ; 
 TYPE_1__* findinterface (int /*<<< orphan*/ *) ; 
 TYPE_1__* loopback_interface ; 
 int /*<<< orphan*/  stoa (int /*<<< orphan*/ *) ; 

endpt *
select_peerinterface(
	struct peer *	peer,
	sockaddr_u *	srcadr,
	endpt *		dstadr
	)
{
	endpt *ep;
#ifndef SIM
	endpt *wild;

	wild = ANY_INTERFACE_CHOOSE(srcadr);

	/*
	 * Initialize the peer structure and dance the interface jig.
	 * Reference clocks step the loopback waltz, the others
	 * squaredance around the interface list looking for a buddy. If
	 * the dance peters out, there is always the wildcard interface.
	 * This might happen in some systems and would preclude proper
	 * operation with public key cryptography.
	 */
	if (ISREFCLOCKADR(srcadr)) {
		ep = loopback_interface;
	} else if (peer->cast_flags &
		   (MDF_BCLNT | MDF_ACAST | MDF_MCAST | MDF_BCAST)) {
		ep = findbcastinter(srcadr);
		if (ep != NULL)
			DPRINTF(4, ("Found *-cast interface %s for address %s\n",
				stoa(&ep->sin), stoa(srcadr)));
		else
			DPRINTF(4, ("No *-cast local address found for address %s\n",
				stoa(srcadr)));
	} else {
		ep = dstadr;
		if (NULL == ep)
			ep = wild;
	}
	/*
	 * If it is a multicast address, findbcastinter() may not find
	 * it.  For unicast, we get to find the interface when dstadr is
	 * given to us as the wildcard (ANY_INTERFACE_CHOOSE).  Either
	 * way, try a little harder.
	 */
	if (wild == ep)
		ep = findinterface(srcadr);
	/*
	 * we do not bind to the wildcard interfaces for output
	 * as our (network) source address would be undefined and
	 * crypto will not work without knowing the own transmit address
	 */
	if (ep != NULL && INT_WILDCARD & ep->flags)
		if (!accept_wildcard_if_for_winnt)
			ep = NULL;
#else	/* SIM follows */
	ep = loopback_interface;
#endif

	return ep;
}