#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ddloc_mem {int dummy; } ;
struct TYPE_5__ {TYPE_1__* dd_td; } ;
struct TYPE_4__ {int /*<<< orphan*/  td_locq; } ;
typedef  TYPE_2__ DIR ;

/* Variables and functions */
 struct ddloc_mem* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 struct ddloc_mem* LIST_NEXT (struct ddloc_mem*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct ddloc_mem*) ; 
 int /*<<< orphan*/  loc_lqe ; 

void
_reclaim_telldir(DIR *dirp)
{
	struct ddloc_mem *lp;
	struct ddloc_mem *templp;

	lp = LIST_FIRST(&dirp->dd_td->td_locq);
	while (lp != NULL) {
		templp = lp;
		lp = LIST_NEXT(lp, loc_lqe);
		free(templp);
	}
	LIST_INIT(&dirp->dd_td->td_locq);
}