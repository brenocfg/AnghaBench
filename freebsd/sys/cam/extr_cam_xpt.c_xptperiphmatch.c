#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
struct periph_match_pattern {int flags; scalar_t__ path_id; scalar_t__ target_id; scalar_t__ target_lun; scalar_t__ unit_number; int /*<<< orphan*/  periph_name; } ;
struct TYPE_6__ {struct periph_match_pattern periph_pattern; } ;
struct dev_match_pattern {scalar_t__ type; TYPE_1__ pattern; } ;
struct cam_periph {scalar_t__ unit_number; int /*<<< orphan*/  periph_name; TYPE_5__* path; } ;
typedef  int dev_match_ret ;
struct TYPE_10__ {TYPE_4__* device; TYPE_3__* target; TYPE_2__* bus; } ;
struct TYPE_9__ {scalar_t__ lun_id; } ;
struct TYPE_8__ {scalar_t__ target_id; } ;
struct TYPE_7__ {scalar_t__ path_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEV_IDLEN ; 
 scalar_t__ DEV_MATCH_PERIPH ; 
 int DM_RET_COPY ; 
 int DM_RET_ERROR ; 
 int DM_RET_STOP ; 
 int PERIPH_MATCH_ANY ; 
 int PERIPH_MATCH_LUN ; 
 int PERIPH_MATCH_NAME ; 
 int PERIPH_MATCH_NONE ; 
 int PERIPH_MATCH_PATH ; 
 int PERIPH_MATCH_TARGET ; 
 int PERIPH_MATCH_UNIT ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static dev_match_ret
xptperiphmatch(struct dev_match_pattern *patterns, u_int num_patterns,
	       struct cam_periph *periph)
{
	dev_match_ret retval;
	u_int i;

	/*
	 * If we aren't given something to match against, that's an error.
	 */
	if (periph == NULL)
		return(DM_RET_ERROR);

	/*
	 * If there are no match entries, then this peripheral matches no
	 * matter what.
	 */
	if ((patterns == NULL) || (num_patterns == 0))
		return(DM_RET_STOP | DM_RET_COPY);

	/*
	 * There aren't any nodes below a peripheral node, so there's no
	 * reason to descend the tree any further.
	 */
	retval = DM_RET_STOP;

	for (i = 0; i < num_patterns; i++) {
		struct periph_match_pattern *cur_pattern;

		/*
		 * If the pattern in question isn't for a peripheral, we
		 * aren't interested.
		 */
		if (patterns[i].type != DEV_MATCH_PERIPH)
			continue;

		cur_pattern = &patterns[i].pattern.periph_pattern;

		/*
		 * If they want to match on anything, then we will do so.
		 */
		if (cur_pattern->flags == PERIPH_MATCH_ANY) {
			/* set the copy flag */
			retval |= DM_RET_COPY;

			/*
			 * We've already set the return action to stop,
			 * since there are no nodes below peripherals in
			 * the tree.
			 */
			return(retval);
		}

		/*
		 * Not sure why someone would do this...
		 */
		if (cur_pattern->flags == PERIPH_MATCH_NONE)
			continue;

		if (((cur_pattern->flags & PERIPH_MATCH_PATH) != 0)
		 && (cur_pattern->path_id != periph->path->bus->path_id))
			continue;

		/*
		 * For the target and lun id's, we have to make sure the
		 * target and lun pointers aren't NULL.  The xpt peripheral
		 * has a wildcard target and device.
		 */
		if (((cur_pattern->flags & PERIPH_MATCH_TARGET) != 0)
		 && ((periph->path->target == NULL)
		 ||(cur_pattern->target_id != periph->path->target->target_id)))
			continue;

		if (((cur_pattern->flags & PERIPH_MATCH_LUN) != 0)
		 && ((periph->path->device == NULL)
		 || (cur_pattern->target_lun != periph->path->device->lun_id)))
			continue;

		if (((cur_pattern->flags & PERIPH_MATCH_UNIT) != 0)
		 && (cur_pattern->unit_number != periph->unit_number))
			continue;

		if (((cur_pattern->flags & PERIPH_MATCH_NAME) != 0)
		 && (strncmp(cur_pattern->periph_name, periph->periph_name,
			     DEV_IDLEN) != 0))
			continue;

		/*
		 * If we get to this point, the user definitely wants
		 * information on this peripheral.  So tell the caller to
		 * copy the data out.
		 */
		retval |= DM_RET_COPY;

		/*
		 * The return action has already been set to stop, since
		 * peripherals don't have any nodes below them in the EDT.
		 */
		return(retval);
	}

	/*
	 * If we get to this point, the peripheral that was passed in
	 * doesn't match any of the patterns.
	 */
	return(retval);
}