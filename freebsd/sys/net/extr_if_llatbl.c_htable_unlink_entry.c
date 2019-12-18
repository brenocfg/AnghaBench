#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct llentry {int la_flags; int /*<<< orphan*/ * lle_head; TYPE_1__* lle_tbl; } ;
struct TYPE_2__ {int /*<<< orphan*/  llt_ifp; } ;

/* Variables and functions */
 int /*<<< orphan*/  CK_LIST_REMOVE (struct llentry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IF_AFDATA_WLOCK_ASSERT (int /*<<< orphan*/ ) ; 
 int LLE_LINKED ; 
 int LLE_VALID ; 
 int /*<<< orphan*/  lle_next ; 

__attribute__((used)) static void
htable_unlink_entry(struct llentry *lle)
{

	if ((lle->la_flags & LLE_LINKED) == 0)
		return;

	IF_AFDATA_WLOCK_ASSERT(lle->lle_tbl->llt_ifp);
	CK_LIST_REMOVE(lle, lle_next);
	lle->la_flags &= ~(LLE_VALID | LLE_LINKED);
#if 0
	lle->lle_tbl = NULL;
	lle->lle_head = NULL;
#endif
}