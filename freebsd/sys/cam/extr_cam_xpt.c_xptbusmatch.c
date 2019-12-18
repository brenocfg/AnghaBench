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
typedef  scalar_t__ u_int ;
struct bus_match_pattern {int flags; scalar_t__ path_id; scalar_t__ bus_id; scalar_t__ unit_number; int /*<<< orphan*/  dev_name; } ;
struct TYPE_3__ {struct bus_match_pattern bus_pattern; } ;
struct dev_match_pattern {scalar_t__ type; TYPE_1__ pattern; } ;
struct cam_eb {scalar_t__ path_id; TYPE_2__* sim; } ;
typedef  int dev_match_ret ;
struct TYPE_4__ {scalar_t__ bus_id; scalar_t__ unit_number; int /*<<< orphan*/  sim_name; } ;

/* Variables and functions */
 int BUS_MATCH_ANY ; 
 int BUS_MATCH_BUS_ID ; 
 int BUS_MATCH_NAME ; 
 int BUS_MATCH_NONE ; 
 int BUS_MATCH_PATH ; 
 int BUS_MATCH_UNIT ; 
 int /*<<< orphan*/  DEV_IDLEN ; 
 scalar_t__ DEV_MATCH_BUS ; 
 int DM_RET_ACTION_MASK ; 
 int DM_RET_COPY ; 
 int DM_RET_DESCEND ; 
 int DM_RET_ERROR ; 
 int DM_RET_NONE ; 
 int DM_RET_STOP ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static dev_match_ret
xptbusmatch(struct dev_match_pattern *patterns, u_int num_patterns,
	    struct cam_eb *bus)
{
	dev_match_ret retval;
	u_int i;

	retval = DM_RET_NONE;

	/*
	 * If we aren't given something to match against, that's an error.
	 */
	if (bus == NULL)
		return(DM_RET_ERROR);

	/*
	 * If there are no match entries, then this bus matches no
	 * matter what.
	 */
	if ((patterns == NULL) || (num_patterns == 0))
		return(DM_RET_DESCEND | DM_RET_COPY);

	for (i = 0; i < num_patterns; i++) {
		struct bus_match_pattern *cur_pattern;

		/*
		 * If the pattern in question isn't for a bus node, we
		 * aren't interested.  However, we do indicate to the
		 * calling routine that we should continue descending the
		 * tree, since the user wants to match against lower-level
		 * EDT elements.
		 */
		if (patterns[i].type != DEV_MATCH_BUS) {
			if ((retval & DM_RET_ACTION_MASK) == DM_RET_NONE)
				retval |= DM_RET_DESCEND;
			continue;
		}

		cur_pattern = &patterns[i].pattern.bus_pattern;

		/*
		 * If they want to match any bus node, we give them any
		 * device node.
		 */
		if (cur_pattern->flags == BUS_MATCH_ANY) {
			/* set the copy flag */
			retval |= DM_RET_COPY;

			/*
			 * If we've already decided on an action, go ahead
			 * and return.
			 */
			if ((retval & DM_RET_ACTION_MASK) != DM_RET_NONE)
				return(retval);
		}

		/*
		 * Not sure why someone would do this...
		 */
		if (cur_pattern->flags == BUS_MATCH_NONE)
			continue;

		if (((cur_pattern->flags & BUS_MATCH_PATH) != 0)
		 && (cur_pattern->path_id != bus->path_id))
			continue;

		if (((cur_pattern->flags & BUS_MATCH_BUS_ID) != 0)
		 && (cur_pattern->bus_id != bus->sim->bus_id))
			continue;

		if (((cur_pattern->flags & BUS_MATCH_UNIT) != 0)
		 && (cur_pattern->unit_number != bus->sim->unit_number))
			continue;

		if (((cur_pattern->flags & BUS_MATCH_NAME) != 0)
		 && (strncmp(cur_pattern->dev_name, bus->sim->sim_name,
			     DEV_IDLEN) != 0))
			continue;

		/*
		 * If we get to this point, the user definitely wants
		 * information on this bus.  So tell the caller to copy the
		 * data out.
		 */
		retval |= DM_RET_COPY;

		/*
		 * If the return action has been set to descend, then we
		 * know that we've already seen a non-bus matching
		 * expression, therefore we need to further descend the tree.
		 * This won't change by continuing around the loop, so we
		 * go ahead and return.  If we haven't seen a non-bus
		 * matching expression, we keep going around the loop until
		 * we exhaust the matching expressions.  We'll set the stop
		 * flag once we fall out of the loop.
		 */
		if ((retval & DM_RET_ACTION_MASK) == DM_RET_DESCEND)
			return(retval);
	}

	/*
	 * If the return action hasn't been set to descend yet, that means
	 * we haven't seen anything other than bus matching patterns.  So
	 * tell the caller to stop descending the tree -- the user doesn't
	 * want to match against lower level tree elements.
	 */
	if ((retval & DM_RET_ACTION_MASK) == DM_RET_NONE)
		retval |= DM_RET_STOP;

	return(retval);
}