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
struct lltable {int /*<<< orphan*/  llt_ifp; } ;
struct llentry {int la_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPSTAT_ADD (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  IF_AFDATA_WLOCK_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int LLE_LINKED ; 
 int /*<<< orphan*/  LLE_WLOCK_ASSERT (struct llentry*) ; 
 int /*<<< orphan*/  dropped ; 
 size_t llentry_free (struct llentry*) ; 
 int /*<<< orphan*/  lltable_unlink_entry (struct lltable*,struct llentry*) ; 

__attribute__((used)) static void
in_lltable_free_entry(struct lltable *llt, struct llentry *lle)
{
	size_t pkts_dropped;

	LLE_WLOCK_ASSERT(lle);
	KASSERT(llt != NULL, ("lltable is NULL"));

	/* Unlink entry from table if not already */
	if ((lle->la_flags & LLE_LINKED) != 0) {
		IF_AFDATA_WLOCK_ASSERT(llt->llt_ifp);
		lltable_unlink_entry(llt, lle);
	}

	/* Drop hold queue */
	pkts_dropped = llentry_free(lle);
	ARPSTAT_ADD(dropped, pkts_dropped);
}