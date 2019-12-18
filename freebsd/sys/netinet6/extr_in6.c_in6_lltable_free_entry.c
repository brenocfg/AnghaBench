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
struct lltable {struct ifnet* llt_ifp; } ;
struct llentry {int la_flags; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IF_AFDATA_WLOCK_ASSERT (struct ifnet*) ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int LLE_LINKED ; 
 int /*<<< orphan*/  LLE_WLOCK_ASSERT (struct llentry*) ; 
 int /*<<< orphan*/  llentry_free (struct llentry*) ; 
 int /*<<< orphan*/  lltable_unlink_entry (struct lltable*,struct llentry*) ; 

__attribute__((used)) static void
in6_lltable_free_entry(struct lltable *llt, struct llentry *lle)
{
	struct ifnet *ifp;

	LLE_WLOCK_ASSERT(lle);
	KASSERT(llt != NULL, ("lltable is NULL"));

	/* Unlink entry from table */
	if ((lle->la_flags & LLE_LINKED) != 0) {

		ifp = llt->llt_ifp;
		IF_AFDATA_WLOCK_ASSERT(ifp);
		lltable_unlink_entry(llt, lle);
	}

	llentry_free(lle);
}