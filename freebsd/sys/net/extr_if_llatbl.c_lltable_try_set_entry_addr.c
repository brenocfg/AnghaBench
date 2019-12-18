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
struct llentry {int la_flags; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IF_AFDATA_WLOCK (struct ifnet*) ; 
 int /*<<< orphan*/  IF_AFDATA_WUNLOCK (struct ifnet*) ; 
 int /*<<< orphan*/  LLE_ADDREF (struct llentry*) ; 
 int LLE_DELETED ; 
 int /*<<< orphan*/  LLE_FREE_LOCKED (struct llentry*) ; 
 int /*<<< orphan*/  LLE_REMREF (struct llentry*) ; 
 int /*<<< orphan*/  LLE_WLOCK (struct llentry*) ; 
 int /*<<< orphan*/  LLE_WLOCK_ASSERT (struct llentry*) ; 
 int /*<<< orphan*/  LLE_WUNLOCK (struct llentry*) ; 
 int /*<<< orphan*/  lltable_set_entry_addr (struct ifnet*,struct llentry*,char const*,size_t,int) ; 

int
lltable_try_set_entry_addr(struct ifnet *ifp, struct llentry *lle,
    const char *linkhdr, size_t linkhdrsize, int lladdr_off)
{

	/* Perform real LLE update */
	/* use afdata WLOCK to update fields */
	LLE_WLOCK_ASSERT(lle);
	LLE_ADDREF(lle);
	LLE_WUNLOCK(lle);
	IF_AFDATA_WLOCK(ifp);
	LLE_WLOCK(lle);

	/*
	 * Since we droppped LLE lock, other thread might have deleted
	 * this lle. Check and return
	 */
	if ((lle->la_flags & LLE_DELETED) != 0) {
		IF_AFDATA_WUNLOCK(ifp);
		LLE_FREE_LOCKED(lle);
		return (0);
	}

	/* Update data */
	lltable_set_entry_addr(ifp, lle, linkhdr, linkhdrsize, lladdr_off);

	IF_AFDATA_WUNLOCK(ifp);

	LLE_REMREF(lle);

	return (1);
}