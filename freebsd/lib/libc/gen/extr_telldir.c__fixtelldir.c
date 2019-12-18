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
struct ddloc_mem {long loc_loc; long loc_seek; } ;
struct TYPE_5__ {long dd_seek; long dd_loc; TYPE_1__* dd_td; } ;
struct TYPE_4__ {int /*<<< orphan*/  td_locq; } ;
typedef  TYPE_2__ DIR ;

/* Variables and functions */
 struct ddloc_mem* LIST_FIRST (int /*<<< orphan*/ *) ; 

void
_fixtelldir(DIR *dirp, long oldseek, long oldloc)
{
	struct ddloc_mem *lp;

	lp = LIST_FIRST(&dirp->dd_td->td_locq);
	if (lp != NULL) {
		if (lp->loc_loc == oldloc &&
		    lp->loc_seek == oldseek) {
			lp->loc_seek = dirp->dd_seek;
			lp->loc_loc = dirp->dd_loc;
		}
	}
}