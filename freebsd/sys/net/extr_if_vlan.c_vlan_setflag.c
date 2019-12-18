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
struct ifvlan {int ifv_pflags; } ;
struct ifnet {int if_flags; struct ifvlan* if_softc; } ;

/* Variables and functions */
 struct ifnet* PARENT (struct ifvlan*) ; 
 int /*<<< orphan*/  VLAN_SXLOCK_ASSERT () ; 
 int stub1 (struct ifnet*,int) ; 

__attribute__((used)) static int
vlan_setflag(struct ifnet *ifp, int flag, int status,
	     int (*func)(struct ifnet *, int))
{
	struct ifvlan *ifv;
	int error;

	VLAN_SXLOCK_ASSERT();

	ifv = ifp->if_softc;
	status = status ? (ifp->if_flags & flag) : 0;
	/* Now "status" contains the flag value or 0 */

	/*
	 * See if recorded parent's status is different from what
	 * we want it to be.  If it is, flip it.  We record parent's
	 * status in ifv_pflags so that we won't clear parent's flag
	 * we haven't set.  In fact, we don't clear or set parent's
	 * flags directly, but get or release references to them.
	 * That's why we can be sure that recorded flags still are
	 * in accord with actual parent's flags.
	 */
	if (status != (ifv->ifv_pflags & flag)) {
		error = (*func)(PARENT(ifv), status);
		if (error)
			return (error);
		ifv->ifv_pflags &= ~flag;
		ifv->ifv_pflags |= status;
	}
	return (0);
}