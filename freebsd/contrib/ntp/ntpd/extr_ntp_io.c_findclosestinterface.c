#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sockaddr_u ;
struct TYPE_4__ {scalar_t__ family; int flags; int /*<<< orphan*/  sin; scalar_t__ ignore_packets; struct TYPE_4__* elink; } ;
typedef  TYPE_1__ endpt ;

/* Variables and functions */
 scalar_t__ AF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DPRINTF (int,char*) ; 
 int /*<<< orphan*/  ZERO_SOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  calc_addr_distance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int cmp_addr_distance (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* ep_list ; 
 int /*<<< orphan*/  stoa (int /*<<< orphan*/ *) ; 

endpt *
findclosestinterface(
	sockaddr_u *	addr,
	int		flags
	)
{
	endpt *		ep;
	endpt *		winner;
	sockaddr_u	addr_dist;
	sockaddr_u	min_dist;

	ZERO_SOCK(&min_dist);
	winner = NULL;

	for (ep = ep_list; ep != NULL; ep = ep->elink) {
		if (ep->ignore_packets ||
		    AF(addr) != ep->family ||
		    flags & ep->flags)
			continue;

		calc_addr_distance(&addr_dist, addr, &ep->sin);
		if (NULL == winner ||
		    -1 == cmp_addr_distance(&addr_dist, &min_dist)) {
			min_dist = addr_dist;
			winner = ep;
		}
	}
	if (NULL == winner)
		DPRINTF(4, ("findclosestinterface(%s) failed\n",
			    stoa(addr)));
	else
		DPRINTF(4, ("findclosestinterface(%s) -> %s\n",
			    stoa(addr), stoa(&winner->sin)));

	return winner;
}