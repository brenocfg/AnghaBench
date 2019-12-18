#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * bus; } ;
struct TYPE_5__ {int position_type; scalar_t__* generations; TYPE_1__ cookie; } ;
struct ccb_dev_match {int /*<<< orphan*/  status; TYPE_2__ pos; scalar_t__ num_matches; } ;
struct cam_eb {int /*<<< orphan*/  refcount; } ;
struct TYPE_6__ {scalar_t__ bus_generation; } ;

/* Variables and functions */
 size_t CAM_BUS_GENERATION ; 
 int /*<<< orphan*/  CAM_DEV_MATCH_LAST ; 
 int /*<<< orphan*/  CAM_DEV_MATCH_LIST_CHANGED ; 
 int CAM_DEV_POS_BUS ; 
 int /*<<< orphan*/  xpt_lock_buses () ; 
 int /*<<< orphan*/  xpt_unlock_buses () ; 
 int xptbustraverse (struct cam_eb*,int /*<<< orphan*/ ,struct ccb_dev_match*) ; 
 int /*<<< orphan*/  xptedtbusfunc ; 
 TYPE_3__ xsoftc ; 

__attribute__((used)) static int
xptedtmatch(struct ccb_dev_match *cdm)
{
	struct cam_eb *bus;
	int ret;

	cdm->num_matches = 0;

	/*
	 * Check the bus list generation.  If it has changed, the user
	 * needs to reset everything and start over.
	 */
	xpt_lock_buses();
	if ((cdm->pos.position_type & CAM_DEV_POS_BUS)
	 && (cdm->pos.cookie.bus != NULL)) {
		if (cdm->pos.generations[CAM_BUS_GENERATION] !=
		    xsoftc.bus_generation) {
			xpt_unlock_buses();
			cdm->status = CAM_DEV_MATCH_LIST_CHANGED;
			return(0);
		}
		bus = (struct cam_eb *)cdm->pos.cookie.bus;
		bus->refcount++;
	} else
		bus = NULL;
	xpt_unlock_buses();

	ret = xptbustraverse(bus, xptedtbusfunc, cdm);

	/*
	 * If we get back 0, that means that we had to stop before fully
	 * traversing the EDT.  It also means that one of the subroutines
	 * has set the status field to the proper value.  If we get back 1,
	 * we've fully traversed the EDT and copied out any matching entries.
	 */
	if (ret == 1)
		cdm->status = CAM_DEV_MATCH_LAST;

	return(ret);
}