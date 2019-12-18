#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct periph_driver {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/ * pdrv; } ;
struct TYPE_3__ {int position_type; TYPE_2__ cookie; } ;
struct ccb_dev_match {int /*<<< orphan*/  status; TYPE_1__ pos; scalar_t__ num_matches; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_DEV_MATCH_LAST ; 
 int CAM_DEV_POS_PDPTR ; 
 int xptpdrvtraverse (struct periph_driver**,int /*<<< orphan*/ ,struct ccb_dev_match*) ; 
 int /*<<< orphan*/  xptplistpdrvfunc ; 

__attribute__((used)) static int
xptperiphlistmatch(struct ccb_dev_match *cdm)
{
	int ret;

	cdm->num_matches = 0;

	/*
	 * At this point in the edt traversal function, we check the bus
	 * list generation to make sure that no buses have been added or
	 * removed since the user last sent a XPT_DEV_MATCH ccb through.
	 * For the peripheral driver list traversal function, however, we
	 * don't have to worry about new peripheral driver types coming or
	 * going; they're in a linker set, and therefore can't change
	 * without a recompile.
	 */

	if ((cdm->pos.position_type & CAM_DEV_POS_PDPTR)
	 && (cdm->pos.cookie.pdrv != NULL))
		ret = xptpdrvtraverse(
				(struct periph_driver **)cdm->pos.cookie.pdrv,
				xptplistpdrvfunc, cdm);
	else
		ret = xptpdrvtraverse(NULL, xptplistpdrvfunc, cdm);

	/*
	 * If we get back 0, that means that we had to stop before fully
	 * traversing the peripheral driver tree.  It also means that one of
	 * the subroutines has set the status field to the proper value.  If
	 * we get back 1, we've fully traversed the EDT and copied out any
	 * matching entries.
	 */
	if (ret == 1)
		cdm->status = CAM_DEV_MATCH_LAST;

	return(ret);
}