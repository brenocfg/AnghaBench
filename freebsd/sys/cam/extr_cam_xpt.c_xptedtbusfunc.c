#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct dev_match_result {int dummy; } ;
struct TYPE_12__ {int /*<<< orphan*/ * target; struct cam_eb* bus; } ;
struct TYPE_14__ {int position_type; scalar_t__* generations; TYPE_5__ cookie; } ;
struct ccb_dev_match {int match_buf_len; int num_matches; TYPE_7__ pos; int /*<<< orphan*/  status; TYPE_3__* matches; int /*<<< orphan*/  num_patterns; int /*<<< orphan*/  patterns; } ;
struct cam_et {int /*<<< orphan*/  refcount; } ;
struct cam_eb {scalar_t__ generation; int /*<<< orphan*/  eb_mtx; TYPE_4__* sim; int /*<<< orphan*/  path_id; } ;
typedef  int dev_match_ret ;
struct TYPE_13__ {scalar_t__ bus_generation; } ;
struct TYPE_11__ {int /*<<< orphan*/  sim_name; int /*<<< orphan*/  unit_number; int /*<<< orphan*/  bus_id; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev_name; int /*<<< orphan*/  unit_number; int /*<<< orphan*/  bus_id; int /*<<< orphan*/  path_id; } ;
struct TYPE_9__ {TYPE_1__ bus_result; } ;
struct TYPE_10__ {TYPE_2__ result; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 size_t CAM_BUS_GENERATION ; 
 int /*<<< orphan*/  CAM_DEV_MATCH_ERROR ; 
 int /*<<< orphan*/  CAM_DEV_MATCH_LIST_CHANGED ; 
 int /*<<< orphan*/  CAM_DEV_MATCH_MORE ; 
 int CAM_DEV_POS_BUS ; 
 int CAM_DEV_POS_EDT ; 
 int CAM_DEV_POS_TARGET ; 
 size_t CAM_TARGET_GENERATION ; 
 int /*<<< orphan*/  DEV_MATCH_BUS ; 
 int DM_RET_ACTION_MASK ; 
 int DM_RET_COPY ; 
 int DM_RET_DESCEND ; 
 int DM_RET_ERROR ; 
 int DM_RET_STOP ; 
 int /*<<< orphan*/  bzero (TYPE_7__*,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int xptbusmatch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cam_eb*) ; 
 int /*<<< orphan*/  xptedttargetfunc ; 
 int xpttargettraverse (struct cam_eb*,struct cam_et*,int /*<<< orphan*/ ,void*) ; 
 TYPE_6__ xsoftc ; 

__attribute__((used)) static int
xptedtbusfunc(struct cam_eb *bus, void *arg)
{
	struct ccb_dev_match *cdm;
	struct cam_et *target;
	dev_match_ret retval;

	cdm = (struct ccb_dev_match *)arg;

	/*
	 * If our position is for something deeper in the tree, that means
	 * that we've already seen this node.  So, we keep going down.
	 */
	if ((cdm->pos.position_type & CAM_DEV_POS_BUS)
	 && (cdm->pos.cookie.bus == bus)
	 && (cdm->pos.position_type & CAM_DEV_POS_TARGET)
	 && (cdm->pos.cookie.target != NULL))
		retval = DM_RET_DESCEND;
	else
		retval = xptbusmatch(cdm->patterns, cdm->num_patterns, bus);

	/*
	 * If we got an error, bail out of the search.
	 */
	if ((retval & DM_RET_ACTION_MASK) == DM_RET_ERROR) {
		cdm->status = CAM_DEV_MATCH_ERROR;
		return(0);
	}

	/*
	 * If the copy flag is set, copy this bus out.
	 */
	if (retval & DM_RET_COPY) {
		int spaceleft, j;

		spaceleft = cdm->match_buf_len - (cdm->num_matches *
			sizeof(struct dev_match_result));

		/*
		 * If we don't have enough space to put in another
		 * match result, save our position and tell the
		 * user there are more devices to check.
		 */
		if (spaceleft < sizeof(struct dev_match_result)) {
			bzero(&cdm->pos, sizeof(cdm->pos));
			cdm->pos.position_type =
				CAM_DEV_POS_EDT | CAM_DEV_POS_BUS;

			cdm->pos.cookie.bus = bus;
			cdm->pos.generations[CAM_BUS_GENERATION]=
				xsoftc.bus_generation;
			cdm->status = CAM_DEV_MATCH_MORE;
			return(0);
		}
		j = cdm->num_matches;
		cdm->num_matches++;
		cdm->matches[j].type = DEV_MATCH_BUS;
		cdm->matches[j].result.bus_result.path_id = bus->path_id;
		cdm->matches[j].result.bus_result.bus_id = bus->sim->bus_id;
		cdm->matches[j].result.bus_result.unit_number =
			bus->sim->unit_number;
		strlcpy(cdm->matches[j].result.bus_result.dev_name,
			bus->sim->sim_name,
			sizeof(cdm->matches[j].result.bus_result.dev_name));
	}

	/*
	 * If the user is only interested in buses, there's no
	 * reason to descend to the next level in the tree.
	 */
	if ((retval & DM_RET_ACTION_MASK) == DM_RET_STOP)
		return(1);

	/*
	 * If there is a target generation recorded, check it to
	 * make sure the target list hasn't changed.
	 */
	mtx_lock(&bus->eb_mtx);
	if ((cdm->pos.position_type & CAM_DEV_POS_BUS)
	 && (cdm->pos.cookie.bus == bus)
	 && (cdm->pos.position_type & CAM_DEV_POS_TARGET)
	 && (cdm->pos.cookie.target != NULL)) {
		if ((cdm->pos.generations[CAM_TARGET_GENERATION] !=
		    bus->generation)) {
			mtx_unlock(&bus->eb_mtx);
			cdm->status = CAM_DEV_MATCH_LIST_CHANGED;
			return (0);
		}
		target = (struct cam_et *)cdm->pos.cookie.target;
		target->refcount++;
	} else
		target = NULL;
	mtx_unlock(&bus->eb_mtx);

	return (xpttargettraverse(bus, target, xptedttargetfunc, arg));
}