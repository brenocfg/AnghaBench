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
typedef  int u_int ;
struct sockaddr {int dummy; } ;
struct lltable {int /*<<< orphan*/  (* llt_delete_entry ) (struct lltable*,struct llentry*) ;struct ifnet* llt_ifp; } ;
struct llentry {int la_flags; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int EPERM ; 
 int /*<<< orphan*/  IF_AFDATA_WLOCK (struct ifnet*) ; 
 int /*<<< orphan*/  IF_AFDATA_WUNLOCK (struct ifnet*) ; 
 int /*<<< orphan*/  LLE_EXCLUSIVE ; 
 int LLE_IFADDR ; 
 int /*<<< orphan*/  LLE_WUNLOCK (struct llentry*) ; 
 struct llentry* lla_lookup (struct lltable*,int /*<<< orphan*/ ,struct sockaddr const*) ; 
 int /*<<< orphan*/  lltable_unlink_entry (struct lltable*,struct llentry*) ; 
 int /*<<< orphan*/  stub1 (struct lltable*,struct llentry*) ; 

int
lltable_delete_addr(struct lltable *llt, u_int flags,
    const struct sockaddr *l3addr)
{
	struct llentry *lle;
	struct ifnet *ifp;

	ifp = llt->llt_ifp;
	IF_AFDATA_WLOCK(ifp);
	lle = lla_lookup(llt, LLE_EXCLUSIVE, l3addr);

	if (lle == NULL) {
		IF_AFDATA_WUNLOCK(ifp);
		return (ENOENT);
	}
	if ((lle->la_flags & LLE_IFADDR) != 0 && (flags & LLE_IFADDR) == 0) {
		IF_AFDATA_WUNLOCK(ifp);
		LLE_WUNLOCK(lle);
		return (EPERM);
	}

	lltable_unlink_entry(llt, lle);
	IF_AFDATA_WUNLOCK(ifp);

	llt->llt_delete_entry(llt, lle);

	return (0);
}