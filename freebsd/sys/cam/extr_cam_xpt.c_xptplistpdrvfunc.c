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
struct periph_driver {scalar_t__ generation; } ;
struct TYPE_3__ {int /*<<< orphan*/ * periph; struct periph_driver** pdrv; } ;
struct TYPE_4__ {int position_type; scalar_t__* generations; TYPE_1__ cookie; } ;
struct ccb_dev_match {TYPE_2__ pos; int /*<<< orphan*/  status; } ;
struct cam_periph {int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_DEV_MATCH_LIST_CHANGED ; 
 int CAM_DEV_POS_PDPTR ; 
 int CAM_DEV_POS_PERIPH ; 
 size_t CAM_PERIPH_GENERATION ; 
 int /*<<< orphan*/  xpt_lock_buses () ; 
 int /*<<< orphan*/  xpt_unlock_buses () ; 
 int xptpdperiphtraverse (struct periph_driver**,struct cam_periph*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  xptplistperiphfunc ; 

__attribute__((used)) static int
xptplistpdrvfunc(struct periph_driver **pdrv, void *arg)
{
	struct cam_periph *periph;
	struct ccb_dev_match *cdm;

	cdm = (struct ccb_dev_match *)arg;

	xpt_lock_buses();
	if ((cdm->pos.position_type & CAM_DEV_POS_PDPTR)
	 && (cdm->pos.cookie.pdrv == pdrv)
	 && (cdm->pos.position_type & CAM_DEV_POS_PERIPH)
	 && (cdm->pos.cookie.periph != NULL)) {
		if (cdm->pos.generations[CAM_PERIPH_GENERATION] !=
		    (*pdrv)->generation) {
			xpt_unlock_buses();
			cdm->status = CAM_DEV_MATCH_LIST_CHANGED;
			return(0);
		}
		periph = (struct cam_periph *)cdm->pos.cookie.periph;
		periph->refcount++;
	} else
		periph = NULL;
	xpt_unlock_buses();

	return (xptpdperiphtraverse(pdrv, periph, xptplistperiphfunc, arg));
}