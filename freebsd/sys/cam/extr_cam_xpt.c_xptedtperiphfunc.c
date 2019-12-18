#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct dev_match_result {int dummy; } ;
struct TYPE_12__ {struct cam_periph* periph; TYPE_4__* device; TYPE_3__* target; TYPE_2__* bus; } ;
struct TYPE_11__ {int position_type; int /*<<< orphan*/ * generations; TYPE_1__ cookie; } ;
struct ccb_dev_match {int match_buf_len; int num_matches; TYPE_8__* matches; int /*<<< orphan*/  status; TYPE_10__ pos; int /*<<< orphan*/  num_patterns; int /*<<< orphan*/  patterns; } ;
struct cam_periph {int /*<<< orphan*/  periph_name; int /*<<< orphan*/  unit_number; TYPE_5__* path; } ;
typedef  int dev_match_ret ;
struct TYPE_20__ {int /*<<< orphan*/  bus_generation; } ;
struct TYPE_17__ {int /*<<< orphan*/  periph_name; int /*<<< orphan*/  unit_number; int /*<<< orphan*/  target_lun; int /*<<< orphan*/  target_id; int /*<<< orphan*/  path_id; } ;
struct TYPE_18__ {TYPE_6__ periph_result; } ;
struct TYPE_19__ {TYPE_7__ result; int /*<<< orphan*/  type; } ;
struct TYPE_16__ {TYPE_4__* device; TYPE_3__* target; TYPE_2__* bus; } ;
struct TYPE_15__ {int /*<<< orphan*/  lun_id; int /*<<< orphan*/  generation; } ;
struct TYPE_14__ {int /*<<< orphan*/  target_id; int /*<<< orphan*/  generation; } ;
struct TYPE_13__ {int /*<<< orphan*/  path_id; int /*<<< orphan*/  generation; } ;

/* Variables and functions */
 size_t CAM_BUS_GENERATION ; 
 size_t CAM_DEV_GENERATION ; 
 int /*<<< orphan*/  CAM_DEV_MATCH_ERROR ; 
 int /*<<< orphan*/  CAM_DEV_MATCH_MORE ; 
 int CAM_DEV_POS_BUS ; 
 int CAM_DEV_POS_DEVICE ; 
 int CAM_DEV_POS_EDT ; 
 int CAM_DEV_POS_PERIPH ; 
 int CAM_DEV_POS_TARGET ; 
 size_t CAM_PERIPH_GENERATION ; 
 size_t CAM_TARGET_GENERATION ; 
 int /*<<< orphan*/  DEV_MATCH_PERIPH ; 
 int DM_RET_ACTION_MASK ; 
 int DM_RET_COPY ; 
 int DM_RET_ERROR ; 
 int /*<<< orphan*/  bzero (TYPE_10__*,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int xptperiphmatch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cam_periph*) ; 
 TYPE_9__ xsoftc ; 

__attribute__((used)) static int
xptedtperiphfunc(struct cam_periph *periph, void *arg)
{
	struct ccb_dev_match *cdm;
	dev_match_ret retval;

	cdm = (struct ccb_dev_match *)arg;

	retval = xptperiphmatch(cdm->patterns, cdm->num_patterns, periph);

	if ((retval & DM_RET_ACTION_MASK) == DM_RET_ERROR) {
		cdm->status = CAM_DEV_MATCH_ERROR;
		return(0);
	}

	/*
	 * If the copy flag is set, copy this peripheral out.
	 */
	if (retval & DM_RET_COPY) {
		int spaceleft, j;
		size_t l;

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
				CAM_DEV_POS_EDT | CAM_DEV_POS_BUS |
				CAM_DEV_POS_TARGET | CAM_DEV_POS_DEVICE |
				CAM_DEV_POS_PERIPH;

			cdm->pos.cookie.bus = periph->path->bus;
			cdm->pos.generations[CAM_BUS_GENERATION]=
				xsoftc.bus_generation;
			cdm->pos.cookie.target = periph->path->target;
			cdm->pos.generations[CAM_TARGET_GENERATION] =
				periph->path->bus->generation;
			cdm->pos.cookie.device = periph->path->device;
			cdm->pos.generations[CAM_DEV_GENERATION] =
				periph->path->target->generation;
			cdm->pos.cookie.periph = periph;
			cdm->pos.generations[CAM_PERIPH_GENERATION] =
				periph->path->device->generation;
			cdm->status = CAM_DEV_MATCH_MORE;
			return(0);
		}

		j = cdm->num_matches;
		cdm->num_matches++;
		cdm->matches[j].type = DEV_MATCH_PERIPH;
		cdm->matches[j].result.periph_result.path_id =
			periph->path->bus->path_id;
		cdm->matches[j].result.periph_result.target_id =
			periph->path->target->target_id;
		cdm->matches[j].result.periph_result.target_lun =
			periph->path->device->lun_id;
		cdm->matches[j].result.periph_result.unit_number =
			periph->unit_number;
		l = sizeof(cdm->matches[j].result.periph_result.periph_name);
		strlcpy(cdm->matches[j].result.periph_result.periph_name,
			periph->periph_name, l);
	}

	return(1);
}