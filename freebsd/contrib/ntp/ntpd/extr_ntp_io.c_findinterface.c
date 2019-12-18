#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sockaddr_u ;
struct TYPE_5__ {int /*<<< orphan*/  name; int /*<<< orphan*/  ifnum; } ;
typedef  TYPE_1__ endpt ;

/* Variables and functions */
 TYPE_1__* ANY_INTERFACE_CHOOSE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DPRINTF (int,char*) ; 
 int /*<<< orphan*/  INT_WILDCARD ; 
 TYPE_1__* findlocalinterface (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stoa (int /*<<< orphan*/ *) ; 

endpt *
findinterface(
	sockaddr_u *addr
	)
{
	endpt *iface;

	iface = findlocalinterface(addr, INT_WILDCARD, 0);

	if (NULL == iface) {
		DPRINTF(4, ("Found no interface for address %s - returning wildcard\n",
			    stoa(addr)));

		iface = ANY_INTERFACE_CHOOSE(addr);
	} else
		DPRINTF(4, ("Found interface #%d %s for address %s\n",
			    iface->ifnum, iface->name, stoa(addr)));

	return iface;
}